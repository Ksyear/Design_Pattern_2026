# 14. Facade - 자율주행 시동 절차

> 로봇을 켜는 데 아홉 단계가 필요하고, **순서를 틀리면 위험하다.**
> 그 순서를 아는 곳을 하나로 만든다.
>
> 책 예제 : [`../../14_Facade`](../../14_Facade) (홈시어터)

## 1. 어떤 문제를 푸는가

자율주행을 켜려면 이 순서를 지켜야 한다.

```
전원 24V → 모터 드라이버 활성 → 브레이크 해제 → 라이다 스핀업
  → 지도 로드 → 초기 위치 설정 → 파티클 수렴 대기 → nav2 configure → activate
```

틀리면 실제로 사고가 난다.

- 브레이크를 안 풀고 주행 → 모터가 탄다
- 측위가 수렴하기 전에 목표를 받음 → 엉뚱한 곳으로 간다
- 종료할 때 브레이크보다 전원을 먼저 끔 → **로봇이 경사로에서 굴러간다**

호출하는 쪽마다 이 순서를 적어 두면 **언젠가 한 곳이 틀린다.**
그래서 순서를 아는 곳을 **딱 하나**로 만들었다.

## 2. 폴더가 곧 패턴 역할

| 폴더 / 파일 | 패턴 역할 | 하는 일 |
|---|---|---|
| [`facade/AutonomyFacade.*`](facade/AutonomyFacade.h) | **Facade** | **순서를 아는 유일한 곳** |
| [`subsystem/PowerRail.*`](subsystem/PowerRail.h) | Subsystem | 24V 레일 ON/OFF |
| [`subsystem/MotorDriver.*`](subsystem/MotorDriver.h) | Subsystem | 드라이버 활성 / 브레이크 |
| [`subsystem/LidarDriver.*`](subsystem/LidarDriver.h) | Subsystem | 스핀업 / 스핀다운 |
| [`subsystem/Localization.*`](subsystem/Localization.h) | Subsystem | 지도 로드 / 초기 위치 / 수렴 확인 |
| [`subsystem/NavStack.*`](subsystem/NavStack.h) | Subsystem | configure / activate / deactivate / cleanup |

**하위 시스템 다섯은 서로를 전혀 모른다.** 다섯을 다 아는 것은 파사드 하나뿐이다.

## 3. 적용 방식

```cpp
// facade/AutonomyFacade.cpp
bool AutonomyFacade::startAutonomy(const char* mapName, double initX, double initY)
{
	power_.enable24V();
	motors_.enable();
	motors_.releaseBrake();

	lidar_.spinUp();

	localization_.loadMap(mapName);
	localization_.setInitialPose(initX, initY);
	if (!localization_.waitForConvergence()) {
		std::cout << "    측위 실패 - 시동 중단\n";
		shutdown();            // 실패하면 여기까지 켠 것을 되돌린다
		return false;
	}

	nav_.configure();
	nav_.activate();
	navActive_ = true;
	return true;
}
```

파사드에 **새 로직이 없다.** 순서와 실패 처리만 있다.
그게 파사드다 - 기능을 더하는 게 아니라 **조합을 제공**한다.

### 종료는 역순이고, 그것도 파사드가 안다

```cpp
void AutonomyFacade::shutdown()
{
	if (navActive_) {          // 켠 것만 끈다
		nav_.deactivate();
		nav_.cleanup();        // Unconfigured 로 돌려 놔야 다음 configure 가 유효하다
		navActive_ = false;
	}
	lidar_.spinDown();
	motors_.engageBrake();   // 반드시 브레이크가 먼저다
	motors_.disable();
	power_.disable24V();
}
```

`engageBrake()` 가 `disable()` 보다 **먼저**여야 한다.
드라이버를 먼저 끄면 브레이크가 걸리기 전에 유지 토크가 사라진다.

