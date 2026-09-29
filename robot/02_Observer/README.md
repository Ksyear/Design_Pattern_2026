# 02. Observer - `/battery_state` 토픽 pub / sub

> ROS 2 의 토픽이 곧 이 패턴이다. 배터리 값 하나가 올라오면
> 도킹 매니저 · 로거 · 관제 화면이 각자 알아서 반응한다.
>
> 소스에는 주석이 없다. 설명은 전부 이 문서에 있다.
>
> 책 예제 : [`../../02_Observer`](../../02_Observer) (기상 스테이션) | 상위 문서 : [`../README.md`](../README.md)

## 1. 어떤 문제를 푸는가

배터리 상태를 필요로 하는 노드가 여러 개다. 그리고 계속 늘어난다.

- 도킹 매니저 : 20% 이하면 충전소로 복귀 요청
- 로거 : 전부 기록
- 관제 화면 : 게이지 표시
- (내일 추가될) 수명 예측, 발열 감시, ...

퍼블리셔가 이 목록을 알고 있으면 구독자가 늘 때마다 퍼블리셔를 고쳐야 한다.
그래서 **"관심 있는 쪽이 등록하고, 퍼블리셔는 인터페이스에만 대고 뿌린다"** 로 뒤집었다.

## 2. 폴더가 곧 패턴 역할

| 폴더 / 파일 | 패턴 역할 | 하는 일 |
|---|---|---|
| [`subject/Publisher.h`](subject/Publisher.h) | **Subject 인터페이스** | `subscribe` / `unsubscribe` / `notify` |
| [`subject/BatteryPublisher.*`](subject/BatteryPublisher.h) | **Concrete Subject** | 값을 보관하고 바뀌면 전부에게 전달 |
| [`observer/Subscriber.h`](observer/Subscriber.h) | **Observer 인터페이스** | `onMessage(const BatteryState&)` - 곧 구독 콜백 |
| [`observer/DockingManager.*`](observer/DockingManager.h) | Concrete Observer | 임계값 이하 → 복귀 요청 (상태를 기억한다) |
| [`observer/StatusLogger.*`](observer/StatusLogger.h) | Concrete Observer | 받은 것을 그대로 기록 (rosbag / `/diagnostics` 자리) |
| [`observer/FleetDashboard.*`](observer/FleetDashboard.h) | Concrete Observer | 막대 게이지로 표시 (rviz 패널 자리) |
| [`msg/BatteryState.h`](msg/BatteryState.h) | (데이터) | `sensor_msgs/msg/BatteryState` 를 줄인 것 |

`msg/BatteryState.h` 의 필드와 단위는 실제 메시지 정의를 따른다.

| 필드 | 단위 / 범위 |
|---|---|
| `percentage` | `0.0 ~ 1.0` (100 분율이 아니다) |
| `voltage` | V |
| `current` | A - **음수 = 방전 중**, 양수 = 충전 중 |

`FleetDashboard` 는 나중에 추가된 구독자라고 생각하고 읽으면 된다.
이것을 추가해도 `BatteryPublisher` 는 한 줄도 바뀌지 않는다 - 그것이 이 패턴을 쓰는 이유다.

## 3. 적용 방식 - 밀어 넣기(push)와 끌어오기(pull)를 둘 다 뒀다

```cpp
// subject/BatteryPublisher.cpp
void BatteryPublisher::notify()
{
	for (Subscriber* sub : subscribers_) {
		sub->onMessage(state_);   // push : 메시지를 통째로 밀어 준다
	}
}
```

(이 문서의 코드 조각에 붙은 `//` 주석은 설명하려고 여기에만 붙인 것이다. 실제 소스에는 없다.)

`onMessage(state_)` 로 값을 **밀어 넣는다**. ROS 2 토픽이 이 방식이다.
동시에 `state()` 게터도 열어 뒀다 - 구독자가 필요할 때 **끌어올** 수도 있다.
책 예제에서 두 방식을 비교하던 그 자리다.

### 핵심은 원시 포인터다

```cpp
std::vector<Subscriber*> subscribers_;   // 비소유 포인터 목록
```

`unique_ptr` 도 `shared_ptr` 도 아니다. 의도적이다.

> **퍼블리셔는 구독자를 소유하지 않는다.**
> 각 구독자는 자기 노드가 소유하고, 퍼블리셔는 "누가 듣고 있는지" 만 안다.

ROS 2 도 똑같다. 퍼블리셔는 누가 듣는지 모르고 구독자의 수명도 관리하지 않는다.
이 저장소의 규약 - **원시 포인터 = 비소유 참조** - 가 그대로 들어맞는 자리다.

