#include <stdio.h>

// SUT
// 주의 사항
//  - 테스트 전용 하위 클래스를 작성하고자 하는 SUT가 상속을 할 수 있도록 설계되어야 한다.
//    1) 가상 소멸자
//    2) 가상 함수 - Start
class Engine {
public:
	virtual ~Engine() {}
	virtual void Start() {
		printf("Engine start...\n");
	}
};

class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	void Go() {
		// ...
		engine->Start();
	}
};

#include <gtest/gtest.h>
// Car의 Go를 호출하였을 때, Engine의 Start가 호출되었는지 여부를 검증하고 싶다.

class TestEngine : public Engine {
	bool isStart;
public:
	TestEngine() : isStart(false) {}

	void Start() override {
		Engine::Start();     // 부모의 기능을 그대로 이용한다.
		isStart = true;
	}

	// 테스트에서 확인할 수 있는 함수를 제공한다.
	bool IsStart() const { return isStart; }
};

TEST(CarTest, GoTest2) {
	TestEngine engine;
	Car car(&engine);

	car.Go();

	EXPECT_TRUE(engine.IsStart()) << "Car가 Go 했을 때";
}

TEST(CarTest, GoTest) {
	Engine engine;
	Car car(&engine);

	car.Go();

}













