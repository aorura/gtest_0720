
// 1.
#include <gmock/gmock.h>


#if 0
// 2.
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
#endif

// Google Test의 main은 거의 동일합니다.
// main을 라이브러리에 포함해서 사용하는 경우가 많습니다.
