
// Mock Object Pattern
//  => 행위 기반 검증
//    1) 메소드 호출 여부 
//    2) 메소드 호출 횟수 / 인자 검증
//    3) 메소드 호출 순서
//
//  => 테스트 대역 프레임워크
//    : Stub 또는 Fake의 동작도 Google Mock을 통해 해결할 수 있습니다.

class User {
public:
	virtual ~User() {}

	virtual void Say(const char* message) = 0;
	virtual int Add(int a, int b) {}
};

//-------------------

#include <gmock/gmock.h>

class MockUser : public User {
public:
	MOCK_METHOD(void, Say, (const char* message), (override));
	MOCK_METHOD(int, Add, (int a, int b), (override));
};

void Do(User* user) {
	user->Say("Hello");
}

// 1. 호출 여부 검사
//  - EXPECT_CALL
TEST(UserTest, DoTest1) {
	MockUser mock;

	EXPECT_CALL(mock, Say("Hello"));

	Do(&mock);
}

// 2. 호출 횟수 검사
//   * EXPECT_CALL - 1번의 호출에 대해서 기대하고 있다.
//   * Times(N)
//      => N - N번 호출 검증
//         AtLeast(N) - N번 이상
//         AtMost(N) - N번 이하
//          - Cardinality
using testing::AtLeast;
using testing::AtMost;
using testing::AnyNumber;
using testing::Between;
//  - Between(1, 3)

// 3. 호출 인자 검증 - Matching 결과에 따라서, 호출 횟수에 대한 조정이 필요하다.
//   * Matcher
//      _: 모든 것에 매칭
//      Eq, Lt, Gt, Le, Ge
//      AllOf: &&
//      AnyOf: ||
using testing::Eq;
using testing::Lt;
using testing::Gt;
using testing::Le;
using testing::Ge;

using testing::AllOf;
using testing::AnyOf;

using testing::HasSubstr;
using testing::StartsWith;

using testing::_;

void Do2(User* user) {
	user->Say("Hello, Tom");
	user->Say("Hello, Bob");

	user->Add(10, 20);
	user->Add(20, 20);
	user->Add(30, 20);
}

TEST(UserTest, DoTest3) {
	MockUser mock;

	// EXPECT_CALL(mock, Say(HasSubstr("Hello"))).Times(AtLeast(2));
	EXPECT_CALL(mock, Say(StartsWith("Hello"))).Times(AtLeast(2));

	// Add의 첫번째 인자 조건: 0 < a && a <= 30
	//       두번째 인자 조건: a > 10 || a < 5
	auto firstMatcher = AllOf(Gt(0), Le(30));
	auto secondMatcher = AnyOf(Gt(10), Lt(5));

	EXPECT_CALL(mock, Add(firstMatcher, secondMatcher))
		.Times(AtMost(3));

	// EXPECT_CALL(mock, Add(Le(30), Eq(20))).Times(3);
	
	// EXPECT_CALL(mock, Add(Lt(30), Ge(20))).Times(2);
	// EXPECT_CALL(mock, Add(30, _));
	
	// EXPECT_CALL(mock, Add(_, _)).Times(3);
#if 0
	EXPECT_CALL(mock, Add(10, 20));
	EXPECT_CALL(mock, Add(20, 20));
	EXPECT_CALL(mock, Add(30, 20));
#endif

	Do2(&mock);
}


using testing::NiceMock;
TEST(UserTest, DISABLED_DoTest2) {
	NiceMock<MockUser> mock;

	// EXPECT_CALL(mock, Say("Hello")).Times(2);
	EXPECT_CALL(mock, Say("Hello")).Times(AtLeast(3));

	Do2(&mock);
}

struct Foo {
	virtual ~Foo() {}

	virtual void First() {}
	virtual void Second() {}
	virtual void Third() {}
	virtual void Forth() {}
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, First, (), (override));
	MOCK_METHOD(void, Second, (), (override));
	MOCK_METHOD(void, Third, (), (override));
	MOCK_METHOD(void, Forth, (), (override));
};

void Do3(Foo* p) { 
	p->First();
	p->Second();
	p->Forth();

	p->Third();
}

// 메소드 호출 순서
//   - EXPECT_CALL은 기본적으로 순서를 검증하고 있지 않습니다.
//   1) InSequence 객체
using testing::InSequence;
using testing::Sequence;

//   2) Sequence 객체
//		   - Third            :s1
//         |
// First --
//         |
//         - Second - Forth  :s2

TEST(FooTest, DoTest5) {
	Sequence s1, s2;
	MockFoo mock;

	EXPECT_CALL(mock, First()).InSequence(s1, s2);
	EXPECT_CALL(mock, Third()).InSequence(s1);
	EXPECT_CALL(mock, Second()).InSequence(s2);
	EXPECT_CALL(mock, Forth()).InSequence(s2);

	Do3(&mock);
}


// First -> Second -> Third -> Forth
TEST(FooTest, DoTest4) {
	InSequence seq;
	MockFoo mock;

	EXPECT_CALL(mock, First());
	EXPECT_CALL(mock, Second());
	EXPECT_CALL(mock, Third());
	EXPECT_CALL(mock, Forth());

	Do3(&mock);
}




























