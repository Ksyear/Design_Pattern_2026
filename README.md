# Design Patterns in C++20

> 디자인 패턴 22종을 C++20으로 구현한 실행 가능한 예제 모음
> 패턴마다 완성 예제와 빈 연습 문제가 한 쌍으로 들어 있다

## 1. 받아서 실행하기

### 준비물

| 항목 | 최소 버전 | 비고 |
|---|---|---|
| C++20 컴파일러 | gcc 10+ / clang 12+ / Apple clang 13+ / MSVC 2019 16.11+ | |
| CMake | 3.16+ | Makefile만 쓸 거면 없어도 된다 |
| 외부 라이브러리 | 없음 | 표준 라이브러리만 쓴다 |

### 받기

```sh
git clone git@github.com:Ksyear/Design_Pattern_2026.git
cd Design_Pattern_2026
```

### Makefile (가장 빠름)

```sh
make                    # 완성 예제 22개 전부 빌드 -> build/bin/
make run-01_Strategy    # 하나만 빌드하고 바로 실행
make 09_Command         # 하나만 빌드
make run-all            # 22개를 순서대로 실행
make ex                 # 연습 스켈레톤 전부 빌드
make clean              # build/ 삭제
```

`run-` 뒤에 붙이는 이름은 폴더 이름과 같다. 전체 목록은 아래 3절의 표에 있다.

```
$ make run-01_Strategy
===== 01_Strategy =====
[물오리] 모습을 보여 줍니다
  날개를 펄럭여 날아갑니다
  꽥꽥
  모든 오리는 물에 뜹니다
...
```

### CMake

```sh
cmake -S . -B build-cmake
cmake --build build-cmake -j4
./build-cmake/bin/01_Strategy

cmake --build build-cmake --target run_all     # 전체 실행
cmake --build build-cmake --target exercises   # 연습 스켈레톤만 빌드
```

### 표준을 바꾸려면

두 곳에 있다. `Makefile`의 `CXXFLAGS`와 `CMakeLists.txt`의 `CMAKE_CXX_STANDARD`다.

예제 코드 자체는 C++20 전용 기능을 쓰지 않으므로 `c++17`로 내려도 경고 없이 그대로 빌드된다.
표준을 올려 둔 이유는 학습용이기 때문이다. `std::variant`나 지정 초기화자처럼
노트에서 대안으로 언급하는 문법을 그 자리에서 바로 시험해 볼 수 있다.

경고 옵션 `-Wall -Wextra -Wpedantic`이 켜져 있고, 완성 예제와 연습 스켈레톤 모두 경고 0개 상태로 유지한다.

## 2. 폴더 구조

```
.
	CMakeLists.txt          새 폴더를 추가하면 자동으로 타깃이 생긴다
	Makefile                cmake 없이 쓰는 최소 빌드
	NN_PatternName/
		main.cpp        진입점 - 객체를 조립하고 호출만 한다
		exercise.cpp    직접 채워 넣는 연습 문제 (빌드는 되지만 내용이 비어 있음)
		<기능>/         클래스마다 .h(선언) + .cpp(정의) 한 쌍
		<기능>/
```

클래스는 **기능별 폴더**로 나뉘고, 한 클래스가 헤더 하나와 구현 하나를 갖는다.
예를 들어 `01_Strategy`는 이렇게 생겼다.

```
01_Strategy/
	main.cpp              조립과 호출만
	fly/                  나는 기능   - FlyBehavior.h + 구상 전략 3개
	quack/                우는 기능   - QuackBehavior.h + 구상 전략 3개
	duck/                 오리 본체   - Duck.* + 구상 오리 3개
```

이렇게 두면 **"무엇이 달라지는 부분인가"가 폴더 이름으로 드러난다.**
`fly/`와 `quack/`은 서로를 전혀 모르고, `duck/`만 둘을 인터페이스로 안다.