대가로 규칙이 하나 생긴다. **구독자가 먼저 죽으면 반드시 `unsubscribe` 해야 한다.**
[`main.cpp`](main.cpp) 에서 구독자 셋을 전부 `main` 스코프에 둔 것은 이 규칙을 지키기 위해서다.

## 4. 실행하면 보이는 것

```
  publish 18%  <- 도킹 매니저만 반응한다
    [docking_manager] 배터리 18% - 내비게이션 중단하고 충전 스테이션으로 복귀 요청
    [status_logger] #3  22.1V  -3.4A  18.0%
    [fleet_dashboard] [##........]

===== 3. 구독 해지 - 관제 화면을 껐다 =====
  [topic] /battery_state <- fleet_dashboard 구독 해지
  publish 15%
    [status_logger] #4  21.8V  -3.5A  15.0%
```

- 같은 메시지 하나에 셋이 **서로 다르게** 반응한다. 퍼블리셔는 그 차이를 모른다
- 해지 후에는 대시보드 줄이 사라진다. 나머지 둘은 영향이 없다
- 80% / 45% 에서 도킹 매니저가 조용한 이유는 `dockRequested_` 로 **상태를 기억**하기 때문이다.
  옵저버가 무상태일 필요는 없다

## 5. 대응표

### 책 예제 ↔ 이 예제

| 책 (기상 스테이션) | 여기 |
|---|---|
| `Subject` | `Publisher` |
| `WeatherData` | `BatteryPublisher` - 값이 바뀌면 알린다 |
| `Observer::update(temp, humidity, pressure)` | `Subscriber::onMessage(const BatteryState&)` - 값 셋을 메시지 하나로 묶었다 |
| `registerObserver` / `removeObserver` / `notifyObservers` | `subscribe` / `unsubscribe` / `notify` |
| `setMeasurements()` | `publish()` |
| `CurrentConditionsDisplay` 등 3종 | `DockingManager` / `StatusLogger` / `FleetDashboard` |
| `std::vector<std::weak_ptr<Observer>>` | `std::vector<Subscriber*>` - 비소유라는 점은 같고, 죽은 구독자를 **스스로 걸러내지는 못한다** |

### 이 예제 ↔ 실제 ROS 2

| 이 예제 | 실제 ROS 2 |
|---|---|
| `subscribe(&docking)` | `create_subscription<BatteryState>("battery_state", 10, cb)` |
| `unsubscribe(&dashboard)` | `subscription.reset()` |
| `publish(msg)` → `notify()` | `publisher->publish(msg)` |
| `Subscriber::onMessage()` | 구독 콜백 (rclcpp 에서는 보통 람다 한 줄) |
| `std::vector<Subscriber*>` | DDS 미들웨어가 들고 있는 구독자 목록 |

rclcpp 에서는 `Subscriber` 클래스 자리가 람다 한 줄이다. **콜백이 클래스로 올라온 것뿐, 구조는 똑같다.**

```cpp
subscription_ = create_subscription<BatteryState>("battery_state", 10,
    [this](BatteryState::SharedPtr msg) { ... });
```

해지도 모양만 다르다. `create_subscription()` 은 구독 핸들을 `SharedPtr` 로 돌려주고,
그 핸들을 `reset()` 하면 해지된다. 여기서는 그 일을 `unsubscribe()` 가 맡는다.

**한 가지가 다르다.** 여기서는 퍼블리셔가 구독자 포인터를 직접 들고 있지만,
ROS 2 는 중간에 DDS 가 끼어서 **양쪽이 서로를 전혀 모른다.** 결합도가 한 단계 더 낮다.
그래서 노드를 다른 머신에 띄워도 코드가 그대로다.

## 6. 이 예제가 드러내는 함정

[`subject/BatteryPublisher.cpp`](subject/BatteryPublisher.cpp) 의 `notify()`

```cpp
for (Subscriber* sub : subscribers_) {
	sub->onMessage(state_);   // 이 안에서 unsubscribe(this) 를 부르면?
}
```

**순회 중에 구독자가 자기 자신을 해지하면 반복자가 깨진다.**
`onMessage` 안에서 `unsubscribe` 를 부르면 `subscribers_` 에서 `erase` 가 일어나고,
순회하던 반복자가 무효화된다.
실제 코드라면 복사본을 떠서 돌거나 지연 삭제 큐를 쓴다.
**이 예제는 일부러 고치지 않았다** - 옵저버를 직접 만들 때 가장 자주 밟는 지뢰라서다.

