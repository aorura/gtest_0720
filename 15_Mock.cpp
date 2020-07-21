#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR,
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

class DLogger {
	std::vector<DLoggerTarget*> targets;
public:
	void AddTarget(DLoggerTarget* p) {
		targets.push_back(p);
	}

	void Write(Level level, const std::string& message) {
		for (DLoggerTarget* p : targets) {
			p->Write(level, message);
		}
	}
};

//-----------------------------
// Mock Object Pattern
//  의도: 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서
//        테스트되지 않은 요구사항이 있을 때
//  방법: '상태 기반 검증'이 아닌 '행위 기반 검증'을 통해 검증한다.
//    모의 객체(Mock Object): 내부적으로 발생하는 함수에 호출에 관한 정보를 기록하는 객체
//      - 상태 검증: 객체에 작용을 가한 후, 단언 메소드 등을 통해서 내부의 상태값을 확인하는 테스트케이스
//      - 행위 검증: 객체에 작용을 가한 후, 올바른 동작의 판단 근거로
//             함수의 호출 여부, 호출 횟수, 호출 순서 등의 정보를 검증하는 테스트케이스
//
//    모의 객체를 생성하기 위해서는 Mock Framework을 이용해야 합니다.
//     - Java: jMock, EasyMock, Mockito
//     - C++: Google Mock

// 1. 헤더 파일 포함
#include <gmock/gmock.h>

// 2. Mocking - 모의 객체 생성
//  - Google Mock에서는 Mocking을 수행하는 스크립트를 제공하고 있습니다.
//   => $ cd ./googletest/googlemock/scripts/generator/gmock_gen.py
//      $ ./gmock_gen ~/chansik.yun/DLoggerTarget.h
//      - 위의 스크립트는 더 이상 사용되지 않습니다.
class MockDLoggerTarget : public DLoggerTarget {
public:
  MOCK_METHOD2(Write,
      void(Level level, const std::string& message));
};

// 3. TestCase를 작성해서, 행위 기반 검증을 수행한다.
TEST(DLoggerTarget, WriteTest) {
	// Arrange
	DLogger logger;
	MockDLoggerTarget mock1, mock2;
	logger.AddTarget(&mock1);
	logger.AddTarget(&mock2);
	Level test_level = INFO;
	std::string test_message = "test_message";
	
	// 주의 사항: Act 단계를 수행하기 전에, 행위 기반 검증을 작성해야 한다. - Google Mock
	// Assert
	EXPECT_CALL(mock1, Write(test_level, test_message));
	EXPECT_CALL(mock2, Write(test_level, test_message));

	// Act
	logger.Write(test_level, test_message);
}

//--------------------------------------
// Test 대역 종류
// 1. Stub
//   : 특수한 상황을 시뮬레이션 한다. 협력 객체에 대해서 원하는 결과를 주는 테스트 대역으로 변경해서 사용한다.
// 2. Fake
// 	 : 의존 하는 객체가 아직 준비되지 않았을 때, 사용하기 어려울 때, 너무 느려서 느린 테스트의 문제가 발생할 때
// 	   가벼운 테스트 대역을 작성해서 검증한다.
//  
//  "객체에 작용을 가했을 때, 관찰할 수 있는 부수효과가 없어서, 테스트되지 않은 요구 사항이 있다."
// 3. Spy
//   => 목격한 일을 기록해두었다가, 테스트에서 검증할 수 있는 기능을 제공하는 테스트 대역
// 4. Mock
//   => 모의 객체(함수의 호출에 대한 정보를 기록하는 테스트 대역)를 통해서 행위 기반 검증을 수행한다.
//
//  Mock(Test Double) Framework - Google Mock
//   "행위 기반 검증만을 제공하는 것이 아니라, Stub, Fake를 만드는 데도 활용할 수 있습니다."
