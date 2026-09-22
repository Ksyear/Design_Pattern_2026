# 01. Strategy - 주행 컨트롤러 플러그인 교체

> "경로를 어떻게 따라갈 것인가" 와 "계산한 속도를 그대로 내보낼 것인가" 를
> 각각 따로 갈아 끼운다. 서버 코드는 한 줄도 바뀌지 않는다.
>
> 책 예제 : [`../../01_Strategy`](../../01_Strategy) (오리 시뮬레이션)

## 1. 어떤 문제를 푸는가

로봇 한 대가 상황에 따라 다른 주행 방식을 쓴다.
평소에는 Pure Pursuit, 좁은 곳에서는 DWB, 장애물 앞에서는 정지다.
여기에 "사람이 많은 구역에서는 0.2m/s 이하" 같은 속도 정책이 또 따로 붙는다.

이걸 `if (mode == PURE_PURSUIT) ... else if` 로 짜면 두 가지가 무너진다.

- 컨트롤러를 하나 추가할 때마다 제어 루프를 연다 (닫혀 있어야 할 코드다)
- 주행 방식 3종 x 속도 정책 3종 = 조합 9개를 전부 코드에 적어야 한다

그래서 **변하는 두 가지를 각각 인터페이스로 뽑아 서버가 "들고 있게"** 했다.
3 + 3 = 6개 클래스로 끝나고, 9개 조합은 실행 중에 만들어진다.

## 2. 폴더가 곧 패턴 역할

| 폴더 / 파일 | 패턴 역할 | 하는 일 |
|---|---|---|
| [`server/ControllerServer.h`](server/ControllerServer.h) | **Context** | 전략 둘을 `unique_ptr` 로 들고 위임만 한다 |
| [`controller/ControllerPlugin.h`](controller/ControllerPlugin.h) | **Strategy 인터페이스 (축 1)** | `computeVelocity(pose, goal, scan) -> Twist` |
| [`controller/PurePursuitController.*`](controller/PurePursuitController.h) | Concrete Strategy | 방향 오차 비례 제어, 오차 크면 감속 |
| [`controller/DwbController.*`](controller/DwbController.h) | Concrete Strategy | 후보 속도에 점수를 매겨 최고점 선택 |
| [`controller/StopController.*`](controller/StopController.h) | Concrete Strategy (Null Object) | 무조건 0 - "컨트롤러 없음" 분기를 없앤다 |
| [`filter/SpeedFilter.h`](filter/SpeedFilter.h) | **Strategy 인터페이스 (축 2)** | `apply(raw) -> Twist` |
| [`filter/NoSpeedLimit.*`](filter/NoSpeedLimit.h) | Concrete Strategy | 그대로 통과 (기본값 자리) |
| [`filter/SlowZoneFilter.*`](filter/SlowZoneFilter.h) | Concrete Strategy | 선속도 상한을 내린다 |
| [`filter/EmergencyBrakeFilter.*`](filter/EmergencyBrakeFilter.h) | Concrete Strategy | 무엇을 계산했든 0 으로 덮는다 |
| [`msg/Types.h`](msg/Types.h) | (데이터) | `Twist` / `Pose2D` / `LaserScan` - `.cpp` 짝이 없다 |

`controller/` 와 `filter/` 는 **서로를 전혀 모른다.** 둘을 아는 곳은 `server/` 하나뿐이고,
그나마도 인터페이스 이름만 안다.

## 3. 적용 방식 - 제어 루프에 알고리즘이 없다

```cpp
// server/ControllerServer.cpp
void ControllerServer::controlLoop(const Pose2D& pose, const Pose2D& goal, const LaserScan& scan) const
{
	const Twist raw = plugin_->computeVelocity(pose, goal, scan);  // 어떻게 갈지 - 전략 1
	const Twist cmd = filter_->apply(raw);                         // 내보낼지   - 전략 2
	publishCmdVel(cmd);
}
```

세 줄이 전부다. `server/` 의 **코드**에는 `PurePursuit`, `DWB`, `Stop` 이라는 이름이
한 번도 나오지 않는다 (그 사실을 짚는 헤더 주석 한 줄에만 등장한다).
어떤 구현이 꽂혀 있는지는 조립하는 쪽([`main.cpp`](main.cpp))만 안다.

교체는 세터로 한다. 상속으로 행동을 물려받았다면 불가능한 지점이다.

```cpp
server.setSpeedFilter(std::make_unique<SlowZoneFilter>(0.2));  // 주행 방식은 그대로
server.setPlugin(std::make_unique<StopController>());          // 속도 정책은 그대로
```

### 불변식으로 방어 코드를 없앴다

생성자와 세터 양쪽에서 `nullptr` 을 거부한다([`ControllerServer.cpp`](server/ControllerServer.cpp)).
그래서 `controlLoop` 안에 `if (plugin_)` 이 필요 없다.
"전략은 항상 존재한다" 를 타입이 아니라 **불변식으로 보장**한 것이다.

