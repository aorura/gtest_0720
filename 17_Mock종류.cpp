// 17_목의 종류
//  - Google Mock

#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual void Say(const std::string& message) = 0;
	virtual void Do() = 0;
};


class User {
public:
	void UseFoo(Foo* p) {
		// p->Say("Hello");
		// p->Do();  // !!
	}
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, Say, (const std::string& message), (override));

	MOCK_METHOD(void, Do, (), (override));
};

// 목의 종류
// 1. NaggyMock
//    MockFoo mock;
//    NaggyMock<MockFoo> mock;
//     => EXPECT_CALL을 하지 않은 Mocking된 메소드가 호출되면, '경고'를 준다.

// 2. NiceMock
//     => EXPECT_CALL을 하지 않은 Mocking된 메소드에 대해서 아무런 메세지를 주지 않는다.
//
// 3. StrictMock
//     =>                      "                            테스트가 실패한다.
//     => 주의해서 사용해야 합니다.
//        테스트의 요구사항을 만족하는 테스트케이스의 작성 비용이 높아질 수 있다.

using testing::NaggyMock;
using testing::NiceMock;
using testing::StrictMock;

class UserTest : public testing::Test {
protected:
	User user;
	NiceMock<MockFoo> mock;

	void SetUp() override {

	}

	void TearDown() override {

	}
};

TEST_F(UserTest, DISABLED_UseFooTest) {
	EXPECT_CALL(mock, Say("Hello"));

	user.UseFoo(&mock);
}

TEST_F(UserTest, UserFooTest2) {
	EXPECT_CALL(mock, Say("Hello"));

	user.UseFoo(&mock);
	ASSERT_EQ(1, 2);
}


#if 0
TEST(UserTest, DISABLED_UseFooTest) {
	StrictMock<MockFoo> mock;
	User user;

	EXPECT_CALL(mock, Say("Hello"));

	user.UseFoo(&mock);
}


// * Google Mock은 mock객체가 파괴되는 시점에 검증을 수행한다.

TEST(UserTest, UserFooTest2) {
	MockFoo mock;
	// MockFoo* mock = new MockFoo;
	User user;

	EXPECT_CALL(mock, Say("Hello"));

	user.UseFoo(&mock);
	ASSERT_EQ(1, 2);

	// delete mock;  // !!!
}
#endif













