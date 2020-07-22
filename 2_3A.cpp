
// 2_3A.cpp

// SUT(System Under Test)
//   : 테스트 대상 시스템
//    - 단위 테스트를 작성하고자 하는 코드, 모듈, 시스템 등을 의미한다.
//    CUT(Class Under Test, Code Under Test)

class Calculator {
public:
	int Display() { return 0; }

	void Enter(int v) {}

	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
};

//-----------------------------------

#include <gtest/gtest.h>

// TDD(테스트 주도 개발) -> BDD(행위 주도 개발)
//                          1) 용어
//                          2) 행위 검증 - Mock


// TestSuite 이름
//  - 테스트 대상 클래스의 이름의 마지막에 Test 또는 Spec를 붙이는 형태로 만든다.
//  => CalculatorTest / CalculatorSpec

// TestCase를 구성하는 방법 - 3A
// 1. Arrange: 테스트 하고자는 클래스의 객체를 생성하고, 필요한 경우 설정하고 준비한다.(Given)
// 2. Act: 객체에 작용을 가한다. (When)
// 3. Assert: 기대하는 바를 단언한다. (Then)

// TestCase 품질
//  : 커버리지 - 테스트 코드에 의해서 제품 코드가 실행된 비율
//  1) 가독성
//  2) 유지보수성
//  3) 신뢰성

#define SPEC(msg) printf(msg)

// ex1) 테스트 케이스 이름
//     테스트대상메소드_동작_기대값
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


// * 테스트케이스의 이름에서 테스트의 시나리오가 드러날 수 있도록 작성하는 것이 좋습니다.
TEST(CalculatorTest, PlusTest2) {
	// Arrange
	Calculator* calc = new Calculator;
	
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert - 원하는 조건을 체크하기 위해서, 조건문을 사용하는 것이 아니라,
	//          xUnit Test Framework이 제공하는 단언기능을 이용하는 것이 좋다.
	//          Google Test: 단언 매크로
	//          * 실패의 원인을 작성하는 것이 중요하다.
	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

// * 테스트케이스 코드안에서는 제어 구문(조건문, 반복문, 예외처리)의 사용을 최소화해야 한다.
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
