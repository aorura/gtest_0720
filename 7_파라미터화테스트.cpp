// 7_파라미터화테스트

// SUT
bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0)
			return false;
	}

	return true;
}


// Parameterized Test
//  정의: 입력 데이터를 바꿔가며, 수차례 반복 검사하는 데이터 중심의 테스트에서 코드 중복을 없애는 기법.
//   => xUnit Test Pattern

#include <gtest/gtest.h>

using testing::Values;

// Google Test에서 파라미터화 테스트를 작성하는 방법.

// 1. Test Suite 작성 - TestWithParam<T>
class PrimeTest : public testing::TestWithParam<int> {

};

// 2. Data Set 정의 - INSTANTIATE_TEST_SUITE_P(변수명, 테스트스위트, 데이터셋)
INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest, 
	Values(2, 3, 5, 7, 11, 13, 17, 19));

// 3. 이제 다양한 테스트케이스를 작성하면 됩니다. - TEST_P
TEST_P(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(GetParam()));
}


// 문제점
// 1) 복잡도
// 2) 일반적인 테스트 케이스와 같이 사용할 수 없다.



#if 0
int data[] = { 2, 3, 5, 7, 11, 13, 17, 19 };
TEST(PrimeTest, IsPrime2) {
	EXPECT_TRUE(IsPrime(data[0]));
	EXPECT_TRUE(IsPrime(data[1]));
	EXPECT_TRUE(IsPrime(data[2]));
	EXPECT_TRUE(IsPrime(data[3]));
	EXPECT_TRUE(IsPrime(data[4]));
	EXPECT_TRUE(IsPrime(data[5]));
	EXPECT_TRUE(IsPrime(data[6]));
	EXPECT_TRUE(IsPrime(data[7]));
	EXPECT_TRUE(IsPrime(data[8]));
}

TEST(PrimeTest, IsPrime) {
	for (int i = 0 ; i < sizeof(data) / sizeof(data[0]) ; ++i) {
		EXPECT_TRUE(IsPrime(data[i]));
	}
}
#endif
