class Calculator {
public:
	Calculator(int v) {}

	int Display() { return 0; }

	void Enter(int v) {}

	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
};

//-----------------------------------
#include <gtest/gtest.h>

// Test Fixture 설치 방법 3가지
#if 1
#define SPEC(msg) printf(msg)
TEST(CalculatorTest, Plus_AddingTwoPlusTwo_DisplaysFour) {
	SPEC("2 더하기 2 하였을 때 Display가 4를 반환하는지를 검증한다.\n");
	// Arrange
	Calculator* calc = new Calculator;
	
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST(CalculatorTest, PlusTest2) {
	Calculator* calc = new Calculator;
	
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST(CalculatorTest, PlusTest) {
	// Arrange
	Calculator* calc = new Calculator;
	
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
