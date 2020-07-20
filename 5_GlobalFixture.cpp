
// 5_GlobalFixture.cpp

// - Google Test가 제공하는 고유의 기능입니다.
// - 프로그램이 시작될 때 수행되는 SetUp(),
//   프로그램이 종료되기 이전에 수행되는 TearDown()을 정의한다.

#include <gtest/gtest.h>

// 1. testing::Environment 기반의 클래스를 작성한다.
class MyTestEnvironment : public testing::Environment {
public:
	void SetUp() override {
		printf("MyTestEnvironment::SetUp()\n");
	}

	void TearDown() override {
		printf("MyTestEnvironment::TearDown()\n");
	}

	// 힙에 생성하는 싱글톤 - C++
	static MyTestEnvironment& Instance() {
		static MyTestEnvironment* instance = new MyTestEnvironment;
		return *instance;
	}
};

// 2. Google Test Framework에 MyTestEnvironment 객체를 등록해주어야 한다.
//   1) 전역 변수 - main함수를 정의하고 있지 않을 때 - 권장 X
// testing::Environment* myTestEnv = testing::AddGlobalTestEnvironment(new MyTestEnvironment);

//   2) main 함수
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	testing::AddGlobalTestEnvironment(&MyTestEnvironment::Instance());
	// testing::AddGlobalTestEnvironment(new MyTestEnvironment);
	
	// MyTestEnvironment myTestEnv;
	// testing::AddGlobalTestEnvironment(&myTestEnv);
	// 힙에 생성된 객체를 등록해야 합니다.

	return RUN_ALL_TESTS();
}


TEST(SampleTest, foo) {}
TEST(SampleTest2, goo) {}




