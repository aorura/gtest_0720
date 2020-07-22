
#include <gmock/gmock.h>

struct MP3 {
	virtual ~MP3() {}

	virtual void Play() = 0;
	virtual void Stop(int n) = 0;

	virtual std::string GetName() const = 0;
};

// MP3* p = ...
// delete p;

// MP3의 모의 객체를 생성하고 싶다.
// 1.10 이후
// - 더 이상 스크립트는 제공되지 않습니다.
// - MOCK_METHOD(반환타입, 메소드이름, 인자정보, 한정자);
class MockMP3 : public MP3 {
public:
	// void Play() override {}
	MOCK_METHOD(void, Play, (), (override));
	MOCK_METHOD(void, Stop, (int n), (override));

	// std::string GetName() const override {}
	MOCK_METHOD(std::string, GetName, (), (const, override));
};


// 1.10 이전
//  - MOCK_METHOD{N}(메소드이름, 메소드의시그니처)
//  - MOCK_CONST_METHOD{N}(메소드이름, 메소드의시그니처)
#if 0
class MockMP3 : public MP3 {
public: // Mocking 된 모든 메소드는 public 이어야 합니다.
	MOCK_METHOD0(Play, void());
	MOCK_METHOD1(Stop, void(int n));

	MOCK_CONST_METHOD0(GetName, std::string());
};
#endif

// Mocking이 제대로 되었는지 확인하기 위해서는 모의 객체를 생성해야 합니다.
TEST(MP3Test, MockTest) {
	MockMP3 mock;


}
