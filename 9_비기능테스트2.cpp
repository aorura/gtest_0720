
// 메모리 검증
//  1) new / delete 재정의가 필요합니다.
//  2) 테스트에서만 활용 가능하도록 만들어주어야 합니다.
//    => 조건부 컴파일 기능

#include <gtest/gtest.h>

class Image {
public:
	Image() { printf("Image()\n"); }
	~Image() { printf("~Image()\n"); }

#ifdef GTEST_LEAK_TEST
	static int allocCount;

	void* operator new(size_t size) {
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		--allocCount;
		free(p);
	}
#endif
};

#ifdef GTEST_LEAK_TEST
int Image::allocCount = 0;
#endif

class ImageTest : public testing::Test {
protected:
	int allocCount;
	void SetUp() override {
#ifdef GTEST_LEAK_TEST
		allocCount = Image::allocCount;
#endif
	}

	void TearDown() override {
#ifdef GTEST_LEAK_TEST
		int diff = Image::allocCount - allocCount;
		EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
#endif
	}
};

// g++ 9_비기능테스트2.cpp -I. -lgtest -L. -pthread -DGTEST_LEAK_TEST
void foo() {
	Image* p1 = new Image;
	Image* p2 = new Image;
	Image* p3 = new Image;
}

TEST_F(ImageTest, foo) {
	foo();
}








