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
//  3. Implicit Setup / Tear Down (암묵적 설치/해체)
//   => xUnit Test Framework이 제공하는 기능입니다.
//   여러 테스트에서 같은 테스트 픽스쳐의 코드를 SetUp()을 통해 설치한다.
//    장점: 테스트 코드 중복을 제거하고, 필요하지 않은 상호작용을 제거할 수 있다.
//    단점: 픽스쳐 설치 코드가 테스트 함수 밖에 존재하기 때문에,
//          테스트 함수만으로 테스트 코드를 이해하기 어려울 수 있다.
//
// xUnit Test Pattern - 4단계 테스트 패턴
// 1단계: 테스트 픽스쳐를 설치하거나 실제 경과를 관찰하기 위해, 필요한 것을 집어넣는 작업을 수행한다.  - SetUp()
// 2단계: SUT와 상호작용한다. - TestBody()
// 3단계: 기대 결과를 확인한다. - TestBody()
// 4단계: 테스트 픽스쳐를 해체해서, 테스트 시작 이전의 상태로 돌려놓는다. - TearDown()

// xUnit Test Runner가 테스트를 수행하는 순서 - 신선한 픽스쳐의 전략
//  TestSuite* ts = new TestSuite;
//  ts->SetUp();
//  ts->TestBody1();
//  ts->TearDown();
//  delete ts;
//
//  TestSuite* ts = new TestSuite;
//  ts->SetUp();
//  ts->TestBody2();
//  ts->TearDown();
//  delete ts;
//
//  TestSuite* ts = new TestSuite;
//  ts->SetUp();
//  ts->TestBody3();
//  ts->TearDown();
//  delete ts;



// 1. TestSuite class
class CalculatorTest : public testing::Test {
protected:
	CalculatorTest() { printf("CalculatorTest()\n"); }
	~CalculatorTest() { printf("~CalculatorTest()\n"); }

	Calculator* calc;   // !!

	void SetUp() override {
		printf("SetUp()\n");
		calc = new Calculator;
	}

	// 암묵적 해체의 함수 - 테스트의 성공 실패와 상관없이, 항상 수행됨을 보장한다.
	void TearDown() override {
		printf("TearDown()\n");
		delete calc;
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
	// 특징: 단언문이 실패할 경우, 이후의 코드는 수행되지 않는다.

	// printf("Calc 객체 파괴..\n");
	// delete calc;
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