`navActive_` 가 필요한 이유는 실패 경로다. 측위가 실패하면 `shutdown()` 으로 되돌리는데,
그 시점의 nav2 는 아직 configure 전(Unconfigured)이다.
Unconfigured 에서 가능한 전이는 `configure` 와 `shutdown` 뿐이라 `deactivate` 를 보내면 잘못된 전이가 된다
([`../21_State`](../21_State) 의 전이표, [ROS 2 노드 라이프사이클 설계 문서](https://design.ros2.org/articles/node_lifecycle.html)).
같은 이유로 정상 종료 때는 `cleanup` 까지 해야 한다. Inactive 에서는 다시 `configure` 할 수 없다.

> [`../09_Command`](../09_Command) 의 매크로 되돌리기가 역순이어야 했던 것과 같은 이야기다.
> **순서가 곧 안전이다.**

## 4. 3번 장면 - 파사드는 봉인하지 않는다

```cpp
// facade/AutonomyFacade.h
	// 정비용 - 하위 시스템 직접 접근
	MotorDriver& motors();
```

```
===== 3. 정비 모드 - 파사드는 막지 않는다 =====
  브레이크만 따로 체결 (정비용) :
    [motor] 전자 브레이크 체결
```

**이 게터가 실수로 열린 게 아니다.** 의도적이다.

캘리브레이션, 정비 모드, 디버깅처럼 **정해진 절차를 벗어나야 하는 작업**이 반드시 생긴다.
파사드가 하위 시스템을 완전히 숨기면 그런 작업이 불가능해지고,
결국 누군가 파사드를 우회하는 뒷길을 만든다.

> **파사드는 편의를 제공할 뿐, 하위 시스템을 봉인하지 않는다.**
> 쉬운 길을 열어 두되, 어려운 길을 막지는 않는다.

## 5. 실행하면 보이는 것

```
===== 1. 파사드 없이 직접 한다면 =====
    power.enable24V(); motors.enable(); motors.releaseBrake();
    lidar.spinUp(); amcl.loadMap(); amcl.setInitialPose();
    amcl.waitForConvergence(); nav.configure(); nav.activate();
  -> 순서를 아는 곳이 여러 군데가 되고, 언젠가 한 곳이 틀린다

===== 2. 파사드로 한 줄 =====
  AutonomyFacade::startAutonomy()
    [power] 24V 레일 ON
    ...
  준비 완료
```

호출하는 쪽의 코드가 **아홉 줄에서 한 줄**이 됐다.
줄 수가 핵심이 아니다 - **아홉 줄이 어디에 있는가**가 핵심이다.

```
===== 5. 측위 실패 - 켠 것만 되돌린다 =====
  AutonomyFacade::startAutonomy()
    ...
    [amcl] 지도 로드 : missing_map.yaml  (파일 없음)
    [amcl] 초기 위치 (0, 0) 설정
    [amcl] 파티클 수렴 확인 - 실패 (지도 없음)
    측위 실패 - 시동 중단
  AutonomyFacade::shutdown()  (역순)
    [lidar] 스핀 다운
    [motor] 전자 브레이크 체결
    [motor] 드라이버 비활성
    [power] 24V 레일 OFF
  정지 완료
  -> 시동 거부. nav2 는 configure 전이라 deactivate 를 보내지 않았다
```

4번 장면의 정상 종료와 비교하면 `[nav2]` 줄이 없다. **켠 것만 역순으로 되돌린다.**
시뮬레이션의 `Localization` 은 `warehouse_1f.yaml` 이 아닌 지도를 "파일 없음" 으로 보고 수렴에 실패한다.

## 6. 원칙 - 최소 지식 원칙 (디미터 법칙)

> 호출하는 쪽이 다섯 개 장치를 다 알 필요가 없다. **친구 하나만** 알면 된다.

[`main.cpp`](main.cpp) 는 `AutonomyFacade` 하나만 안다 (정비 모드 제외).
`PowerRail` 이나 `NavStack` 같은 이름을 몰라도 로봇을 켤 수 있다.

## 7. 실제 ROS 2 대응

| 이 예제 | 실제 ROS 2 |
|---|---|
| `AutonomyFacade` | 런치 파일 (`ros2 launch`) |
| 라이프사이클 전이 순서 | `nav2_lifecycle_manager` - 정확히 이 역할이다 |
| `startAutonomy()` | `bringup_launch.py` + lifecycle manager 의 자동 전이 |
| `motors()` 게터 | 개별 노드에 직접 서비스 콜 하는 것 |
| 하위 시스템 | 각각 독립된 노드 |

`nav2_lifecycle_manager` 는 이름부터가 "순서를 아는 관리자" 다.
노드 목록을 받아서 정해진 순서로 **모든 노드를** `configure` 한 다음 **모든 노드를** `activate` 하고,
종료할 때는 역순으로 `deactivate` → `cleanup` 한다
([lifecycle_manager.cpp](https://github.com/ros-navigation/navigation2/blob/main/nav2_lifecycle_manager/src/lifecycle_manager.cpp)).

## 8. 어댑터 / 중재자와의 구분

| | 하는 일 | 인터페이스 |
|---|---|---|
| **13 Adapter** | 안 맞는 형식을 맞춘다 | **바꾼다** (A → B) |
| **14 Facade** | 쓰기 쉽게 한다 | **더한다** (여러 개 → 간단한 것 하나) |
| **12 Mediator** | 상호작용을 조정한다 | 양방향 - 하위가 중재자를 **안다** |

파사드와 중재자의 차이가 미묘하다. **방향**으로 구분하면 쉽다.

- **파사드** : 하위 시스템이 파사드의 존재를 **모른다**. 단방향
- **중재자** : 노드들이 중재자를 **가리킨다**. 양방향

`subsystem/` 폴더의 어떤 파일에도 `AutonomyFacade` 라는 이름이 없다.
[`../12_Mediator`](../12_Mediator) 의 `RobotNode` 는 `Mediator*` 를 들고 있었다.

## 9. 이 예제가 하지 않는 것

- 각 단계의 **실제 대기**가 없다. 라이다 스핀업 3초, 파티클 수렴 대기 등이 즉시 끝난다
- 실패 처리가 `waitForConvergence()` 한 곳뿐이다.
  실제로는 모든 단계가 실패할 수 있고, 어디까지 되돌릴지가 매번 다르다
- 타임아웃이 없다. 실제 lifecycle manager 는 전이마다 타임아웃을 둔다
- 하위 시스템이 파사드 안에 값으로 들어 있다.
  실제 노드들은 별도 프로세스라 서비스 콜로 이어진다

## 10. 객체지향 관점 - 어떤 원칙을 어떻게 지켰나

| 원칙 | 이 예제에서 어떻게 했나 |
|---|---|
| **최소 지식(디미터 법칙)** | 대표 예. 클라이언트는 **친구 하나**(`AutonomyFacade`)만 안다 |
| **느슨한 결합** | 클라이언트 ↔ 하위 시스템 5개의 결합을 끊었다 |
| **캡슐화** | 감추는 것이 데이터가 아니라 **순서**라는 점이 특이하다 |

**C++ 문법으로 지킨 것**

- 하위 시스템을 **값 멤버로 소유** - 포인터도 `unique_ptr` 도 필요 없다 (RAII 가 알아서)
- `MotorDriver& motors()` - 참조 게터. **봉인하지 않겠다**는 선언이다
- 실패 시 `shutdown()` 을 호출해 롤백하되 `navActive_` 로 켠 것만 끈다 - 절차의 예외 처리도 파사드의 책임

**거스른 것 / 대가**

- 파사드 자신이 비대해질 수 있다 (하위 시스템이 늘수록)
- 게터를 열어 둔 만큼 **우회가 가능하다.** 의도된 대가지만, 우회 경로가 늘면 파사드의 보증이 약해진다
- 하위 시스템은 파사드를 모르므로 **파사드를 건너뛴 호출을 막을 방법이 없다**

## 11. 실행

### 이 폴더만 단독으로

```sh
cd robot/14_Facade
make          # build/14_Facade 에 실행 파일 생성
make run      # 빌드하고 바로 실행
make clean    # build/ 삭제
```

### 저장소 루트에서 (다른 패턴과 함께)

```sh
make robot                    # 로봇 예제 22개 전부 빌드 -> build/bin/robot_*
make run-robot-14_Facade    # 이 예제만 빌드하고 실행
make run-robot-all            # 22개를 순서대로 실행
```

두 경로의 빌드 옵션은 같다 - `-std=c++20 -Wall -Wextra -Wpedantic -O1`, **경고 0개**를 유지한다.
산출물 위치만 다르다 - 단독은 `14_Facade/build/`, 루트는 `build/bin/`.

## 12. 확인 질문

> `subsystem/` 의 다섯 파일 중 `AutonomyFacade` 를 아는 것이 있는가?

없다. 하위 시스템은 파사드가 존재하는지도 모른다.
그래서 파사드를 지워도 하위 시스템은 그대로 동작한다 - 편의층일 뿐이라서.
