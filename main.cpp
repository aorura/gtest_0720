
// 1.
#include <gmock/gmock.h>

// Google Mock - ./googletest/googlemock/src/gmock_main.cc
int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);
	// InitGoogleTest를 호출할 필요가 없다.
	
	return RUN_ALL_TESTS();
}


// Google Test - ./googletest/googletest/src/gtest_main.cc
#if 0
// 2.
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
#endif

// Google Test의 main은 거의 동일합니다.
// main을 라이브러리에 포함해서 사용하는 경우가 많습니다.