## 7. 이 예제가 하지 않는 것

- DDS 도, QoS 도, 직렬화도 없다. 같은 프로세스 안의 직접 호출이다
- 스레드 안전성을 고려하지 않았다. 실제 ROS 2 콜백은 실행기(executor) 스레드에서 돈다
- 메시지 큐가 없다. `publish` 는 즉시 동기 호출이다

## 8. 객체지향 관점 - 어떤 원칙을 어떻게 지켰나

| 원칙 | 이 예제에서 어떻게 했나 |
|---|---|
| **느슨한 결합** | 이 패턴의 존재 이유. 퍼블리셔가 구독자에 대해 아는 것은 `Subscriber` 인터페이스뿐이다 |
| **OCP** | 구독자를 추가해도 `subject/` 는 0줄 바뀐다 |
| **구현이 아닌 인터페이스** | 목록의 타입이 `std::vector<Subscriber*>` 다 |

**C++ 문법으로 지킨 것**

- **원시 포인터 = 비소유.** 수명은 각 구독 노드가 갖는다는 것을 타입으로 말한다
- `onMessage(const BatteryState&)` - 복사 없이 읽기 전용으로 넘긴다
- 가상 소멸자로 다형적 삭제를 안전하게

**거스른 것 / 대가**

- 수명 규칙이 **사람 손에 남는다.** 구독자가 먼저 죽으면 반드시 `unsubscribe` 해야 한다
- 통지 순서가 보장되지 않고, 순회 중 해지(재진입)에 취약하다 - 6절에 적어 둔, 일부러 남긴 결함

## 9. 자주 나오는 오해 - 문답으로 정리

옵저버는 설명을 들으면 다 아는 것 같은데, **말로 해 보면 어긋나는** 패턴이다.
실제로 오간 질문과 그 교정을 그대로 옮겼다.

### Q1. "객체 구조는 모르겠고, 목록에 있으면 값을 그대로 전달한다" 가 맞나

**동작은 정확히 그렇다.**

```cpp
void BatteryPublisher::publish(const BatteryState& msg)
{
	state_ = msg;   // 받은 값을 그대로 저장하고
	notify();       // 그 자리에서 바로 뿌린다
}

void BatteryPublisher::notify()
{
	for (Subscriber* sub : subscribers_) {
		sub->onMessage(state_);   // 목록에 있으면 무조건, 전원에게 같은 값
	}
}
```

선별도 가공도 없다. **목록에 있다는 것이 유일한 자격 조건**이고,
받아서 무엇을 하든 퍼블리셔는 관심이 없다.

**다만 "구조를 모른다" 는 틀렸다.** 구상 타입을 모르는 것이지 구조를 모르는 것이 아니다.
아무것도 모르면 `sub->onMessage(...)` 라고 쓸 수조차 없다.
퍼블리셔가 구독자에 대해 아는 것은 정확히 둘이다.

```cpp
virtual void onMessage(const BatteryState& msg) = 0;   // notify() 에서 호출
virtual std::string name() const = 0;                  // 구독 / 해지 로그에서 호출
```

> **구상 타입은 모르고, 인터페이스는 정확히 안다.**

### Q2. 그럼 "이름 말고는 아무것도 모른다" 인가

방향은 맞는데 꼽은 것이 반대다.

| 퍼블리셔가 **아는** 것 | 퍼블리셔가 **모르는** 것 |
|---|---|
| 이 객체에게 `onMessage(BatteryState)` 를 **부를 수 있다** | 그 안에서 무슨 일이 벌어지는지 |
| 이름을 물어볼 수 있다 | 구상 타입 · 결과 · 실패 여부 |

한 줄로 줄이면 이렇다.

> **"무엇을 할 수 있나" 는 알고, "무엇을 하나" 는 모른다.**

그리고 `name()` 은 **곁가지**다. 이 예제가 로그를 찍으려고 넣은 것이라 지워도 패턴은 성립한다.
`onMessage` 를 지우면 옵저버가 사라진다. **본체는 `onMessage` 하나다.**

### Q3. "나랑 쟤랑 연결되어 있다" - 양방향인가

**아니다. 화살표가 한 방향뿐이다.**

`observer/` 폴더에 `BatteryPublisher` 를 가리키는 멤버가 0개다.

```cpp
class DockingManager : public Subscriber {
private:
	double threshold_;
	bool dockRequested_ = false;   // 퍼블리셔 포인터? 없다
};
```

