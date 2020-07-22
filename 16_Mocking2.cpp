#include <gmock/gmock.h>

struct Element {};

class Foo {
public:
	virtual ~Foo() {} 
	// 상속을 기반으로 코드가 구현되어 있다면, 반드시 가상 소멸자를 제공해야 합니다.

	virtual int Add() { printf("Foo:Add()\n"); }
	virtual int Add(Element x) { printf("Foo::Add(Element)\n"); }
	virtual int Add(int times, Element x) {
		printf("Foo::Add(int, Element)\n");
	}
};

// 핵심: 모의 객체 안에서 Mocking을 수행한 메소드는 더이상 실제 메소드를 호출하지 않는다.
//------
class MockFoo : public Foo {
public:
	// 의도: Add(int, Element)에 대해서만, 행위 기반 검증을 수행하고,
	//       나머지 Add는 부모의 구현을 그대로 이용하고 싶다.
	MOCK_METHOD(int, Add, (int times, Element x), (override));

	using Foo::Add;  // 명시적인 선언이 필요하다.
	
#if 0
	int Add(int times, Element x) override {
		printf("MockFoo::Add\n");
	}
#endif
};


TEST(FooTest, MockTest) {
	MockFoo mock;

	mock.Add();                
	mock.Add(Element());
	mock.Add(42, Element());
}
