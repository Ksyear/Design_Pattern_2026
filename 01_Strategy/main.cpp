// 전략 패턴 (Strategy) - 헤드 퍼스트 1장 SimUDuck 오리 시뮬레이션
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   fly/    나는 기능   - FlyBehavior.h(인터페이스) + 구상 전략 3개
//   quack/  우는 기능   - QuackBehavior.h(인터페이스) + 구상 전략 3개
//   duck/   오리 본체   - Duck.*(Context) + 구상 오리 3개
//   guru/   비교용      - refactoring.guru 의 GoF 교과서형 예제
//
// 기능 폴더가 나뉘어 있으면 "무엇이 달라지는 부분인가"가 폴더 이름으로 드러난다.
// fly/ 와 quack/ 은 서로를 전혀 모르고, duck/ 만 둘을 인터페이스로 안다.
//
// guru/ 를 나란히 둔 이유: 같은 패턴을 '도메인 언어(Duck/fly)'로 쓸 때와
// '패턴 용어(Context/Strategy)'로 쓸 때가 어떻게 다른지 한 실행 파일에서 비교하기 위해서.
//
// main 은 세 장면을 차례로 보여 준다.
//   1) 오리별 기본 행동      - 구성으로 조립된 전략이 무엇인지
//   2) 실행 중 전략 교체      - 상속으로는 불가능한 지점
//   3) Duck 형식만 보고 순회  - '인터페이스에 맞춰 프로그래밍한다' 원칙
#include <iostream>
#include <memory>
#include <vector>

#include "duck/Duck.h"
#include "duck/MallardDuck.h"
#include "duck/ModelDuck.h"
#include "duck/RubberDuck.h"
#include "fly/FlyRocketPowered.h"
#include "guru/ClientCode.h"
#include "quack/MuteQuack.h"

int main()
{
	MallardDuck mallard;
	mallard.display();
	mallard.performFly();
	mallard.performQuack();
	mallard.swim();

	std::cout << '\n';

	RubberDuck rubber;
	rubber.display();
	rubber.performFly();
	rubber.performQuack();

	std::cout << '\n';

	// 여기가 전략 패턴의 하이라이트 : 실행 중 전략 교체
	ModelDuck model;
	model.display();
	model.performFly(); // 못 남
	model.setFlyBehavior(std::make_unique<FlyRocketPowered>());
	model.performFly(); // 로켓 장착 후 날아감
	model.setQuackBehavior(std::make_unique<MuteQuack>());
	model.performQuack();

	// 원칙 확인 : "구현이 아닌 인터페이스(상위 형식)에 맞춰 프로그래밍한다"
	//
	// 아래 루프에는 MallardDuck / RubberDuck / ModelDuck 이라는 이름이 없다.
	// 아는 것은 Duck 이라는 상위 형식 하나뿐 -> 오리 종류가 몇 개로 늘어나든
	// 이 루프는 한 글자도 바뀌지 않는다. 위의 개별 호출과 대비해서 볼 것.
	//
	// 전략 패턴의 두 축이 여기서 같이 드러난다.
	//   세로축(상속) : Duck* 하나로 여러 구상 오리를 다룸        -> 다형성
	//   가로축(구성) : 같은 Duck 이 서로 다른 행동을 들고 있음  -> 전략
	//
	// 주의 : 여기 모형 오리는 위에서 로켓을 달았던 그 객체가 아니라 새 객체다.
	//        그래서 다시 기본 전략(못 남 / 꽥꽥)으로 돌아와 있다
	//        -> 전략 교체는 '클래스'가 아니라 '객체 하나'의 상태를 바꾼 것이었다는 증거.
	std::cout << "\n===== 다형성: Duck 형식만 보고 순회 =====\n";
	std::vector<std::unique_ptr<Duck>> ducks;
	ducks.push_back(std::make_unique<MallardDuck>());
	ducks.push_back(std::make_unique<RubberDuck>());
	ducks.push_back(std::make_unique<ModelDuck>());

	for (const std::unique_ptr<Duck> &duck : ducks)
	{
		duck->display();
		duck->performFly();
		duck->performQuack();
		std::cout << '\n';
	}

	// 같은 패턴을 GoF 교과서 형태로 쓰면 이렇게 된다 (guru/ 폴더)
	std::cout << "===== 비교: refactoring.guru 스타일 =====\n";
	guru::clientCode();

	return 0;
}
