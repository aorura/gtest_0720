#include <gtest/gtest.h>

class Image {
public:
	Image() { printf("Image()\n"); }
	~Image() { printf("~Image()\n"); }

	static int allocCount;

	void* operator new(size_t size) {
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		--allocCount;
		free(p);
	}
};

int Image::allocCount = 0;

TEST(ImageTest, foo) {
	Image* p1 = new Image;
	Image* p2 = new Image;

	// ...
}

using testing::TestSuite;
using testing::TestInfo;
class MyTestListener : public testing::EmptyTestEventListener {
	int allocCount;

	void OnTestStart(const TestInfo& test_info) override {
		std::cout << test_info.name() << "," << test_info.test_suite_name() << std::endl;
		printf("OnTestStart\n");

		if (strcmp(test_info.test_suite_name(), "ImageTest") != 0)
			return;

		allocCount = Image::allocCount;
	}

	void OnTestEnd(const TestInfo& test_info) override {
		printf("OnTestEnd\n");

		if (strcmp(test_info.test_suite_name(), "ImageTest") != 0)
			return;

		int diff = Image::allocCount - allocCount;
		EXPECT_LE(diff, 0) << "Leaked " << diff << " objects";
	}
};

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	bool check_for_leaks = false;
	if (argc > 1 && strcmp(argv[1], "--check_for_leaks") == 0) {
		check_for_leaks = true;
	}
	
	if (check_for_leaks) {
		// 기본 출력 형식을 제거하는 것도 가능합니다.
		testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
		// listeners.Release(listeners.default_result_printer());
 
		listeners.Append(new MyTestListener);
	}

	return RUN_ALL_TESTS();
}
