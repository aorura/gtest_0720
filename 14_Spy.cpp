
#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR,
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

class DLogger {
	std::vector<DLoggerTarget*> targets;
public:
	void AddTarget(DLoggerTarget* p) {
		targets.push_back(p);
	}

	void Write(Level level, const std::string& message) {
		for (DLoggerTarget* p : targets) {
			p->Write(level, message);
		}
	}
};

//-----------------------------
#include <gtest/gtest.h>
#include <algorithm>

// Test Spy Pattern
//  의도: 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서
//        테스트되지 않은 요구사항이 있을 때
//  방법: 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역을 이용하면 된다.

class SpyTarget : public DLoggerTarget {
	std::vector<std::string> history;

	std::string concat(Level level, const std::string& message) {
		static const char* levels[] = {
			"INFO", "WARN", "ERROR",
		};

		return std::string(levels[level]) + "@" + message;
	}

public:
	void Write(Level level, const std::string& message) override {
		history.push_back(concat(level, message));
	}

	bool IsReceived(Level level, const std::string& message) {
		return std::find(history.begin(), history.end(), concat(level, message)) != history.end();
	}
};

TEST(DLoggerTest, WriteTest) {
	// Arrange
	DLogger logger;
	SpyTarget spy1, spy2;
	logger.AddTarget(&spy1);
	logger.AddTarget(&spy2);
	Level test_level = INFO;
	std::string test_message = "test_message";

	// Act
	logger.Write(test_level, test_message);

	// Assert
	EXPECT_TRUE(spy1.IsReceived(test_level, test_message));
	EXPECT_TRUE(spy2.IsReceived(test_level, test_message));
}
