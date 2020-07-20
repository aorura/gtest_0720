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

// Test Fixture
//  정의: xUnit Test Pattern에서는 SUT를 실행하기 위해 준비해야 하는 모든 것을 테스트 픽스쳐라고 합니다.
//   픽스쳐를 구성하는 모든 로직 부분을 "픽스쳐를 설치한다." 라고 합니다.


// Test Fixture 설치 방법 3가지
//  1. Inline Setup
//    : 모든 픽스쳐의 설치를 테스트 함수안에서 수행한다.
//    장점: 픽스쳐를 설치하는 과정과 검증로직이 테스트 함수 안에 존재하기 때문에
//          테스트 인과관계를 쉽게 파악할 수 있다.
//    단점: 모든 테스트 코드 안에서 "테스트 코드 중복"이 발생한다.

//  2. Delegate Setup(위임 설치)
//    : 테스트 코드 안에서 픽스쳐 설치에 관한 코드를 테스트 유틸리티 메소드를 통해 모듈화한다.
//    => Test Suite 클래스를 명시적으로 작성해야 합니다.
//    => Test Case를 만들 때, TEST가 아닌 TEST_F라는 매크로를 통해 작성해야 합니다.


//   - TEST
//  testing::Test
//       |
// TEST(CalcTest, foo)
//
//   - TEST_F
//   testing::Test
//       |
//  CalculatorTest
//       |
// TEST_F(CalculatorTest, foo)

#if 1
// 명시적으로 Test Suite 클래스를 만드는 방법.
class CalculatorTest : public testing::Test {
protected:
	Calculator* Create() { return new Calculator(0); }
	// Test Utility Method - Creation Method
};

#define SPEC(msg) printf(msg)
TEST_F(CalculatorTest, Plus_AddingTwoPlusTwo_DisplaysFour) {
	SPEC("2 더하기 2 하였을 때 Display가 4를 반환하는지를 검증한다.\n");
	// Arrange
	Calculator* calc = Create();
	
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST_F(CalculatorTest, PlusTest2) {
	Calculator* calc = Create();
	
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST_F(CalculatorTest, PlusTest) {
	// Arrange
	Calculator* calc = Create();
	
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
#if 0
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
