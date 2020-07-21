#include <gtest/gtest.h>

// #define class struct
// #define private public
#include "User.h"

// SUT의 검증하고자 하는 상태 또는 함수가 private으로 되어 있을 경우,
// 검증을 수행할 수 없다.
//  - private 필드나 메소드를 검증하기 위해서, Google Test는 FRIEND_TEST라는 기능을 제공하고 있습니다.
//  
//  * 클린 코드 - 로버트 C 마틴
//  - private 메소드는 public 메소드의 가독성을 높이기 위해 사용해야 한다.
//   => public 메소드를 호출하면, 자연스럽게 private 메소드도 호출되어야 한다.
//  - 검증되지 않은 private 메소드 보다 검증된 pubilc 메소드가 안전하다.

TEST(UserTest, AgeTest) {
	User user(42);

	// ...
	
	EXPECT_EQ(user.GetAge(), 42);
}