## 4. 실행하면 보이는 것

```
===== 2. 사람이 많은 구역 진입 - 속도 정책만 교체 =====
  [param] speed_filter     : none -> slow-zone
  [deliverybot] /cmd_vel  linear.x= 0.20  angular.z= 0.46   (plugin=RegulatedPurePursuit, filter=slow-zone)

===== 5. 비상 정지 - 컨트롤러는 그대로 두고 출력만 막는다 =====
  [param] speed_filter     : none -> e-stop
  [deliverybot] /cmd_vel  linear.x= 0.00  angular.z= 0.00   (plugin=DWBLocalPlanner, filter=e-stop)
```

2번 장면에서 `angular.z` 가 **0.46 그대로**인 것이 핵심이다.
속도 정책을 갈았는데 주행 방식은 영향을 받지 않았다 - 축이 정말로 분리되어 있다는 증거다.

## 5. 실제 ROS 2 대응

| 이 예제 | 실제 ROS 2 |
|---|---|
| `ControllerPlugin` | `nav2_core::Controller` (순수 가상 인터페이스) |
| `computeVelocity()` | `computeVelocityCommands()` |
| `ControllerServer` | `nav2_controller` 의 controller_server 노드 |
| `setPlugin()` | pluginlib 로더 + `FollowPath.plugin` 파라미터 |
| `publishCmdVel()` | `/cmd_vel` 토픽 퍼블리시 |
| `SpeedFilter` | `nav2_costmap_2d` 의 Speed Filter 플러그인 |
| 3번 장면의 판단 | 비헤이비어 트리(BT)가 컨트롤러/복구 동작을 바꿔 끼운다 |

Nav2 가 `.so` 를 런타임에 로드해서 하는 일을, 여기서는 `make_unique` 로 한다.
**로딩 방식만 다르고 구조는 같다.**

## 6. 설계 판단 - 왜 여기에 뒀는가

`StopController` 와 `EmergencyBrakeFilter` 는 결과가 똑같이 0 인데 자리가 다르다.

| | 어디에 있나 | 의미 |
|---|---|---|
| `StopController` | 축 1 (주행 방식) | "목표를 향한 판단을 포기한다" |
| `EmergencyBrakeFilter` | 축 2 (출력 정책) | "컨트롤러는 계속 계산 중인데 출력만 막는다" |

성능 문제가 아니라 **책임 배분**의 문제다.
실제 로봇의 하드웨어 E-stop 은 후자에 가깝다 - 소프트웨어가 뭘 시키든 전원을 끊는다.

## 7. 이 예제가 하지 않는 것

- Pure Pursuit / DWB 를 정확히 구현하지 않는다. 구조가 보일 만큼만 줄였다
- 실제 `nav2_core::Controller` 에 있는 `configure()` / `activate()` /
  `setPlan()` 등은 뺐다. "속도를 계산한다" 하나만 남겼다
- pluginlib 도, `.so` 로딩도 없다

## 8. 객체지향 관점 - 어떤 원칙을 어떻게 지켰나

| 원칙 | 이 예제에서 어떻게 했나 |
|---|---|
| **캡슐화** - 바뀌는 부분을 분리한다 | 변하는 것이 둘이다. 주행 방식은 `ControllerPlugin` 뒤로, 속도 정책은 `SpeedFilter` 뒤로 각각 뺐다 |
| **상속보다 구성** | 서버가 전략을 **들고 있다**(has-a). 물려받았다면 실행 중 교체가 불가능하다 |
| **구현이 아닌 인터페이스** | `ControllerServer` 의 멤버 타입이 전부 추상 클래스다 |
| **OCP** | 컨트롤러를 추가해도 `server/` 는 0줄 바뀐다. 확장엔 열리고 변경엔 닫혔다 |

**C++ 문법으로 지킨 것**

- `virtual ~ControllerPlugin() = default` - 다형적 기반 클래스에는 가상 소멸자가 필수다
- `unique_ptr` 멤버 = 소유. 세터에서 `std::move` 하면 옛 전략이 그 자리에서 파괴된다
- 멤버를 `protected` 가 아니라 `private` 로 - 파생 클래스에게도 열지 않는다
- 생성자·세터의 `nullptr` 거부가 **불변식**이 되어 `controlLoop` 에서 방어 코드를 지웠다

**거스른 것 / 대가**

- 조립 지식이 클라이언트로 옮겨 갔다. `main.cpp` 는 구상 클래스를 전부 안다
- 전략 축이 늘면 인터페이스도 함께 는다

## 9. 실행

```sh
make run-robot-01_Strategy
```

## 10. 확인 질문

> `server/` 폴더의 코드에서 구상 클래스 이름이 몇 번 나오는가?

0번이다 (주석 제외). 1번이라도 나온다면 아직 구현에 묶여 있는 것이다.
