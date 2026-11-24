# 13. Adapter - 레거시 초음파 보드를 표준 스캔으로

> 10년 된 센서 보드는 **고칠 수 없다.** 내비게이션도 고칠 수 없다.
> 그 사이에 번역기를 하나 끼운다.
>
> 책 예제 : [`../../13_Adapter`](../../13_Adapter) (칠면조를 오리로)

## 1. 어떤 문제를 푸는가

센서는 벤더마다 전부 다르다. 이 예제의 레거시 보드는 이렇게 생겼다.

| | 레거시 초음파 보드 | 표준 `LaserScan` |
|---|---|---|
| 단위 | **cm** | m |
| 읽는 방식 | 한 번에 **하나씩** (`pingCentimeters(i)`) | 배열 한 방 |
| 측정 실패 | **-1** | 0.0 |
| 좌표계 | 개념 자체가 없다 | `frame_id` 필수 |

중요한 것은 **양쪽 다 고칠 수 없다**는 전제다.

- 레거시 보드 : 벤더가 준 바이너리거나, 이미 다른 장비 열 대가 의존하고 있거나, 검증이 끝난 코드
- 내비게이션 : 센서 하나 붙일 때마다 고칠 수는 없다

> **어댑터가 필요한 상황은 대개 "고칠 수 없다" 에서 시작한다.**

## 2. 폴더가 곧 패턴 역할

| 폴더 / 파일 | 패턴 역할 | 하는 일 |
|---|---|---|
| [`sensor/RangeSensor.h`](sensor/RangeSensor.h) | **Target** | 상위 코드가 아는 유일한 형식 |
| [`sensor/Lidar2D.*`](sensor/Lidar2D.h) | (이미 표준인 센서) | 어댑터가 필요 없는 쪽 - 비교용 |
| [`legacy/SerialSonarArray.*`](legacy/SerialSonarArray.h) | **Adaptee** | 형식이 안 맞는 기존 물건. **고칠 수 없다** |
| [`adapter/SonarToScanAdapter.*`](adapter/SonarToScanAdapter.h) | **Adapter (객체)** | 보드를 품고(has-a) 번역 |
| [`adapter/SonarClassAdapter.*`](adapter/SonarClassAdapter.h) | **Adapter (클래스)** | 다중 상속 - **C++ 에서만 가능** |
| [`msg/LaserScan.h`](msg/LaserScan.h) | (데이터) | 표준 메시지 |

## 3. 적용 방식 - 번역은 두 줄이다

```cpp
// adapter/SonarToScanAdapter.cpp
LaserScan SonarToScanAdapter::scan() const
{
	LaserScan out;
	out.frameId = "sonar_link";                        // 없던 개념을 채워 넣고
	const int n = board_->sensorCount();
	for (int i = 0; i < n; ++i) {
		const int cm = board_->pingCentimeters(i);     // 하나씩 읽어서
		out.ranges.push_back(cm < 0 ? 0.0 : cm / 100.0);  // 단위와 실패 표현을 바꾼다
	}
	return out;
}
```

`cm < 0 ? 0.0 : cm / 100.0` 이 한 줄에 **실패 표현 변환과 단위 변환이 둘 다** 들어 있다.
어댑터가 하는 일은 이게 전부다 - 로직이 아니라 **형식 맞추기**다.

## 4. C++ 에만 있는 선택지 - 클래스 어댑터

책의 자바 구현을 그대로 옮기면 객체 어댑터뿐이다. C++ 에는 하나가 더 있다.

```cpp
// adapter/SonarClassAdapter.h
class SonarClassAdapter : public RangeSensor, private SerialSonarArray {
//                        ^^^^^^ is-a        ^^^^^^^ 물려받되 감춘다
```

- `public RangeSensor` : 상위 코드가 기대하는 **형식이 된다**
- `private SerialSonarArray` : 낡은 보드의 기능을 **물려받되 밖으로는 감춘다**

```cpp
// adapter/SonarClassAdapter.cpp
SonarClassAdapter::SonarClassAdapter(const char* device)
{
	openPort(device);   // 물려받은 기능을 직접 부른다 (포인터 경유가 없다)
}
```

`board_->` 가 사라진다. 상속받은 멤버 함수를 그냥 부른다.

### 어느 쪽을 쓸 것인가

