# 01. Strategy - 주행 컨트롤러 플러그인 교체

> 소스에는 주석이 없다. 설명은 전부 이 문서에 있다.
> 코드는 "무엇을 하는가"만 보이고, "왜 그렇게 했는가"는 여기서 읽는다.
>
> 책 예제 : [`../../01_Strategy`](../../01_Strategy) (오리 시뮬레이션) | 상위 문서 : [`../README.md`](../README.md)

---

## 0. 이 프로젝트는 정확히 무엇인가

**ROS 2 Nav2 의 주행 컨트롤러 플러그인 구조를, rclcpp 없이 표준 C++ 만으로 재현한 단일 실행 파일 예제다.**

한 문장으로 줄이면 이렇다.

> 배달 로봇 한 대(`deliverybot`)가 제어 주기마다 `/cmd_vel` 을 계산해 내보내는데,
> **"경로를 어떻게 따라갈지"** 와 **"계산한 속도를 그대로 내보낼지"** 를
> 실행 중에 따로따로 갈아 끼울 수 있게 만든 것.

### 무엇인가 / 무엇이 아닌가

| 이것이다 | 이것이 아니다 |
|---|---|
| ROS 2 의 **구조**를 흉내 낸 학습용 예제 (노드, 토픽, 플러그인) | 실제 ROS 2 패키지가 아니다. `rclcpp` 를 쓰지 않는다 |
| 표준 라이브러리만으로 빌드되는 `main()` 하나짜리 프로그램 | colcon / ament 빌드가 아니다. DDS 통신도 없다 |
| 제어 알고리즘을 **구조가 보일 만큼만** 줄인 것 | Pure Pursuit / DWB 의 정확한 구현이 아니다 |
| 패턴이 실제 Nav2 어디에 대응되는지 짚는 자료 | pluginlib 로 `.so` 를 로드하지 않는다 (`make_unique` 로 대신한다) |

### 시뮬레이션하는 상황

로봇 한 대가 상황에 따라 다른 주행 방식을 쓴다.

- 평소에는 **Pure Pursuit** (목표 방향으로 부드럽게)
- 장애물 앞에서는 **정지**
- 좁은 곳을 빠져나온 뒤에는 **DWB** (후보 속도에 점수를 매겨 선택)

여기에 주행 방식과는 **별개로** 속도 정책이 또 붙는다.

- 사람이 많은 구역에서는 `0.2 m/s` 이하 (서행)
- 비상 상황에서는 무조건 `0` (E-stop)

`main()` 은 이 상황을 6개 장면으로 순서대로 재생한다.

### 이 구조가 없으면 생기는 일

`if (mode == PURE_PURSUIT) ... else if (mode == DWB) ...` 로 짜면 두 가지가 무너진다.

- 컨트롤러를 하나 추가할 때마다 **제어 루프를 연다.** 가장 닫혀 있어야 할 코드다
- 주행 방식 3종 × 속도 정책 3종 = **조합 9개**를 전부 코드에 적어야 한다

그래서 변하는 두 가지를 각각 인터페이스로 뽑아 서버가 **들고 있게** 했다.
`3 + 3 = 6`개 클래스로 끝나고, 9개 조합은 **실행 중에** 만들어진다.

---

## 1. 전략 패턴을 어디에 썼는가

### 한눈에 - 패턴 역할 ↔ 실제 파일

