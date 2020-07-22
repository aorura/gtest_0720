
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

		// ...
	}
};

#include <gmock/gmock.h>

class StubConnection : public IConnection {
public:
	MOCK_METHOD(void, Move, (int x, int y), (override));
};

using testing::NiceMock;
using testing::Throw;
using testing::_;

TEST(PlayerTest, BadNetworkMoveTest_UsingStub) {
	StubConnection stub;
	ON_CALL(stub, Move(_, _)).WillByDefault(Throw(NetworkException()));
	Player player(&stub);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}
