
#include <gmock/gmock.h>

// Template Class
template <typename T>
struct StackInterface {
	virtual ~StackInterface() {}

	virtual int GetSize() const = 0;
	virtual void Push(const T& x) = 0;
};

// Google Mock은 Template Interface를 Mocking 하는 것이 가능합니다.
template <typename T>
class MockStack : public StackInterface<T> {
public:
	MOCK_METHOD(int, GetSize, (), (const, override));
	MOCK_METHOD(void, Push, (const T& x), (override));
};

TEST(StackTest, MockTest) {
	MockStack<int> s;

	s.GetSize();
	s.Push(42);
}