| 패턴 역할 | 이 프로젝트의 그것 | 파일 |
|---|---|---|
| **Context** | `ControllerServer` | [`server/ControllerServer.h`](server/ControllerServer.h) |
| **Strategy 인터페이스 (축 1)** | `ControllerPlugin` | [`controller/ControllerPlugin.h`](controller/ControllerPlugin.h#L12) |
| Concrete Strategy | `PurePursuitController` | [`controller/PurePursuitController.cpp`](controller/PurePursuitController.cpp) |
| Concrete Strategy | `DwbController` | [`controller/DwbController.cpp`](controller/DwbController.cpp) |
| Concrete Strategy (Null Object) | `StopController` | [`controller/StopController.cpp`](controller/StopController.cpp) |
| **Strategy 인터페이스 (축 2)** | `SpeedFilter` | [`filter/SpeedFilter.h`](filter/SpeedFilter.h#L12) |
| Concrete Strategy | `NoSpeedLimit` | [`filter/NoSpeedLimit.cpp`](filter/NoSpeedLimit.cpp) |
| Concrete Strategy | `SlowZoneFilter` | [`filter/SlowZoneFilter.cpp`](filter/SlowZoneFilter.cpp) |
| Concrete Strategy | `EmergencyBrakeFilter` | [`filter/EmergencyBrakeFilter.cpp`](filter/EmergencyBrakeFilter.cpp) |
| **Client (조립하는 쪽)** | `main()` | [`main.cpp`](main.cpp#L21) |
| (데이터 전용, `.cpp` 없음) | `Twist` / `Pose2D` / `LaserScan` | [`msg/Types.h`](msg/Types.h) |

**폴더가 곧 역할이다.** `controller/` 와 `filter/` 는 **서로를 전혀 모르고**,
둘을 아는 곳은 `server/` 하나뿐이며 그나마도 인터페이스 이름만 안다.

### 적용 지점 ① - 인터페이스로 뽑아낸 "달라지는 한 가지"

[`controller/ControllerPlugin.h`](controller/ControllerPlugin.h)

```cpp
virtual Twist computeVelocity(const Pose2D& pose,
                              const Pose2D& goal,
                              const LaserScan& scan,
                              const Twist& current) const = 0;
```

달라지는 부분은 딱 하나다. **같은 `(현재 위치, 목표, 스캔, 현재 속도)` 를 받고도 어떤 속도를 낼지가 구현마다 다르다.**
그 한 줄을 인터페이스 뒤로 뽑아낸 것이 이 패턴의 전부다.

`current` 는 실제 `nav2_core::Controller::computeVelocityCommands()` 가 받는 현재 `twist` 에 해당한다.
DWB 는 이것 없이는 동작할 수 없고(§3), Pure Pursuit 과 Stop 은 쓰지 않는다 —
**인터페이스는 모든 전략의 최대공약수가 아니라 합집합이 된다**는 것이 이 패턴의 값이다.

### 적용 지점 ② - Context 는 들고만 있는다

[`server/ControllerServer.h:30-31`](server/ControllerServer.h#L30-L31)

```cpp
private:
	std::unique_ptr<ControllerPlugin> plugin_;
	std::unique_ptr<SpeedFilter> filter_;
```

상속이 아니라 **구성(has-a)** 이다. 멤버 타입이 둘 다 추상 클래스라는 점이 핵심이다.
`protected` 가 아니라 `private` 인 것도 의도적이다 — 파생 클래스에게도 열지 않는다.

### 적용 지점 ③ - 제어 루프에 알고리즘이 0줄

[`server/ControllerServer.cpp:21-30`](server/ControllerServer.cpp#L21-L30)

```cpp
Twist ControllerServer::controlLoop(const Pose2D& pose,
                                    const Pose2D& goal,
                                    const LaserScan& scan,
                                    const Twist& odom) const
{
	const Twist raw = plugin_->computeVelocity(pose, goal, scan, odom);  // 어떻게 갈지 - 전략 1
	const Twist cmd = filter_->apply(raw);                               // 내보낼지   - 전략 2
	publishCmdVel(cmd);
	return cmd;
}
```

(위 두 줄의 `//` 주석은 설명하려고 여기에만 붙인 것이다. 실제 소스에는 없다.)

네 줄이 전부다. 계산은 한 줄도 없고 **위임과 퍼블리시만** 한다.
퍼블리시한 명령을 돌려주는 것은 `main` 이 그것을 다음 주기의 `odom` 으로 되먹이기 위해서다
(실제 로봇에서는 오도메트리가 그 자리를 맡는다).
`server/` 폴더 전체에 `PurePursuit`, `Dwb`, `Stop` 이라는 이름이 **단 한 번도** 나오지 않는다.

```sh
$ grep -rn "Dwb\|PurePursuit\|Stop" server/
(결과 없음)
```

### 적용 지점 ④ - 실행 중 교체

[`server/ControllerServer.cpp:28`](server/ControllerServer.cpp#L28), [`:37`](server/ControllerServer.cpp#L37)

```cpp
server.setSpeedFilter(std::make_unique<SlowZoneFilter>(0.2));  // 주행 방식은 그대로
server.setPlugin(std::make_unique<StopController>());          // 속도 정책은 그대로
```

**상속으로 행동을 물려받았다면 불가능한 지점이다.** `DwbServer : ControllerServer` 였다면
행동을 바꾸려고 객체를 새로 만들어야 한다. Nav2 로 치면 `FollowPath.plugin` 파라미터를 바꿔 끼우는 것에 해당한다.

### 적용 지점 ⑤ - 조립 지식은 클라이언트에만

[`main.cpp:21-23`](main.cpp#L21-L23)

```cpp
ControllerServer server("deliverybot",
                        std::make_unique<PurePursuitController>(),
                        std::make_unique<NoSpeedLimit>());
```

어떤 구현을 쓸지는 **여기서만** 결정한다.
실제 Nav2 에서 이 자리를 맡는 것이 **pluginlib 로더 + 파라미터 YAML 파일**이다.

---

## 2. 왜 축이 둘인가 - 조합 폭발

책의 오리가 `fly` 와 `quack` 두 축을 따로 들고 있던 것과 같은 자리다.

| | 축 1 : `ControllerPlugin` | 축 2 : `SpeedFilter` |
|---|---|---|
| 묻는 것 | "경로를 **어떻게 따라갈** 것인가" | "계산한 속도를 **그대로 낼** 것인가" |
| 시그니처 | `computeVelocity(pose, goal, scan, current) -> Twist` | `apply(raw) -> Twist` |
| 실제 Nav2 | `nav2_core::Controller` | `nav2_costmap_2d` 의 Speed Filter 플러그인 |

축을 둘로 나눈 이유는 **조합 폭발을 막기 위해서다.**
컨트롤러 3종 × 속도 정책 3종을 상속으로 만들면 클래스가 9개 필요하지만,
구성으로 들고 있으면 **3 + 3 = 6개**로 끝나고 조합은 실행 중에 만들어진다.

---

## 3. 파일별 설명

### `msg/` - 메시지 구조체

ROS 2 메시지를 `rclcpp` 없이 구조만 빌려 왔다.

| 타입 | 원본 | 필드 / 단위 |
|---|---|---|
| `Twist` | `geometry_msgs/msg/Twist` | `linear_x` [m/s], `angular_z` [rad/s] |
| `Pose2D` | `geometry_msgs/msg/PoseStamped` 의 평면 버전 | `x`, `y` [m], `yaw` [rad] |
| `LaserScan` | `sensor_msgs/msg/LaserScan` | `front_range_m` [m] — 정면 최단 거리 **하나로 줄였다** |

이 폴더만 `.cpp` 짝이 없다. **데이터만 있고 동작이 없으니 정의할 것도 없기 때문이다.**

### `controller/` - 주행 전략 축

**`ControllerPlugin`** — 실제 ROS 2 의 `nav2_core::Controller` 자리다.
진짜 Nav2 인터페이스에는 `configure()` / `activate()` / `deactivate()` / `cleanup()` /
`setPlan()` / `setSpeedLimit()` / `computeVelocityCommands()` 가 들어 있다.
여기서는 패턴만 남기려고 **"속도를 계산한다" 하나로** 줄였다.

**`PurePursuitController`** — `nav2_regulated_pure_pursuit_controller::RegulatedPurePursuitController`.
목표를 향한 방향 오차에 비례해 회전하고, 오차가 크면 선속도를 줄인다.

- 실제 RPP 는 lookahead 점의 **곡률**로 계산하고 곡률·장애물·경사에 따라 속도를 "규제"한다.
  여기서는 비례 제어로 줄였다 — 이 예제의 목표는 제어 성능이 아니라 **구조**다
- `desiredLinearVel_` 은 **전략이 자기 파라미터를 들고 있는 예**다 (ROS 파라미터에 해당)
- `scan.front_range_m < 1.0` 일 때 스스로도 줄인다 — **전략이 센서를 직접 보는 경우**
- `current` 를 쓰지 않으므로 **파라미터 이름을 생략**했다. 인터페이스가 넓어질 때 치르는 대가가 여기서 보인다

**`DwbController`** — `dwb_core::DWBLocalPlanner` (Dynamic Window Approach).
**현재 속도에서 한 주기 안에 도달 가능한 속도 범위**(= 동적 윈도)를 만들고,
그중 안전한 후보만 남겨 점수를 매겨 제일 좋은 것을 고른다.

```
윈도   v ∈ [current.linear_x  ± 0.6 m/s² × 0.5s]  ∩ [0, 0.55]
       w ∈ [current.angular_z ± 1.6 rad/s² × 0.5s] ∩ [-0.8, 0.8]
허용   v² / 2a  +  v·dt  <  front_range_m      (제동 거리 + 한 주기 이동 < 남은 공간)
점수   2.0 × alignment  +  0.3 × v             (목표를 향하는가 / 빠른가)
```

`window` 가 상수가 아니라 `current` 에서 계산된다는 점이 핵심이다.
**"동적" 윈도라는 이름이 비로소 의미를 갖는다** — 정지 상태에서는 0.30 m/s 밖에 못 내고,
0.30 m/s 로 달리는 중이면 0.55 m/s 까지 낼 수 있다(§4의 장면 4 vs 6).

허용 속도가 하나도 없으면 `Twist{}` 가 그대로 반환되어 정지한다.
샘플링은 축마다 3개(총 9개 후보)로 줄였다 — 실제 DWB 는 훨씬 촘촘하게 훑는다.

> 중요한 것은 **계산 방식이 Pure Pursuit 과 완전히 다른데도 `ControllerServer` 는 그 차이를 전혀 모른다**는 점이다.

**`StopController`** — 무조건 멈춘다. 책의 `FlyNoWay` 와 같은 자리이고,
**널 객체 패턴(Null Object)** 이라고 따로 부르기도 한다.
덕분에 `ControllerServer` 쪽에 "컨트롤러가 없을 때" 분기를 만들 필요가 없다.
구현에서 파라미터 **이름을 아예 쓰지 않는 것**은 `-Wunused-parameter` 경고를 피하는 정석이다.

### `filter/` - 속도 정책 축

| 클래스 | 하는 일 | 자리 |
|---|---|---|
| `NoSpeedLimit` | 그대로 통과 | 기본값 자리 (이쪽의 Null Object) |
| `SlowZoneFilter` | 선속도 상한을 내린다 — **선속도와 각속도를 같은 비율로** 줄여 곡률을 보존한다 | 사람이 다니는 복도, 교차로 |
| `EmergencyBrakeFilter` | 무엇을 계산했든 `0` 으로 덮는다 | 비상 정지 |

### `server/` - Context

ROS 2 Nav2 의 `controller_server` 노드 자리다.
헤더와 구현 **어디에도** 구상 클래스 이름이 없다. 아는 것은 `ControllerPlugin`, `SpeedFilter` 두 인터페이스뿐이고,
무엇이 꽂혀 있는지는 조립하는 쪽(`main`)만 안다.

**불변식 : 전략 둘은 항상 존재한다.**
생성자에서 받고 세터도 `nullptr` 을 거부하므로 `controlLoop` 안에 `if (plugin_)` 같은 방어 코드가 필요 없다.
"전략은 항상 존재한다"를 타입이 아니라 **불변식으로 보장**한 것이다.

---

## 4. 실행하면 보이는 것

```
===== 1. 기본 조립으로 한 주기 =====
  [deliverybot] /cmd_vel  linear.x= 0.40  angular.z= 0.46   (plugin=RegulatedPurePursuit, filter=none)

===== 2. 사람이 많은 구역 진입 - 속도 정책만 교체 =====
  [param] speed_filter     : none -> slow-zone
  [deliverybot] /cmd_vel  linear.x= 0.20  angular.z= 0.23   (plugin=RegulatedPurePursuit, filter=slow-zone)

===== 3. 정면 0.25m 장애물 - 컨트롤러를 교체 =====
  [param] FollowPath.plugin : RegulatedPurePursuit -> StopAndWait
  [deliverybot] /cmd_vel  linear.x= 0.00  angular.z= 0.00   (plugin=StopAndWait, filter=slow-zone)

===== 4. 장애물 회피 후 DWB 로 교체 =====
  [param] FollowPath.plugin : StopAndWait -> DWBLocalPlanner
  [param] speed_filter     : slow-zone -> none
  [deliverybot] /cmd_vel  linear.x= 0.30  angular.z= 0.80   (plugin=DWBLocalPlanner, filter=none)

===== 5. 비상 정지 - 컨트롤러는 그대로 두고 출력만 막는다 =====
  [param] speed_filter     : none -> e-stop
  [deliverybot] /cmd_vel  linear.x= 0.00  angular.z= 0.00   (plugin=DWBLocalPlanner, filter=e-stop)

===== 6. 같은 상황을 컨트롤러 3종에게 물어보기 =====
  [bench] /cmd_vel  linear.x= 0.40  angular.z= 0.46   (plugin=RegulatedPurePursuit, filter=none)
  [bench] /cmd_vel  linear.x= 0.55  angular.z= 0.80   (plugin=DWBLocalPlanner, filter=none)
  [bench] /cmd_vel  linear.x= 0.00  angular.z= 0.00   (plugin=StopAndWait, filter=none)
```

각 장면은 직전 장면이 퍼블리시한 명령을 `odom`(현재 속도)으로 되먹인다.
그래서 숫자가 장면 사이에 이어진다.

**장면 1 → 2 : 축이 분리되어 있다는 증거.**
컨트롤러는 `RegulatedPurePursuit` 그대로인데 속도 정책만 갈았다.

| | linear.x | angular.z | 곡률 ω/v |
|---|---|---|---|
| 장면 1 (`none`) | 0.40 | 0.46 | 1.15 |
| 장면 2 (`slow-zone`) | 0.20 | **0.23** | **1.15** |

둘 다 같은 비율(0.5)로 줄어서 **곡률이 보존된다.**
선속도만 잘랐다면 `0.20 / 0.46` 이 되어 곡률이 2배로 튀고 로봇이 경로를 이탈한다.

**장면 3 : 컨트롤러 교체.**
실제 Nav2 에서는 **비헤이비어 트리(BT)** 가 이 판단을 내려 컨트롤러/복구 동작을 바꿔 끼운다.

**장면 4 : 동적 윈도가 실제로 동작한다.**
직전 장면에서 로봇이 멈췄으므로(`odom = 0`) 이번 주기에 낼 수 있는 선속도 상한은
`0 + 0.6 m/s² × 0.5 s = 0.30` 이다. 그래서 `0.55` 가 아니라 **`0.30`** 이 나온다.
가속 한계를 무시한 값을 내보내면 실제 로봇은 그 속도에 도달하지 못하고 명령과 실제가 어긋난다.

**장면 5 : 자리가 다르다는 것.**
컨트롤러는 `DWBLocalPlanner` 그대로인데 출력만 `0` 이다. 계산은 계속 돌고 있다.

**장면 6 : "구현이 아닌 인터페이스에 맞춰 프로그래밍한다"의 확인.**
세 컨트롤러에게 **같은 `odom`(0.30 m/s)** 을 주고 물었다.
DWB 가 장면 4 의 `0.30` 이 아니라 `0.55` 를 고르는 이유가 여기서 드러난다 —
`0.30 + 0.30 = 0.60` 이 최대 속도 `0.55` 에서 잘린 값이다. **같은 코드, 다른 현재 속도, 다른 답.**

루프에는 구상 컨트롤러 이름이 `vector` 를 채울 때 말고는 나오지 않는다.
아는 것은 `ControllerPlugin` 하나뿐이라 **컨트롤러가 몇 개로 늘어나든 비교 루프는 한 글자도 바뀌지 않는다.**

여기서 두 축이 같이 드러난다.

| | 무엇 | 이름 |
|---|---|---|
| 세로축 (상속) | `ControllerPlugin*` 하나로 여러 구현을 다룬다 | 다형성 |
| 가로축 (구성) | 같은 서버가 서로 다른 구현을 들고 있다 | **전략** |

---

## 5. 대응표

### 책 예제 ↔ 이 예제

| 책 (오리 시뮬레이션) | 여기 |
|---|---|
| `Duck` | `ControllerServer` (Context) |
| `FlyBehavior` | `ControllerPlugin` — "경로를 어떻게 따라갈 것인가" |
| `QuackBehavior` | `SpeedFilter` — "계산한 속도를 그대로 낼 것인가" |
| `setFlyBehavior()` | `setPlugin()` — 실행 중 교체 |
| `FlyNoWay` | `StopController` / `NoSpeedLimit` (Null Object) |

### 이 예제 ↔ 실제 ROS 2

| 여기 | 실제 ROS 2 |
|---|---|
| `ControllerPlugin` | `nav2_core::Controller` (순수 가상 인터페이스) |
| `computeVelocity()` | `computeVelocityCommands()` |
| `ControllerServer` | `nav2_controller` 의 controller_server 노드 |
| `setPlugin()` | pluginlib 로더 + `FollowPath.plugin` 파라미터 |
| `publishCmdVel()` | `/cmd_vel` 토픽 퍼블리시 |
| `SpeedFilter` | `nav2_costmap_2d` 의 Speed Filter 플러그인 |
| 장면 3의 판단 | 비헤이비어 트리(BT) |

Nav2 가 `.so` 를 런타임에 로드해서 하는 일을 여기서는 `make_unique` 로 한다.
**로딩 방식만 다르고 구조는 같다.**

---

## 6. C++ 문법 메모

- `virtual ~ControllerPlugin() = default` — **다형적 기반 클래스에는 가상 소멸자가 필수다.**
  없으면 `unique_ptr<ControllerPlugin>` 이 파생 객체를 파괴할 때 미정의 동작이 된다
- `unique_ptr` 멤버 = **소유**. 세터에서 `std::move` 하면 옛 전략이 그 자리에서 파괴된다
- 멤버를 `protected` 가 아니라 `private` 로 — 파생 클래스에게도 열지 않는다
- 생성자·세터의 `nullptr` 거부가 **불변식**이 되어 `controlLoop` 에서 방어 코드를 지웠다
- `main` 의 장면 6 루프에서 참조에 `const` 를 붙이지 않는 이유 :
  `unique_ptr` 은 복사가 안 되므로 소유권을 옮겨 줘야 하고(`std::move`), 옮기고 나면 `plugins` 쪽은 비게 된다
- 파라미터를 안 쓸 때는 **이름을 생략**한다 (`StopController`, `PurePursuitController` 의 `const Twist&`)
  — `-Wunused-parameter` 회피의 정석
- `std::abs` 는 정수용이 `<cstdlib>`, 실수용이 `<cmath>` 다. `SlowZoneFilter` 가 후자를 쓴다
- `DwbController.cpp` 의 `sampleWindow` 는 **익명 네임스페이스**에 둔다 — 이 번역 단위 밖으로 새지 않는다

---

## 7. OOP 원칙

| 원칙 | 이 예제에서 어떻게 했나 |
|---|---|
| **캡슐화** — 바뀌는 부분을 분리한다 | 변하는 것이 둘이다. 주행 방식은 `ControllerPlugin` 뒤로, 속도 정책은 `SpeedFilter` 뒤로 각각 뺐다 |
| **상속보다 구성** | 서버가 전략을 **들고 있다**(has-a). 물려받았다면 실행 중 교체가 불가능하다 |
| **구현이 아닌 인터페이스** | `ControllerServer` 의 멤버 타입이 전부 추상 클래스다 |
| **OCP** | 컨트롤러를 추가해도 `server/` 는 0줄 바뀐다. 확장엔 열리고 변경엔 닫혔다 |

**거스른 것 / 치른 대가**

- 조립 지식이 클라이언트로 옮겨 갔다 — `main.cpp` 는 구상 클래스를 전부 안다
- 전략 축이 늘면 인터페이스도 함께 는다
- **인터페이스가 넓어지면 그 인자를 안 쓰는 전략도 받게 된다.**
  `current` 는 DWB 만 쓰는데 Pure Pursuit 과 Stop 도 받아야 한다
- 인터페이스를 한 번 고치면 **구상 전략 전부 + Context + 클라이언트**가 같이 바뀐다 (이번에 6개 파일)
- 간접 호출이 늘었다 (가상 함수 디스패치 2회/주기)

---

## 8. 설계 판단과 한계

### 왜 `StopController` 와 `EmergencyBrakeFilter` 를 따로 뒀나

결과는 똑같이 `0` 인데 **자리가 다르다.**

| | 어느 축 | 의미 |
|---|---|---|
| `StopController` | 축 1 (주행 방식) | "목표를 향한 판단을 **포기**한다" |
| `EmergencyBrakeFilter` | 축 2 (출력 정책) | "컨트롤러는 계속 **계산 중**인데 출력만 막는다" |

성능 문제가 아니라 **책임 배분**의 문제다.
실제 로봇의 하드웨어 E-stop 은 후자에 가깝다 — 소프트웨어가 뭘 시키든 전원을 끊는다.

### 이 예제의 한계 (알고 읽어야 하는 것)

**① "런타임 교체"가 사실은 대본이다.**
`main.cpp` 가 시나리오를 순서대로 직접 쓴다. 전략 패턴의 값어치는 *선택하는 주체가 따로 있을 때* 나오는데
(Nav2 에선 BT 나 파라미터 파일), 이 예제엔 그 주체가 없다.
지금 코드만으로는 "if-else 를 클래스로 흩어 놓은 것"이라는 반론에 방어가 안 된다.

**② 두 축이 완전히 직교하지는 않는다.**
`e-stop` 을 걸면 컨트롤러 3종의 결과가 **전부 동일**하다(장면 5).
흡수 원소라서 실제로 의미 있는 조합은 9개가 아니다.

**③ 필터는 여전히 사후 절삭이다.**
`SlowZoneFilter` 가 곡률을 보존하도록 고쳤지만, **컨트롤러는 자기 명령이 깎인 것을 모른다.**
실제 Nav2 는 `setSpeedLimit()` 으로 컨트롤러에 **미리** 상한을 알려 준다 —
그래야 컨트롤러가 그 상한을 전제로 경로를 다시 계산할 수 있다.
지금 구조에서는 DWB 가 0.55 를 계획했는데 필터가 0.20 으로 깎아도 DWB 는 다음 주기까지 그 사실을 모른다.

**④ 되먹이는 `odom` 이 실측이 아니라 "퍼블리시한 명령"이다.**
`controlLoop` 이 돌려주는 값은 로봇에게 *시킨* 속도지 로봇이 *낸* 속도가 아니다.
실제로는 슬립·지연·부하 때문에 둘이 어긋나고, 그래서 Nav2 는 오도메트리를 따로 구독한다.
이 예제는 "명령 = 실제"를 가정한 개루프다.

**⑤ 샘플링이 거칠다.**
DWB 의 동적 윈도를 축마다 3개(총 9개 후보)로만 훑는다.
그래서 각속도가 `-0.8 / 0 / +0.8` 처럼 튀는 값으로 나오기 쉽다.
실제 DWB 는 훨씬 촘촘하게 훑고 궤적 전체를 굴려 본다(trajectory rollout).

### 이 예제가 하지 않는 것

- Pure Pursuit / DWB 를 정확히 구현하지 않는다. 구조가 보일 만큼만 줄였다
- `nav2_core::Controller` 의 `configure()` / `activate()` / `setPlan()` / `setSpeedLimit()` 등은 뺐다.
  받는 것은 `computeVelocity()` 하나뿐이다
- pluginlib 도, `.so` 로딩도 없다
- 로봇이 실제로 움직이지 않는다. 자세(`pose`)는 모든 장면에서 원점 그대로다

---

## 9. 실행

### 이 폴더만 단독으로

```sh
cd robot/01_Strategy
make          # build/01_Strategy 에 실행 파일 생성
make run      # 빌드하고 바로 실행
make clean    # build/ 삭제
```

### 저장소 루트에서 (다른 패턴과 함께)

```sh
make robot                    # 로봇 예제 22개 전부 빌드 -> build/bin/robot_*
make run-robot-01_Strategy    # 이 예제만 빌드하고 실행
make run-robot-all            # 22개를 순서대로 실행
```

두 경로의 빌드 옵션은 같다 — `-std=c++20 -Wall -Wextra -Wpedantic -O1`, **경고 0개**를 유지한다.
산출물 위치만 다르다 — 단독은 `01_Strategy/build/`, 루트는 `build/bin/`.

---

## 10. 확인 문제

1. `server/` 폴더의 코드에서 구상 클래스 이름이 몇 번 나오는가?
   → **0번.** 1번이라도 나온다면 아직 구현에 묶여 있는 것이다.

2. 컨트롤러를 하나 더 추가해 보라. `server/`, `filter/`, 기존 컨트롤러를 **한 줄도** 안 고치고 되는가?
   → 인터페이스가 주는 정보(`pose`, `goal`, `scan`, `current`)만으로 되는 컨트롤러라면 된다.
   그 밖의 것(예: 전역 경로, 코스트맵, 직전 명령 이력)이 필요해지는 순간
   **인터페이스를 고쳐야 하고, 그러면 구상 전략 전부가 같이 바뀐다.** 그 지점이 이 패턴의 경계다.

3. `EmergencyBrakeFilter` 를 지우고 `StopController` 로만 비상 정지를 처리하면 무엇이 달라지는가?
   → 출력은 같지만 "누가 멈추기로 했는가"가 로그에서 사라진다.
