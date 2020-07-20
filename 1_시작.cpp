#include <gtest/gtest.h>


// 테스트 구성 - xUnit
//    TestSuite
//       TestCase 1
//       TestCase 2
//
// Google Test(1.10 버전 이전)
//    TestCase
//       Test 1
//       Test 2


// 1. 구글 테스트에서 테스트를 작성하는 방법.
//  - TEST(테스트 스위트 이름, 테스트 케이스 이름)
TEST(TestSuiteName, TestCase1) {
	FAIL();
}

TEST(TestSuiteName, TestCase2) {

}

TEST(SampleTest, TestCase1) {
	FAIL() << "작성 중입니다.";
}

TEST(SampleTest, TestCase2) {

}