- 빌드는 `main.cpp` + 기능 폴더의 모든 `.cpp`를 모아 실행 파일 하나로 묶는다
- 폴더 간 참조는 `-I<패턴폴더>` 덕분에 `#include "fly/FlyBehavior.h"`처럼 쓴다 (`../` 없음)
- 인클루드 가드는 `<폴더>_<파일>_H` 규약을 따른다
- 완성 예제는 패턴의 의도가 드러나는 고전적인 시나리오를 쓴다
- 연습 문제는 다른 도메인이나 C++ 고유의 함정을 다룬다

## 3. 학습 순서

패턴 이름 앞 번호가 곧 권장 순서다. 생성 -> 행동 -> 구조 순이 아니라
**앞 패턴이 뒤 패턴의 밑바탕이 되는 순서**로 배치했다.

| 번호 | 패턴 | 완성 예제 시나리오 | 기능 폴더 |
|---|---|---|---|
| 01 | Strategy | 오리 시뮬레이션 | `duck` `fly` `quack` `guru`¹ |
| 02 | Observer | 기상 스테이션 | `display` `observer` `subject` |
| 03 | Decorator | 커피 주문과 첨가물 | `beverage` `condiment` |
| 04 | Factory Method | 피자 가게 프레임워크 | `chicago` `ny` `pizza` `store` |
| 05 | Abstract Factory | 피자 원재료 공장 | `chicago` `factory` `ingredient` `ny` `pizza` `store` |
| 06 | Builder | 휴가 계획표 | `builder` `director` `plan` |
| 07 | Prototype | 몬스터 레지스트리 | `monster` `registry` |
| 08 | Singleton | 초콜릿 보일러 | `boiler` |
| 09 | Command | IoT 리모컨 | `command` `device` `remote` |
| 10 | Memento | RPG 세이브 슬롯 | `character` `save` |
| 11 | Chain of Responsibility | 메일 분류 | `handler` `mail` |
| 12 | Mediator | 자동화 주택 | `appliance` `mediator` |
| 13 | Adapter | 칠면조를 오리로 | `adapter` `duck` `turkey` |
| 14 | Facade | 홈시어터 | `device` `facade` |
| 15 | Bridge | 리모컨 x TV | `remote` `tv` |
| 16 | Template Method | 커피와 홍차 | `beverage` |
| 17 | Iterator | 자료구조가 다른 두 메뉴의 통합 | `iterator` `menu` `waitress` |
| 18 | Composite | 메뉴 안의 서브메뉴 | `component` `composite` `leaf` |
| 19 | Flyweight | 조경 설계 앱의 나무 | `factory` `flyweight` `forest` |
| 20 | Visitor | 메뉴 영양 정보 | `element` `visitor` |
| 21 | State | 뽑기 기계 | `machine` `state` |
| 22 | Proxy | 앨범 커버 뷰어 | `image` `person` `proxy` |

¹ `01_Strategy/guru/` 는 같은 패턴을 GoF 교과서 용어로 다시 쓴 것이다.
**도메인 언어**(`Duck`/`fly`)로 쓸 때와 **패턴 용어**(`Context`/`Strategy`)로 쓸 때의
차이를 한 실행 파일 안에서 비교하려고 나란히 뒀다.

## 4. 패턴 하나를 공부하는 법

1. `NN_PatternName/main.cpp`를 실행해 출력부터 본다
2. `main.cpp`의 머리말 주석이 폴더 지도를 알려 준다.
   그다음 인터페이스 헤더 -> 구상 클래스 -> `main.cpp` 순으로 읽으면 된다.
   폴더 이름이 곧 패턴 참여자의 역할과 대응된다
3. `exercise.cpp`의 TODO를 직접 채운다
4. 아래 5절의 C++ 고유 주의점으로 돌아와 자기 코드를 점검한다

## 5. 자바 구현을 C++로 옮길 때 달라지는 점

패턴 설명은 대개 자바를 기준으로 쓰여 있어 C++에서는 그대로 옮길 수 없는 부분이 있다.

