#include <gmock/gmock.h>


struct Point {
	virtual ~Point() {}

	virtual int GetValue() const { return 100; }
};


class MockPoint : public Point {
public:
	MOCK_METHOD(int, GetValue, (), (override, const));
};
//
// ON_CALL - WillByDefault
//   : 행위 기반 검증없이 결과를 제어할 때 사용한다.
// EXPECT_CALL
//   : 행위 기반 검증 + 결과를 제어할 수 있습니다.
//    - WillOnce
//    - WillRepeatedly

void UsePoint(Point* p) {
	int a = p->GetValue();
	int b = p->GetValue();

	if (a > 0) {
		printf("A가 0보다 큽니다..%d\n", a);
	}

	if (b > 100) {
		printf("B가 100보다 큽니다..%d\n", b);
	}

	printf("%d\n", p->GetValue()); 
	printf("%d\n", p->GetValue()); 
	printf("%d\n", p->GetValue()); 
	printf("%d\n", p->GetValue()); 
}

using testing::Return;

// 호출 횟수 결정
// 1. EXPECT_CALL(...) 
//    -> 1번
//
// 2. EXPECT_CALL(..).WillOnce(...)
//    -> WillOnce가 N번 정의되었으면, N번
//
// 3. N개의 WillOnce / 1개의 WillRepeatedly
//    -> .Times(AtLeast(N));

TEST(PointTest, GetValue) {
	MockPoint mock;
	int n = 1000;

	// EXPECT_CALL(mock, GetValue()).Times(2);
	EXPECT_CALL(mock, GetValue())
		.WillOnce(Return(42))
		.WillOnce(Return(120))
		.WillRepeatedly([&n] {
			return ++n;
		});

	UsePoint(&mock);
}










