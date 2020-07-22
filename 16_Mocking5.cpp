#include <stdio.h>

//  2. 암묵적 인터페이스 - template
//   => 단위 전략(Policy based Design)
//   => 컴파일 타임에 정책의 교체가 발생하기 때문에,
//      런타임에 정책의 교체를 위해서는 별도의 타입을 생성해야한다.
//   => 가상 함수가 아니기 때문에, 인라인화가 가능하다.
struct Packet {};

class ConcreatePacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatePacketStream::AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {
		printf("ConcreatePacketStream::GetPacket\n");
	}
};

template <typename IPacketStream>
class PacketReader {
public:
	void ReadPacket(IPacketStream* stream, size_t packet_number) {
		stream->AppendPacket(nullptr);
		stream->GetPacket(42);
	}
};

#include <gmock/gmock.h>

class MockPacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const));
};

TEST(PacketReaderTest, MockTest) {
	PacketReader<MockPacketStream> reader;
	MockPacketStream mock;

	EXPECT_CALL(mock, AppendPacket(nullptr));
	EXPECT_CALL(mock, GetPacket(42));

	reader.ReadPacket(&mock, 42);
}

#if 0
int main() {
	PacketReader<ConcreatePacketStream> reader;
	ConcreatePacketStream stream;

	reader.ReadPacket(&stream, 42);
}
#endif
