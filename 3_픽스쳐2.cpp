class Calculator {
public:
	// Calculator(int v) {}

	int Display() { return 0; }

	void Enter(int v) {}

	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
};

//-----------------------------------
#include <gtest/gtest.h>

// Test Fixture 설치 방법 3가지
//  3. Implicit Setup(암묵적 설치)
//   => xUnit Test Framework이 제공하는 기능입니다.
//   여러 테스트에서 같은 테스트 픽스쳐의 코드를 SetUp()을 통해 설치한다.
//    장점: 테스트 코드 중복을 제거하고, 필요하지 않은 상호작용을 제거할 수 있다.
//    단점: 픽스쳐 설치 코드가 테스트 함수 밖에 존재하기 때문에,
//          테스트 함수만으로 테스트 코드를 이해하기 어려울 수 있다.

// 1. TestSuite class
class CalculatorTest : public testing::Test {
protected:
	Calculator* calc;   // !!

	void SetUp() override {
		printf("SetUp()\n");
		calc = new Calculator;
	}
};


#if 1
#define SPEC(msg) printf(msg)
TEST_F(CalculatorTest, Plus_AddingTwoPlusTwo_DisplaysFour) {
	printf("Plus_AddingTwoPlusTwo_DisplaysFour()\n");
	SPEC("2 더하기 2 하였을 때 Display가 4를 반환하는지를 검증한다.\n");
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST_F(CalculatorTest, PlusTest2) {
	printf("PlusTest2()\n");
	
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST_F(CalculatorTest, PlusTest) {
	printf("PlusTest()\n");
	
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	if (calc->Display() == 4) {
		SUCCEED();
	} else {
		FAIL();
	}
}
#endif
