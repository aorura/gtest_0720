
// 파라미터화 테스트에서 데이터 셋을 지정하는 방법.

// 1. Values
// 2. Range
// 3. ValuesIn

#include <gtest/gtest.h>

using testing::Range;
using testing::ValuesIn;

class ParamTest : public testing::TestWithParam<std::string> {

};

std::vector<std::string> GetNames() {
	std::vector<std::string> v;

	v.push_back("Tom");
	v.push_back("Bob");
	v.push_back("Alice");

	return v;
};

INSTANTIATE_TEST_SUITE_P(ParamValues, ParamTest,
	ValuesIn(GetNames()));

#if 0
std::string names[] = {
	"Tom", "Bob", "Alice",
};

INSTANTIATE_TEST_SUITE_P(ParamValues, ParamTest,
	ValuesIn(names));
#endif

TEST_P(ParamTest, Sample2) {
	std::cout << GetParam() << std::endl;
}


#if 0
class ParamTest : public testing::TestWithParam<int> {
};

INSTANTIATE_TEST_SUITE_P(ParamValues, ParamTest,
	Range(0, 100, 5));
    // [0, 100)

TEST_P(ParamTest, Sample1) {
	printf("%d\n", GetParam());
}
#endif

