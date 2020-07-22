
#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual int Do(const char* str) {
		printf("Foo::Do - %s\n", str);
		return 0;
	}
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(int, Do, (const char* str), (override));

	// 부모의 기능을 호출하는 함수를 제공해주어야 합니다.
	int DoImpl(const char* str) {
		return Foo::Do(str);
	}
};

TEST(FooTest, Do) {
	// ON_CALL을 이용해서, Do의 호출이, Foo::Do를 이용하도록 하고 싶다.
	MockFoo mock;
	ON_CALL(mock, Do).WillByDefault([&mock](const char* str) {
		// 재귀 호출이 발생합니다.
		return mock.DoImpl(str);
	});

	mock.Do("hello");
}
