#include <stdio.h>
// C++에서 의존성 주입 모델을 구현하는 방법
//  1. 명시적 인터페이스 - struct(class)
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

int main() {
	PacketReader reader;
	ConcreatePacketStream stream;

	reader.ReadPacket(&stream, 42);
}







//  2. 암묵적 인터페이스 - template


