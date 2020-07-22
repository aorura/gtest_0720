
#include <string>

struct IFileSystem {
	virtual ~IFileSystem() {}

	virtual bool IsValid(const std::string& filename) = 0;
};

class FileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
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

#include <gmock/gmock.h>

class MockFileSystem : public IFileSystem {
public:
	MOCK_METHOD(bool, IsValid, (const std::string& filename), (override));
};

using testing::Return;
using testing::NiceMock; // Stub, Fake

TEST(LoggerTest, IsValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	std::string badFilename = "bad.log";
	NiceMock<MockFileSystem> stub;
	ON_CALL(stub, IsValid(badFilename)).WillByDefault(Return(true));
	Logger logger(&stub);

	EXPECT_FALSE(logger.IsValidFilename(badFilename)) << "파일이름이 5글자 미만일때";
}

TEST(LoggerTest, IsValidFilename_NameLoggerThan5Chars_ReturnsTrue) {
	std::string validFilename = "valid.log";
	NiceMock<MockFileSystem> stub;
	ON_CALL(stub, IsValid(validFilename)).WillByDefault(Return(true));
	Logger logger(&stub);

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
