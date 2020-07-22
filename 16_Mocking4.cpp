#include <stdio.h>
// C++에서 의존성 주입 모델을 구현하는 방법
//  1. 명시적 인터페이스 - struct(class)
//   => 실행 시간에 정책을 교체하는 것이 가능하다.
//   => 가상 함수를 통해 처리되기 때문에, 상대적으로 느리다.
struct Packet {};
struct IPacketStream {
	virtual ~IPacketStream() {}

	virtual void AppendPacket(Packet* new_packet) = 0;
	virtual const Packet* GetPacket(size_t packet_number) const = 0;
};

class ConcreatePacketStream : public IPacketStream {
public:
	void AppendPacket(Packet* new_packet) override {
		printf("ConcreatePacketStream::AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const override {
		printf("ConcreatePacketStream::GetPacket\n");
	}
};

class PacketReader {
public:
	void ReadPacket(IPacketStream* stream, size_t packet_number) {
		stream->AppendPacket(nullptr);
		stream->GetPacket(42);
	}
};

//-----------------------
#include <gmock/gmock.h>

class MockPacketStream : public IPacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet), (override));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const, override));
};

TEST(PacketReaderTest, MockTest) {
	PacketReader reader;
	MockPacketStream mock;

	EXPECT_CALL(mock, AppendPacket(nullptr));
	EXPECT_CALL(mock, GetPacket(42));

	reader.ReadPacket(&mock, 42);
}


#if 0
int main() {
	PacketReader reader;
	ConcreatePacketStream stream;

	reader.ReadPacket(&stream, 42);
}
#endif







//  2. 암묵적 인터페이스 - template


