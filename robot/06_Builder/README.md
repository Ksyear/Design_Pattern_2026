# 06. Builder - 내비게이션 임무 조립

> 경유지는 **조건에 따라** 붙었다 말았다 한다. 생성자 인자로는 그렇게 못 짠다.
> 그리고 덜 만들어진 임무를 nav2 에 넘기면 로봇이 이상한 곳으로 간다.
>
> 책 예제 : [`../../06_Builder`](../../06_Builder) (휴가 계획표)

## 1. 어떤 문제를 푸는가

임무 하나에 들어가는 조각이 많다 - 경유지 목록, 속도 상한, 복구 동작, 반복 여부.
생성자로 받으면 이렇게 된다.

```cpp
Mission("r1", {...}, 0.4, {"spin", "backup"}, true);
```

1년 뒤에 읽으면 `0.4` 가 뭔지, `true` 가 뭔지 알 수 없다. 더 큰 문제는 따로 있다.

```cpp
if (batteryLow) {  /* 충전도크를 경유지에 추가하고 속도도 낮춘다 */ }
if (needInspection) {  /* 검수대를 중간에 끼운다 */ }
```

**조각이 조건부로 붙는다.** 생성자 인자 하나로는 표현할 수 없는 모양이다.
그래서 "짓는 동안" 과 "다 지어진 다음" 을 **다른 타입으로** 나눴다.

## 2. 폴더가 곧 패턴 역할

| 폴더 / 파일 | 패턴 역할 | 하는 일 |
|---|---|---|
| [`builder/MissionBuilder.*`](builder/MissionBuilder.h) | **Builder** | 조각을 하나씩 쌓고, `build()` 에서 검증한다 |
| [`director/MissionDirector.*`](director/MissionDirector.h) | **Director** | 자주 쓰는 조립 순서를 이름으로 굳혀 둔다 |
| [`mission/Mission.*`](mission/Mission.h) | **Product** | 완성된 임무. **세터가 없다** |
| [`mission/Waypoint.h`](mission/Waypoint.h) | (데이터) | 경유지 하나 (이름표 + x + y) |

역할 분담이 명확하다.

- **빌더**는 *어떻게* 쌓을지를 안다
- **디렉터**는 *무엇을* 쌓을지를 안다

## 3. 적용 방식

### (1) 메소드 체이닝 - 자기 참조를 돌려준다

```cpp
// builder/MissionBuilder.cpp
MissionBuilder& MissionBuilder::waypoint(const std::string& label, double x, double y)
{
	waypoints_.push_back(Waypoint{label, x, y});
	return *this;       // 이 한 줄이 점으로 이어 쓰게 만든다
}
```

### (2) 검증은 `build()` 한 곳에만

```cpp
Mission MissionBuilder::build() const
{
	if (waypoints_.empty()) {
		throw std::invalid_argument("경유지가 하나도 없는 임무는 만들 수 없습니다");
	}
	return Mission(robotId_, waypoints_, speedLimit_, recoveries_, looping_);
}
```

검사가 한 곳에 있으니 **임무를 만드는 모든 경로가 같은 검사를 거친다.**
디렉터를 통하든 직접 쌓든, 통과하지 못하면 `Mission` 객체 자체가 만들어지지 않는다.

### (3) 완성품은 불변이다

[`Mission.h`](mission/Mission.h) 에 세터가 하나도 없다.
태어난 순간 이미 완전하고, 이후로 바뀌지 않는다.
**"절반만 채워진 임무" 라는 상태가 타입 수준에서 존재하지 않는다.**

## 4. 실행하면 보이는 것 - 3번 장면이 핵심이다

```cpp
// main.cpp - 빌더가 진짜 힘을 쓰는 자리
MissionBuilder builder("adhoc-09");
builder.waypoint("출발", 0.0, 0.0).waypoint("A동", 6.0, 3.0);
if (needInspection) {
	builder.waypoint("검수대", 6.0, 6.0);
}
if (batteryLow) {
	builder.waypoint("충전도크", 0.0, 0.0).speedLimit(0.25);
}
builder.recovery("clear_costmap").build().print();
```

```
===== 3. 조건에 따라 조각을 붙이기 =====
  [adhoc-09] 임무 (1회)
    속도 상한 0.25 m/s
    경유지 3개
      - 출발 (0.00, 0.00)
      - A동 (6.00, 3.00)
      - 충전도크 (0.00, 0.00)     ← batteryLow 라서 붙었다
                                   ← 검수대는 needInspection=false 라서 없다
```

**빌더를 중간에 변수로 붙잡아 두고 `if` 사이에서 조각을 더한다.**
체이닝은 편의일 뿐이고, 빌더의 본질은 이 "붙잡아 둘 수 있음" 이다.

