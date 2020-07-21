class User {
	int age;
public:
	User(int n) : age(n) {}
protected:
	int GetAge() const { return age; }
};


#include <gtest/gtest.h>

// 테스트 전용 하위 클래스 
//  : SUT에서 테스트하고자 하는 기능을 제공하지 않을 경우,
//    SUT의 하위 클래스를 테스트 전용으로 만들어서 검증한다.

class TestUser : public User {
public:
	TestUser(int n) : User(n) {}

	using User::GetAge;   // 부모의 protected를 public으로 공개하겠다.
};


TEST(UserTest, AgeTest) {
	// User user(42);
	TestUser user(42);

	// ...
	
	EXPECT_EQ(user.GetAge(), 42);
}