| 주제 | 자바 | 이 저장소의 C++ |
|---|---|---|
| 소유권 | GC가 알아서 처리 | `unique_ptr` 소유 / `shared_ptr` 공유 / 원시 포인터는 비소유 참조 |
| 인터페이스 | `interface` | 순수 가상 소멸자를 가진 추상 클래스 |
| 가상 소멸자 | 필요 없음 | 다형적 기반 클래스에는 **반드시** `virtual ~T() = default` |
| 슬라이싱 | 없음 | 값으로 복사하면 파생 정보가 잘림 -> 기반 클래스는 포인터/참조로만 다룸 |
| 복제 | `clone()` + `Cloneable` | 가상 `clone()`이 `unique_ptr<Base>`를 반환 (07_Prototype) |
| 싱글턴 스레드 안전성 | DCL, `volatile`, enum 싱글턴 | 함수 지역 `static` 하나로 끝 (08_Singleton) |
| final 메소드 | `final` | 템플릿 메소드는 `virtual`을 안 붙이면 됨 (16_TemplateMethod) |
| 내부 클래스 접근 | 중첩 클래스가 바깥을 봄 | 중첩 클래스 + `friend` (10_Memento) |
| 다중 상속 | 불가 (인터페이스만) | 가능 -> 클래스 어댑터를 만들 수 있음 (13_Adapter) |
| 반복자 | `Iterator` 인터페이스 | STL 반복자 규약(`begin`/`end`)이 이미 이 패턴 (17_Iterator) |
| 필드 초기화 | `protected` 필드에 서브클래스가 대입 | **생성자 주입 + `private`** (아래 참고) |

### 캡슐화 규약 - 흔한 자바 구현과 의도적으로 다른 부분

자바 구현은 기반 클래스의 필드를 `protected` 로 열어 두고 서브클래스 생성자 몸통에서 대입하는 경우가 많다.
이 저장소는 그 대신 **기반 클래스 생성자로 넘기고 필드는 `private`** 으로 닫는다.

```cpp
// 흔한 방식 - "전략이 없는 오리"가 잠시 존재할 수 있다
MallardDuck::MallardDuck() : Duck("물오리") {
	flyBehavior_ = std::make_unique<FlyWithWings>();   // protected 필드에 대입
}

// 이 저장소 방식 - 생성이 끝난 순간 이미 완전하다
MallardDuck::MallardDuck()
	: Duck("물오리", std::make_unique<FlyWithWings>(), std::make_unique<Quack>()) {}
```

얻는 것은 **불변식(invariant)** 이다. 전략이 항상 존재하므로
`if (flyBehavior_)` 같은 방어 코드가 사라지고, 서브클래스가 필드를 깨뜨릴 통로도 없다.
`nullptr` 을 넘기면 생성자와 세터가 `std::invalid_argument` 를 던진다.

적용: `01_Strategy` `03_Decorator` `04_FactoryMethod` `07_Prototype` `12_Mediator` `15_Bridge`

**예외 2곳** - 패턴 구조상 서브클래스가 필드를 실제로 써야 해서 `protected` 로 남겼다.

| 위치 | 필드 | 남긴 이유 |
|---|---|---|
| `03_Decorator/condiment/CondimentDecorator.h` | `beverage_` | `Mocha::cost()` 등이 감싼 음료에 위임해야 한다 |
| `05_AbstractFactory/pizza/Pizza.h` | `dough_` 등 | `CheesePizza::prepare()` 가 어떤 재료를 주문할지 스스로 정한다 |

## 6. 표준 라이브러리에 이미 들어 있는 패턴

패턴은 발명이 아니라 발견이다. 표준 라이브러리에서 찾아보면 이해가 빨라진다.

- 전략: `std::sort`의 비교자, `std::function`
- 반복자: 모든 컨테이너의 `begin()` / `end()`
- 프록시: `std::shared_ptr`, `std::unique_ptr`, `std::vector<bool>::reference`
- 팩토리 메소드: `std::make_unique`, `std::make_shared`
- 어댑터: `std::stack`, `std::queue`, `std::priority_queue` (표준이 대놓고 container adaptor라 부름)
- 비지터: `std::visit` + `std::variant`
- 옵저버: 표준에는 없음 -> 02_Observer에서 직접 만드는 이유
