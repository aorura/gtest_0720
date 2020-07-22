#include <stdio.h>

//  2. 암묵적 인터페이스 - template
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

int main() {
	PacketReader<ConcreatePacketStream> reader;
	ConcreatePacketStream stream;

	reader.ReadPacket(&stream, 42);
}









