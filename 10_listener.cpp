
// Google Test가 제공하는 기능 - Listener
// - Listener를 등록
//    : main 함수를 직접 작성해서, 등록해야 합니다.


#include <gtest/gtest.h>

TEST(SampleTest, Sample1) {

}

TEST(SampleTest, Sample2) {

}

TEST(SampleTest2, foo) {

}

using testing::TestSuite;
using testing::TestInfo;
class MyTestListener : public testing::EmptyTestEventListener {
	void OnTestSuiteStart(const TestSuite& /*test_suite*/) override {
		printf("OnTestSuiteStart\n");
	}

	void OnTestStart(const TestInfo& /*test_info*/) override {
		printf("OnTestStart\n");
	}

	void OnTestEnd(const TestInfo& /*test_info*/) override {
		printf("OnTestEnd\n");
	}

	void OnTestSuiteEnd(const TestSuite& /*test_suite*/) override {
		printf("OnTestSuiteEnd\n");
	}
};

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	
	testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
	listeners.Append(new MyTestListener);

	return RUN_ALL_TESTS();
}






