
// SUT

#include <iostream>

class NetworkException : public std::exception {
public:
	const char* what() {
		return "Bad Network State...";
	}
};

// 인터페이스 문제점: 변화에 대응하기 어렵다.
//   - 인터페이스에 기본 구현을 제공하는 것이 좋다.
struct IConnection {
	virtual ~IConnection() {}

	virtual void Move(int x, int y) = 0;

	// default method / defender method
	virtual void Attack() {}
};

class TCPConnection : public IConnection {
public:
	void Move(int x, int y) override {
		// Packet 생성
		// Packet 전송
		// ...
	}
};

// Player player(new TCPConnection);

class Player {
	IConnection* conn;
public:
	Player(IConnection* p) : conn(p) {}

	void Move(int x, int y) {
		try {
			conn->Move(x, y);
		} catch (NetworkException& e) {
			printf("Network 예외에 대한 로직...\n");
			throw e;
		}
	}
};

#include <gtest/gtest.h>

// Test Stub Pattern
//  의도: 다른 컴포넌트로부터의 간접 입력에 의존하는 로직을 독립적으로 검증하고 싶다.
//  방법: 실제 의존하는 객체를 테스트용 객체로 교체해서, SUT가 테스트하는데 필요한 결과를 보내도록 제어한다.
// => 특수한 상황을 시뮬레이션 하고 싶다.
//  : 네트워크 상태, 시간 등의 제어가 불가능한 환경을 제어할 수 있다.

// 협력 객체의 인터페이스가 간결할 수록, 테스트 대역을 만드는 비용이 적다.
class StubConnection : public IConnection {
public:
	void Move(int x, int y) override {
		throw NetworkException();
	}
};

// 의존성 주입 모델
//   : 제품 코드를 사용하는 방법과 동일하게, 테스트 코드를 작성할 수 있다.
TEST(PlayerTest, BadNetworkMoveTest_UsingStub) {
	StubConnection stub;
	Player player(&stub);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}

// 네트워크 연결이 오류가 발생하였을 때, NetworkException이 외부로 전달되는지 여부를 검증하고 싶다.
TEST(PlayerTest, BadNetworkMoveTest) {
	TCPConnection conn;
	Player player(&conn);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}

















