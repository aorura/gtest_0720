
// 6_Assertions.cpp
#include <gtest/gtest.h>

// 1. EXPECT
// ASSERT_ 단언문은 실패할 경우, 이후의 코드를 수행하지 않는다.
//  => 하나의 테스트 케이스 안에 여러개의 단언문을 사용하지 않는 것이 좋다.
//    : '죽은 단언문'의 문제가 발생할 수 있다.

// EXPECT_ 단언문을 제공합니다.
//  => 단언문이 실패하더라도, 이후의 코드를 계속 수행한다.
//     하나의 단언문이라도 실패하면, 테스트의 결과는 실패가 된다.

// EXPECT_
//    EQ(==), NE(!=), LT(<), GT(>), LE(<=), GE(>=), TRUE, FALSE ...

TEST(GoogleTest, DISABLED_Sample1) {
	int expected1 = 42;
	int expected2 = 42;

	int actual1 = 10;
	int actual2 = 20;

	EXPECT_EQ(expected1, actual1) << "reason 1";
	EXPECT_EQ(expected2, actual2) << "reason 2";
}

#include <string>
// 2. 문자열(C-Style)
//  C-Style의 문자열을 단언문을 통해 비교할 경우,
//  EXPECT_STREQ / EXPECT_STRCASEEQ / EXPECT_STRNE / EXPECT_STRCASENE
TEST(DISABLED_GoogleTest, Sample2) {
	std::string s1 = "hello";
	std::string s2 = "hello";

	EXPECT_EQ(s1, s2);

	const char* s3 = "Hello";
	const char* s4 = s2.c_str();

	// EXPECT_EQ(s3, s4) << "C-Style";
	EXPECT_STREQ(s3, s4) << "C-Style";
	EXPECT_STRCASEEQ(s3, s4) << "대소문자 구문하지 않는";
}


// 3. 부동 소수점
//  EXPECT_DOUBLE_EQ/NE
//  EXPECT_FLOAT_EQ/NE
//
//  오차 범위를 직접 지정하고 싶다.
//  EXPECT_NEAR
TEST(GoogleTest, Sample3) {
	double a = 0.7;
	double b = 0.1 * 7;

	// EXPECT_EQ(a, b);
	// EXPECT_DOUBLE_EQ(a, b); // 4ULPs
	EXPECT_NEAR(a, b, 0.00000000001);
}


// TDD
//  1. 만들고자 하는 기능의 테스트 코드를 작성한다.
//  2. 실패한다.
//  3. 기능을 작성한다.
//  4. 성공한다.
//  5. 리팩토링한다.

// 4. 예외 테스트
void IsValidFilename(const std::string& name) {
	// return;
	// throw 1;
	if (name.empty()) {
		throw std::invalid_argument("파일 이름이 비어있다...");
	}
}

TEST(GoogleTest, Sample4_Good) {
	std::string emptyFilename = "";

	EXPECT_THROW(IsValidFilename(emptyFilename), std::invalid_argument);
}

// IsValidFilename에 ""문자열을 전달하였을 경우, invalid_argument 예외가 발생하는지를 검증하고 싶다.
TEST(GoogleTest, Sample4) {
	std::string emptyFilename = "";

	try {
		IsValidFilename(emptyFilename);
		FAIL() << "예외가 발생하지 않음...";
	} catch (std::invalid_argument&) {
		SUCCEED();
	} catch (...) {
		FAIL() << "다른 종류의 예외가 발생하였음...";
	}
}

// 5. 테스트 비활성화
//  - 테스트를 비활성화하기 위해서, 테스트를 주석 처리하는 것은 좋지 않다.
//    => 잊혀진 테스트
//    구글 테스트에서 테스트를 비활성화하기 위해서는, TestSuite 이름 또는 TestCase의 이름이
//    DISABLED_의 접두로 시작하면 됩니다.

//  - 비활성화된 테스트를 같이 구동할 수 있는 기능을 제공합니다.
//   $ ./a.out --gtest_also_run_disabled_tests

class DISABLED_SampleTest : public testing::Test {
};

TEST_F(DISABLED_SampleTest, Sample5) {

}

// 6. 구글 테스트가 제공하는 실행 옵션
//  1) --gtest_filter
//    : 선택적으로 테스트를 수행할 수 있는 기능을 제공합니다.
//      $ ./a.out --gtest_filter=*.P_*
//  2) 반복 테스트
//      $ ./a.out --gtest_repeat=N --gtest_break_on_failure --gtest_shuffle

// CalcTest.AddTest
TEST(CalcTest, P_AddTest) {
	// FAIL();
}

// CalcTest.SubTest
TEST(CalcTest, N_SubTest) {

}





















