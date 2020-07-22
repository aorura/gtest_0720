
// 19_Delegating.cpp

#include <gmock/gmock.h>

class User {
public:
	virtual ~User() {}

	virtual std::string GetName() const { return "Tom"; }
	virtual int GetAge() const { return 42; }
};

//-----------

class MockUser : public User {
public:
	MOCK_METHOD(std::string, GetName, (), (override, const));
	MOCK_METHOD(int, GetAge, (), (override, const));
};

// * Google Mock은 Mocking Method의 결과를 제어할 수 있는 기능을 제공합니다.
//  - ON_CALL
//      .WillByDefault
//   : Stub, Fake를 구현할 때 이용하는 매크로

using testing::Return;
using testing::ReturnRef;

using testing::NiceMock;
TEST(UserTest, MockTest) {
	NiceMock<MockUser> user;
	int age = 10;

	ON_CALL(user, GetName())
		.WillByDefault(Return("Alice"));
	ON_CALL(user, GetAge())
		.WillByDefault([&age] {
			return age++;
		});

	std::cout << user.GetName() << ", " << user.GetAge() << std::endl;
	std::cout << user.GetName() << ", " << user.GetAge() << std::endl;
	std::cout << user.GetName() << ", " << user.GetAge() << std::endl;
	std::cout << user.GetName() << ", " << user.GetAge() << std::endl;
	std::cout << user.GetName() << ", " << user.GetAge() << std::endl;
}