| | 객체 어댑터 | 클래스 어댑터 |
|---|---|---|
| 관계 | has-a (`unique_ptr` 로 품는다) | is-a (`private` 상속) |
| 대상 교체 | **런타임에 가능** | 컴파일 시점에 고정 |
| 여러 개 감싸기 | 가능 | 불가능 |
| 오버헤드 | 포인터 하나 | 없다 |
| Adaptee 동작 수정 | 불가능 | `virtual` 이면 오버라이드 가능 |
| 자바에서 | 가능 | **불가능** (다중 상속 없음) |

**대개 객체 어댑터가 낫다.** 클래스 어댑터는 상속 관계가 얽히고 대상이 고정된다.
이 예제가 둘을 나란히 둔 것은 선택지를 보여 주기 위해서다.

## 5. 실행하면 보이는 것

```
===== 2. 낡은 보드를 직접 쓰면 이렇게 생겼다 =====
    pingCentimeters(0) = 187 (cm)
    pingCentimeters(2) = -1 (실패를 -1 로)

===== 3. 객체 어댑터를 끼우면 표준 센서가 된다 =====
  [SonarArray (어댑터 경유)] frame=sonar_link  ranges = 1.87 2.43 0.00 0.96
      최단 거리 0.96m -> 감속

===== 4. 클래스 어댑터 (C++ 다중 상속) =====
  [SonarArray (클래스 어댑터)] frame=sonar_link  ranges = 1.87 2.43 0.00 0.96
      최단 거리 0.96m -> 감속
```

`187` → `1.87`, `-1` → `0.00`. 두 어댑터의 **결과가 완전히 같다** - 구현 방식만 다르다.

```
===== 5. 상위 코드는 셋을 구분하지 않는다 =====
  [RPLIDAR A2] frame=laser_link ...
  [SonarArray (클래스 어댑터)] frame=sonar_link ...
```

`std::vector<std::unique_ptr<RangeSensor>>` 에 라이다와 어댑터를 섞어 담고 같은 루프로 돈다.

```
===== 6. 응답 없는 보드 - 실패를 빈 길로 읽지 않는다 =====
  [SonarArray (어댑터 경유)] frame=sonar_link  ranges = 0.00 0.00 0.00 0.00
      유효한 측정값 없음 -> 정지
```

`openPort()` 를 빠뜨린 보드는 전부 `-1` 을 주고, 어댑터는 그것을 전부 `0.0` 으로 번역한다.
예전 `runObstacleCheck` 는 `0.0` 을 건너뛰고 최단 거리를 `1e9` 로 남겨 **"정상 주행"** 이라고 판단했다.
고장 난 센서를 빈 길로 읽은 것이다. 지금은 유효값이 하나도 없으면 멈춘다.

> 어댑터가 형식을 맞추면서 **"측정 실패" 라는 의미까지 흐리면**, 상위 코드는 그 차이를 알 수 없다.
> 번역은 형식만이 아니라 의미를 보존해야 한다.

### 이 예제가 증명하는 것

```cpp
// main.cpp 끝의 주석
// SerialSonarArray 는 한 줄도 고치지 않았다.
// runObstacleCheck 도 어댑터 때문에 고친 줄은 없다.
// 새로 생긴 것은 그 사이의 번역기 하나뿐이다.
```

**양쪽을 건드리지 않고 사이에 한 겹을 넣었다.** 그게 어댑터의 전부다.
(6번 장면의 "유효값 없음 → 정지" 는 어댑터와 무관한 판단 로직의 안전장치다.)

## 6. 실제 ROS 2 대응

ROS 2 에는 이 패턴이 **노드 형태로** 대량 존재한다.

| 이 예제 | 실제 ROS 2 노드 |
|---|---|
| `SonarToScanAdapter` | `pointcloud_to_laserscan` (PointCloud2 → LaserScan) |
| 같은 자리 | `depthimage_to_laserscan` (뎁스 이미지 → LaserScan) |
| 같은 자리 | `imu_transformer`, 각종 메시지 변환 노드 |
| `frameId` 를 채워 넣는 부분 | TF 프레임을 붙이는 작업 |

**"센서는 그대로 두고 형식만 맞춰 주는 노드"** 가 전부 이 패턴이다.
ROS 생태계가 서로 다른 벤더의 하드웨어를 같이 쓸 수 있는 이유이기도 하다.

