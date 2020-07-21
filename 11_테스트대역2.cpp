
#include <string>

struct IFileSystem {
	virtual ~IFileSystem() {}

	virtual bool IsValid(const std::string& filename) = 0;
};

class FileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		// ...
		return false;
	}
};

class Logger {
	IFileSystem* fs;
public:
	explicit Logger(IFileSystem* p = nullptr) : fs(p) {
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}

	bool IsValidFilename(const std::string& filename) {
		//------
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5)
			return false;
		//-----

		// IFileSystem* fs = new FileSystem;
		return fs->IsValid(filename);
	}
};

#include <gtest/gtest.h>

// 1. 테스트 대역을 만드는 방법 - 협력 객체의 인터페이스 또는 추상 클래스를 상속 받는다.
class TestDouble : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		return true;
	}
};

TEST(LoggerTest, IsValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	TestDouble stub;
	Logger logger(&stub);
	std::string badFilename = "bad.log";

	EXPECT_FALSE(logger.IsValidFilename(badFilename)) << "파일이름이 5글자 미만일때";
}

TEST(LoggerTest, IsValidFilename_NameLoggerThan5Chars_ReturnsTrue) {
	TestDouble stub;
	Logger logger(&stub);
	std::string validFilename = "valid.log";

	EXPECT_TRUE(logger.IsValidFilename(validFilename)) << "파일이름이 5글자 이상일때";
}

// - 참고: Test Double이전에 Mock 이름을 사용하였습니다.
// Test Double 종류 
//   : xUnit Test Pattern - 제라드
//   1) Test Stub
//   2) Fake Object
//   3) Test Spy
//   4) Mock Object
//
//   5) Dummy Object - Type
