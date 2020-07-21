#ifndef USER_H
#define USER_H

#include <gtest/gtest.h> 
// FRIEND_TEST를 사용할 경우, SUT가 Google Test에 의존성을 가지게 된다.

class User {
	int age;
	int GetAge() const { return age; }
public:
	User(int n) : age(n) {}


	FRIEND_TEST(UserTest, AgeTest);

private:
	// int GetAge() const { return age; }
};

#define private public

#endif