4번 장면에서는 경유지 없이 `build()` 를 불러 거부당한다.

```
  build() 거부 : 경유지가 하나도 없는 임무는 만들 수 없습니다
```

## 5. 실제 ROS 2 대응

| 이 예제 | 실제 ROS 2 |
|---|---|
| `Mission` | `nav2_msgs/action/FollowWaypoints` 의 goal |
| `waypoint()` | goal 의 `poses` 배열에 `PoseStamped` 를 추가 |
| `speedLimit()` | `/speed_limit` 토픽 또는 Speed Filter |
| `recovery()` | 비헤이비어 트리의 `RecoveryNode` 자식들 |
| `loopForever()` | BT 의 `KeepRunningUntilFailure` |
| `MissionDirector` | 임무 템플릿을 굳혀 둔 BT XML 파일들 |

nav2 의 비헤이비어 트리 XML 도, 런치 파일의 파라미터 묶음도 전부 이 모양이다.
**조각이 많고, 조건에 따라 붙었다 말았다 하고, 다 모이기 전에는 쓰면 안 되는 것.**

## 6. 디렉터가 꼭 필요한가

없어도 된다. 빌더만으로 다 만들 수 있다.
디렉터가 막는 것은 **같은 임무를 여러 곳에서 만들 때 조립 순서가 조금씩 어긋나는 일**이다.

```cpp
// director/MissionDirector.cpp - 야간 순찰의 "정의" 가 여기 한 곳에 있다
return MissionBuilder(robotId)
	.waypoint("로비", 0.0, 0.0)
	...
	.speedLimit(0.35)
	.recovery("spin").recovery("wait")
	.loopForever()
	.build();
```

"야간 순찰은 0.35m/s" 를 세 군데에 적어 두면 언젠가 하나만 고쳐진다.

## 7. 이 예제가 하지 않는 것

- 빌더를 재사용해 여러 임무를 찍어 내는 시나리오가 없다 (`build()` 는 `const` 라 가능하긴 하다)
- 경유지 좌표의 유효성(지도 밖인지, 도달 가능한지)을 검사하지 않는다.
  실제로는 이 검증이 `build()` 에서 가장 중요한 일이 된다
- 타입 수준의 단계 강제(예: 경유지를 넣기 전에는 `build()` 를 **호출조차 못 하게**)는 하지 않았다.
  런타임 예외로 처리한다

## 8. 객체지향 관점 - 어떤 원칙을 어떻게 지켰나

| 원칙 | 이 예제에서 어떻게 했나 |
|---|---|
| **SRP** | "임무란 무엇인가"(`Mission`)와 "어떻게 조립하나"(`MissionBuilder`)를 다른 클래스로 나눴다 |
| **캡슐화** | 검증이 `build()` 한 곳에만 있다. 모든 생성 경로가 같은 검사를 통과한다 |
| **불변 객체** | `Mission` 에 세터가 0개. "절반만 채워진 임무" 라는 상태가 타입에 없다 |

**C++ 문법으로 지킨 것**

- 메소드 체이닝 = `MissionBuilder&` (자기 참조) 반환
- `build()` 가 `const` - 빌더를 재사용해도 내부 상태가 망가지지 않는다
- 예외로 잘못된 객체의 **탄생 자체를** 막는다 (생성 후 검사가 아니라)

**거스른 것 / 대가**

- 단계 순서를 타입이 강제하지 않는다. "경유지 없이 `build()`" 가 **런타임** 예외다
  (타입 상태 기법으로 컴파일 시점에 막을 수도 있지만 복잡해진다)
- 클래스가 Product · Builder · Director 셋으로 늘어난다

## 9. 실행

### 이 폴더만 단독으로

```sh
cd robot/06_Builder
make          # build/06_Builder 에 실행 파일 생성
make run      # 빌드하고 바로 실행
make clean    # build/ 삭제
```

### 저장소 루트에서 (다른 패턴과 함께)

```sh
make robot                    # 로봇 예제 22개 전부 빌드 -> build/bin/robot_*
make run-robot-06_Builder    # 이 예제만 빌드하고 실행
make run-robot-all            # 22개를 순서대로 실행
```

두 경로의 빌드 옵션은 같다 - `-std=c++20 -Wall -Wextra -Wpedantic -O1`, **경고 0개**를 유지한다.
산출물 위치만 다르다 - 단독은 `06_Builder/build/`, 루트는 `build/bin/`.

## 10. 확인 질문

> `Mission` 에 세터가 있는가? 검증 코드가 몇 군데 있는가?

세터는 0개, 검증은 `build()` 한 곳이다.
세터를 하나라도 열면 "다 지어진 다음" 이라는 보장이 그 자리에서 사라진다.
