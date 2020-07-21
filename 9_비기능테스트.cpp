
// 비기능 테스트
//  : 기능적인 동작에 대한 검증이 아니라,
//    성능이나 메모리에 대한 비기능적인 부분을 검증하는 테스트
//    => Google Test는 비기능 검증에 대한 기능을 제공하지 않습니다.

#include <unistd.h>

void Job() {
	sleep(2);
}


#include <gtest/gtest.h>

// 1) 시간 측정용 Test Suite
class TimeCriticalTest : public testing::Test {
protected:
	time_t startTime;
	void SetUp() override {
		startTime = time(0);
	}

	void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_LE(duration, 1) << "시간 초과: " << duration << " 초가 걸렸습니다.";
	}
};


// Job이 1초의 시간안에 수행되어야 한다.
TEST_F(TimeCriticalTest, Job) {
	//...
	// Job();
	// ...
}

// 2) Test Utility Method - Assertions
#define EXPECT_TIMEOUT(fn, limit)				\
	do {										\
		time_t startTime = time(0);             \
		fn;										\
		time_t endTime = time(0);				\
		time_t duration = endTime - startTime;	\
		EXPECT_LE(duration, limit) << "시간 초과: " << duration << " 초가 걸렸습니다."; \
	} while (0)


TEST(JobTest, Job) {
	EXPECT_TIMEOUT(Job(), 1);
}
















