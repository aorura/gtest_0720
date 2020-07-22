
#include <stdio.h>

class Animal {
public:
	virtual ~Animal() { printf("~Animal()\n"); }

	virtual void Cry() { printf("Animal Cry\n"); }  // 1
};


class Dog : public Animal {
public:
	~Dog() { printf("~Dog()\n"); }
	void Cry() { printf("Dog Cry\n"); } // 2
};

// 함수 호출 - 바인딩
//   정적 바인딩 - 컴파일 타임에 어떤 함수를 호출할지 결정하는 것
//   동적 바인딩 - 실행 시간에 객체의 타입을 판단해서, 객체의 함수를 호출하는 것
//
// 가상 소멸자
//  - 소멸자는 정적 바인딩을 합니다.


int main() {
	Animal* p = new Dog;   // Ok!

	p->Cry();

	delete p;
}