## 7. 03_Decorator 와 구조가 비슷한데

둘 다 무언가를 감싼다. **목적이 다르다.**

| | 13 Adapter | 03 Decorator |
|---|---|---|
| 인터페이스 | **바꾼다** (A → B) | **유지한다** (A → A) |
| 목적 | 안 맞는 것을 맞춘다 | 기능을 더한다 |
| 겹쳐 쌓기 | 보통 한 겹 | 여러 겹이 전제 |

어댑터를 두 겹 쌓는 일은 거의 없다. 데코레이터는 쌓으라고 만든 것이다.

## 8. 이 예제가 하지 않는 것

- 각도 정보가 없다. 실제 `LaserScan` 은 `angle_min` / `angle_increment` 가 있고,
  초음파 센서 배열을 진짜로 스캔으로 바꾸려면 **각 센서가 어느 방향을 보는지** 알아야 한다
- 초음파의 넓은 빔 각도를 무시한다. 라이다처럼 점으로 취급하면 실제로는 부정확하다
- 타임스탬프가 없다. 센서마다 지연이 다른데 그걸 맞추는 것도 어댑터의 일이 될 수 있다
- 양방향 어댑터가 아니다. 읽기만 하고 명령은 보내지 않는다
- 실패를 `0.0` 으로 표현한다. ROS 의 [REP 117](https://www.ros.org/reps/rep-0117.html) 은
  오류를 `NaN`, 범위 밖을 `+Inf`, 너무 가까움을 `-Inf` 로 쓴다
- 초음파를 `LaserScan` 에 담았다. 실제 [`LaserScan.msg`](https://github.com/ros2/common_interfaces/blob/rolling/sensor_msgs/msg/LaserScan.msg)
  주석은 초음파 배열처럼 동작이 다른 장치에는 다른 메시지를 쓰라고 하고,
  초음파용으로는 빔 폭(`field_of_view`)을 담는 `sensor_msgs/Range` 가 있다

## 9. 객체지향 관점 - 어떤 원칙을 어떻게 지켰나

| 원칙 | 이 예제에서 어떻게 했나 |
|---|---|
| **구현이 아닌 인터페이스** | 클라이언트는 `RangeSensor` 만 안다 |
| **OCP** | 레거시도 클라이언트도 **0줄 수정**하고 사이에 한 겹을 넣었다 |
| **LSP** | 어댑터가 `RangeSensor` 자리에 그대로 들어가야 성립한다 (5번 장면이 그 검증) |

**C++ 문법으로 지킨 것**

- **is-a 와 has-a 를 나란히 놓고 비교한다** - 이 예제의 교육적 핵심이다
  - 객체 어댑터 : `unique_ptr<SerialSonarArray> board_` (has-a)
  - 클래스 어댑터 : `public RangeSensor, private SerialSonarArray` (is-a + 구현 상속)
- **`private` 상속 = "구현만 물려받고 타입은 물려받지 않는다"** - 자바에 없는 개념
- 다중 상속이 있어야 가능한 형태

**거스른 것 / 대가**

- 한 겹이 더 생긴다 (지연 · 복잡도)
- **어댑터가 정보 손실을 감춘다.** 초음파의 넓은 빔 각도를 라이다처럼 점으로 바꿔 놓으면
  클라이언트는 그 차이를 알 방법이 없다

## 10. 실행

### 이 폴더만 단독으로

```sh
cd robot/13_Adapter
make          # build/13_Adapter 에 실행 파일 생성
make run      # 빌드하고 바로 실행
make clean    # build/ 삭제
```

### 저장소 루트에서 (다른 패턴과 함께)

```sh
make robot                    # 로봇 예제 22개 전부 빌드 -> build/bin/robot_*
make run-robot-13_Adapter    # 이 예제만 빌드하고 실행
make run-robot-all            # 22개를 순서대로 실행
```

두 경로의 빌드 옵션은 같다 - `-std=c++20 -Wall -Wextra -Wpedantic -O1`, **경고 0개**를 유지한다.
산출물 위치만 다르다 - 단독은 `13_Adapter/build/`, 루트는 `build/bin/`.

## 11. 확인 질문

> 이 패턴을 적용하면서 `legacy/` 나 `runObstacleCheck` 를 몇 줄 고쳤는가?

0줄이다. 고쳐야 했다면 어댑터가 아니라 리팩터링이다.
