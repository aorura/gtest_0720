
#include <string>

// 문제점: 아래의 SUT는 테스트 대역을 적용할 수 없습니다.
//     = 테스트 대역을 적용하기 위해서는 반드시 제품 코드가 테스트 대역을 적용할 수 있는 설계이어야 합니다.
//     -> 의존하는 객체에 대해서 '강한 결합'이 아닌 '약한 결합'이 사용되어야 합니다.
//       * 강한 결합: 의존하는 객체를 이용할 때, 구체적인 타입에 의존하는 것
//       * 약한 결합: 의존하는 객체를 이용할 때, 인터페이스나 추상 클래스에 의존하는 것
//         => 의존하는 객체를 직접 생성하면 안됩니다.
//            new는 강한 결합을 형성합니다.
//             : 외부에서 생성해서, 전달받아야 합니다. - DI(Dependency Injection)
//             1) 생성자 주입
//               - 의존 객체가 필수적일 때 
//             2) 메소드 주입
//               - 의존 객체가 필수적이지 않을 때
//
//            문제점: 보일러플레이트가 발생한다.
//               User -> School, Address
//                User user(new School(), new Address());
//
//                "의존성 주입에 대한 설계를 적용할 때, 의존성 주입 프레임워크를 이용하면,
//                 보일러플레이트를 효과적으로 제거하는 것이 가능하다."
//                 - "google/fruit"

// SUT
// 1. Interface 도입하자.
// 2. 의존성 주입 - 생성자 주입
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
	// 틈새 만들기: 기존 클래스의 사용법과 동일하게 만드는 것이 좋습니다.

	explicit Logger(IFileSystem* p = nullptr) : fs(p) {
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}

	// file.log
	//  => 확장자를 제외한 파일의 이름이 5글자 이상이어야 한다.
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

TEST(LoggerTest, IsValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	Logger logger;
	std::string badFilename = "bad.log";

	EXPECT_FALSE(logger.IsValidFilename(badFilename)) << "파일이름이 5글자 미만일때";
}

TEST(LoggerTest, IsValidFilename_NameLoggerThan5Chars_ReturnsTrue) {
	Logger logger;
	std::string validFilename = "valid.log";

	EXPECT_TRUE(logger.IsValidFilename(validFilename)) << "파일이름이 5글자 이상일때";
}