구독자는 **자기가 누구에게 등록됐는지도 모른다.** 등록조차 자기가 하지 않는다.

```cpp
batteryNode.subscribe(&docking);   // docking 은 이 일이 벌어진 줄도 모른다
```

중재자와 비교하면 선명하다.

| | 02 Observer | 12 Mediator |
|---|---|---|
| A 가 B 를 안다 | 퍼블리셔 → 구독자 | 중재자 → 노드 |
| B 가 A 를 안다 | **모른다** | **안다** (`Mediator* mediator_` 멤버) |

그래서 옵저버가 중재자보다 결합이 **한 단계 더** 느슨하다.

### Q4. "값이 오는 즉시 바로 갱신한다" 가 패턴의 정의인가

아니다. 그것은 **이 구현의 선택**이고, 서로 다른 축이 둘 있다.

| 축 | 이 예제 | 다른 선택 |
|---|---|---|
| 전달 방식 | **push** - 값을 밀어 넣는다 | **pull** - 구독자가 `state()` 로 꺼내 간다 |
| 시점 | **동기** - `publish()` 호출 스택 안에서 즉시 | **비동기** - 큐에 넣고 나중에 |

`BatteryPublisher::state()` 게터가 pull 용 자리다. **둘 다 옵저버다.**

그리고 **실제 ROS 2 는 비동기다.** `publish()` 가 DDS 큐에 넣고 바로 리턴하고,
콜백은 실행기(executor) 스레드가 나중에 돌린다. "바로바로" 가 아니다.
이 예제가 동기인 것은 미들웨어를 빼고 구조만 남겼기 때문이다.

### Q5. 그래서 느슨한 결합이란 무엇인가

맞다. 다만 **결합이 없다는 뜻이 아니다.**

`BatteryState` 에 필드를 하나 추가해 보면 구독자 전원이 다시 컴파일된다 - 결합이 남아 있다.
대신 그 결합점이 **인터페이스 하나**라서, 구독자를 100개로 늘려도 퍼블리셔는 0줄 바뀐다.

> **느슨한 결합 = 결합이 0인 것이 아니라, 결합이 한 점에만 있는 것.**

### 경계선 - 언제 옵저버가 아니게 되는가

정의를 테스트해 보는 것이 이해를 굳히는 데 제일 좋다. 셋 중 하나라도 하면 깨진다.

```cpp
// 1. 골라서 보낸다 -> 옵저버 아님
if (dynamic_cast<DockingManager*>(sub)) { ... }

// 2. 구독자마다 다른 값을 보낸다 -> 이건 12_Mediator 의 일이다
sub->onMessage(customizedFor(sub));

// 3. 구독자의 반환값을 보고 퍼블리셔가 판단한다 -> 결합이 역류한다
if (sub->onMessage(state_) == REJECTED) { ... }
```

`onMessage` 의 반환 타입이 `void` 인 것이 3번을 **문법으로** 막는 장치다.

### 퍼블리셔가 끝까지 모르는 것

- **몇 명인지** - 0명이어도 정상 동작한다
- **순서** - 등록 순서일 뿐 보장이 아니다
- **결과** - 반환이 `void`
- **실패** - `notify()` 에 `try` 가 없어서, 구독자 하나가 예외를 던지면
  **뒤에 있는 구독자들은 값을 못 받는다**

마지막은 실제 결함이다. 순회 중 해지로 반복자가 깨지는 것과 같은 종류 -
옵저버를 직접 만들 때 가장 자주 밟는 지뢰다.

## 10. 실행

### 이 폴더만 단독으로

```sh
cd robot/02_Observer
make          # build/02_Observer 에 실행 파일 생성
make run      # 빌드하고 바로 실행
make clean    # build/ 삭제
```

### 저장소 루트에서 (다른 패턴과 함께)

```sh
make robot                    # 로봇 예제 22개 전부 빌드 -> build/bin/robot_*
make run-robot-02_Observer    # 이 예제만 빌드하고 실행
make run-robot-all            # 22개를 순서대로 실행
```

두 경로의 빌드 옵션은 같다 - `-std=c++20 -Wall -Wextra -Wpedantic -O1`, **경고 0개**를 유지한다.
산출물 위치만 다르다 - 단독은 `02_Observer/build/`, 루트는 `build/bin/`.

## 11. 확인 질문

> `BatteryPublisher.cpp` 에 `docking` / `logger` / `dashboard` 라는 이름이 나오는가?

없다. 그래서 구독자를 하나 더 추가해도 `subject/` 는 한 줄도 바뀌지 않는다 (OCP).
