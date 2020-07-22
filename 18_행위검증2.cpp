
#include <gmock/gmock.h>

class Printer {
public:
	virtual ~Printer() {}

	virtual void Print(int c) {}
	virtual void Print(char c) {}
};

class MockPrinter : public Printer {
public:
	MOCK_METHOD(void, Print, (int c), (override));
	MOCK_METHOD(void, Print, (char c), (override));
};

// 위의 상황에처럼 오버로딩에서 모호성 에러가 발생한다면,
// Matcher를 이용해서, 정확하게 EXPECT_CALL을 작성해야 합니다.

using testing::Matcher;
using testing::Eq;
using testing::TypedEq;

TEST(PrinterTest, Print) {
	MockPrinter mock;

	EXPECT_CALL(mock, Print(Matcher<int>(Eq(42))));
	EXPECT_CALL(mock, Print(TypedEq<char>('c')));

	mock.Print(42);
	mock.Print('c');
}
