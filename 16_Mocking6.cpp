#include <gmock/gmock.h>

enum Level { INFO, WARN };

struct Logger {
	virtual ~Logger() {}

	virtual void Send(Level level, const char* filename, const char* dir, int line) = 0;
};

class User {
public:
	void Go(Logger* logger) {
		logger->Send(INFO, "user.txt", "/tmp", 0);
		// ...
	}
};

class MockLogger : public Logger {
public:
	// 1. EXPECT_CALL에서 사용하는 형태로 Mocking을 수행한다.
	MOCK_METHOD(void, Send, (Level level, const char* filename));

	// 2. 기존 함수를 재정의한다.
	void Send(Level level, const char* filename, const char* dir, int line) override {
		Send(level, filename);
		// 3. Mocking된 메소드를 호출한다.
	}
};

//---------------------------------
TEST(LoggerTest, GoTest) {
	MockLogger mock;
	User user;

	EXPECT_CALL(mock, Send(INFO, "user.txt"));

	user.Go(&mock);
}
