# 07. Prototype - 같은 기종 로봇을 여러 대 스폰하기

> 설정이 끝난 견본 하나를 두고 **복제해서** 띄운다.
> URDF 를 열 번 파싱하고 센서 파라미터를 열 번 조립하지 않는다.
>
> 책 예제 : [`../../07_Prototype`](../../07_Prototype) (몬스터 레지스트리)

## 1. 어떤 문제를 푸는가

창고에 같은 기종 AMR 을 열 대 띄운다. 열 대가 공유하는 것과 다른 것이 나뉜다.

| 공유하는 것 | 개체마다 다른 것 |
|---|---|
| 모델명, 센서 목록, 최고 속도 | 네임스페이스, 초기 위치 |

공유하는 쪽을 매번 처음부터 조립하면 낭비다.
게다가 **"기본 프로필을 고친다"** 는 요구가 반드시 온다 -
센서 하나를 추가하면 열 대에 전부 반영돼야 한다.

그래서 **설정이 끝난 객체를 견본으로 보관하고, 복제 + 차이점만 덮어쓰기** 로 만들었다.

## 2. 폴더가 곧 패턴 역할

| 폴더 / 파일 | 패턴 역할 | 하는 일 |
|---|---|---|
| [`spec/RobotSpec.*`](spec/RobotSpec.h) | **Prototype** | `clone()` 을 선언하고 공통 상태를 보관 |
| [`spec/DeliveryBot.*`](spec/DeliveryBot.h) | Concrete Prototype | AMR-200, 2D 라이다 + 뎁스 카메라 + IMU, 0.8m/s |
| [`spec/PatrolBot.*`](spec/PatrolBot.h) | Concrete Prototype | SEC-50, 3D 라이다 + 열화상 + 마이크 + IMU, 1.2m/s |
| [`registry/SpawnRegistry.*`](registry/SpawnRegistry.h) | **Client (견본 보관소)** | 이름 → 견본. 달라고 하면 복제해서 내준다 |

## 3. 적용 방식 - C++ 에서 `clone()` 을 쓰는 법

```cpp
// spec/RobotSpec.h
virtual std::unique_ptr<RobotSpec> clone() const = 0;
```

자바의 `clone()` 과 두 가지가 다르다.

1. **값이 아니라 포인터로 돌려준다** - 값으로 돌려주면 슬라이싱이 일어난다
2. **원시 포인터가 아니라 `unique_ptr`** - 복제본의 소유권이 호출한 쪽으로 넘어간다는 것을 타입이 말해 준다

```cpp
// spec/PatrolBot.cpp
std::unique_ptr<RobotSpec> PatrolBot::clone() const
{
	return std::unique_ptr<RobotSpec>(new PatrolBot(*this));   // 복사 생성자를 쓴다
}
```

### 깊은 복사가 공짜였던 이유

```cpp
// spec/RobotSpec.h
protected:
	RobotSpec(const RobotSpec&) = default;   // 기본 복사로 충분하다

private:
	std::string model_;
	std::vector<std::string> sensors_;   // 값 타입
	double maxSpeed_;
	...
```

멤버가 **전부 값 타입**(`string` / `vector` / `double`)이라서 컴파일러가 만들어 주는
복사 생성자가 이미 깊은 복사다.

> **만약 `RobotSpec` 이 포인터 멤버를 들고 있었다면 4번 장면에서 견본까지 오염된다.**

복사 생성자를 `protected` 로 둔 것도 의도적이다.
외부에서 `RobotSpec` 을 값으로 복사하려는 시도를 막고, `clone()` 을 통과하게 강제한다.

### 레지스트리는 기종 이름을 모른다

```cpp
// registry/SpawnRegistry.cpp
std::unique_ptr<RobotSpec> fresh = it->second->clone();   // 무엇을 복제하는지 모른다
fresh->placeAt(namespaceName, x, y);                      // 차이점만 덮어쓴다
return fresh;
```

`DeliveryBot` / `PatrolBot` 이라는 이름이 이 파일에 없다.
새 기종을 추가할 때 고치는 곳은 [`main.cpp`](main.cpp) 의 **등록 한 줄**뿐이다.

## 4. 실행하면 보이는 것

### 견본을 손보면 이후 스폰이 전부 물려받는다

```cpp
auto tuned = std::make_unique<DeliveryBot>();
tuned->addSensor("cargo_weight_sensor");
registry.registerPrototype("delivery_v2", std::move(tuned));
```

```
  delivery_v2 ->   /(미배치)  AMR-200 [배송]  max 0.80 m/s
      센서 : 2d_lidar depth_camera imu cargo_weight_sensor
```

**"기본 프로필을 고친다" 가 코드 세 줄이 된다.** 클래스를 새로 만들 필요가 없다.

### 4번 장면 - 깊은 복사 확인

```
  amr_01 에만 범퍼를 달았다
  /amr_01  AMR-200 [배송]  센서 : 2d_lidar depth_camera imu bumper
  견본 delivery 는 :
  /check   AMR-200 [배송]  센서 : 2d_lidar depth_camera imu      ← 안 바뀌었다
```

복제본에 범퍼를 달았는데 견본은 그대로다.
**이 확인이 프로토타입 패턴에서 가장 중요한 검증**이다. 얕은 복사였다면 여기서 터진다.

### 5번 장면 - 없는 견본

```
  스폰 실패 : drone 라는 견본이 없습니다
  nullptr 이 돌아왔다 - 호출한 쪽이 확인해야 한다
```

`nullptr` 을 돌려준다. `std::optional` 이나 예외를 쓸 수도 있는 자리다 - **의도적인 선택**이고,
그래서 호출한 쪽에 확인 책임이 생긴다.

## 5. 실제 로봇에서의 자리

| 이 예제 | 실무 |
|---|---|
| `SpawnRegistry` | Gazebo 의 모델 데이터베이스 |
| `spawn(key, ns, x, y)` | `ros2 run gazebo_ros spawn_entity.py -entity ... -x ... -y ...` |
| `placeAt()` 의 네임스페이스 | 멀티 로봇 런치의 `namespace:=amr_01` |
| 견본 수정 → 전체 반영 | fleet 기본 프로필 YAML 을 고치는 것 |

멀티 로봇 시스템에서 **"기본 프로필 + 개체별 차이"** 는 거의 표준 구조다.

## 6. 언제 이 패턴이 필요한가 (그리고 필요 없는가)

프로토타입이 값을 하는 조건은 **초기 설정이 비쌀 때**다.

- URDF 파싱, 센서 캘리브레이션 로드, 지도 로드 → 복제가 싸다
- 필드 세 개짜리 구조체 → 그냥 생성자를 부르는 게 낫다

이 예제는 학습용이라 설정이 싸다. 그래서 **패턴의 이득이 잘 안 보인다** -
실제로는 "견본 만드는 데 2초, 복제하는 데 1ms" 같은 차이가 있어야 도입할 이유가 생긴다.

## 7. 이 예제가 하지 않는 것

- 복제 비용이 실제로 싸다는 것을 보여 주지 않는다 (설정이 애초에 가볍다)
- 견본을 등록 후에 수정하는 API 가 없다. 수정하려면 새 견본으로 다시 등록해야 한다
- `clone()` 에 `new` 가 남아 있다 (`make_unique` 는 `protected` 복사 생성자에 접근할 수 없다)

## 8. 객체지향 관점 - 어떤 원칙을 어떻게 지켰나

| 원칙 | 이 예제에서 어떻게 했나 |
|---|---|
| **구현이 아닌 인터페이스** | `clone()` 하나로 기종을 모른 채 복제한다 |
| **캡슐화** | "자기를 어떻게 만드는가" 를 객체 자신이 안다. 레지스트리는 모른다 |
| **OCP** | 기종 추가에 `registry/` 는 0줄 바뀐다 |

**C++ 문법으로 지킨 것**

- **슬라이싱 회피** - 값이 아니라 `unique_ptr<RobotSpec>` 을 반환한다. 이게 자바와 가장 다른 점
- **복사 생성자를 `protected`** - 밖에서 값 복사를 못 하게 막고 `clone()` 만 통과시킨다
- rule of zero - 멤버가 전부 값 타입이라 `= default` 로 **깊은 복사가 공짜**가 됐다

**거스른 것 / 대가**

- 포인터 멤버가 하나라도 생기면 복사 생성자를 직접 써야 한다. 안 쓰면 **견본이 오염된다**
- `clone()` 안에 `new` 가 남는다 (`make_unique` 는 `protected` 복사 생성자에 접근할 수 없다)

## 9. 실행

### 이 폴더만 단독으로

```sh
cd robot/07_Prototype
make          # build/07_Prototype 에 실행 파일 생성
make run      # 빌드하고 바로 실행
make clean    # build/ 삭제
```

### 저장소 루트에서 (다른 패턴과 함께)

```sh
make robot                    # 로봇 예제 22개 전부 빌드 -> build/bin/robot_*
make run-robot-07_Prototype    # 이 예제만 빌드하고 실행
make run-robot-all            # 22개를 순서대로 실행
```

두 경로의 빌드 옵션은 같다 - `-std=c++20 -Wall -Wextra -Wpedantic -O1`, **경고 0개**를 유지한다.
산출물 위치만 다르다 - 단독은 `07_Prototype/build/`, 루트는 `build/bin/`.

## 10. 확인 질문

> `RobotSpec` 의 멤버 중 포인터가 하나라도 있는가?

없다. 그래서 `= default` 복사 생성자로 충분했다.
포인터를 하나 추가하는 순간 복사 생성자를 직접 써야 하고,
안 쓰면 4번 장면에서 **견본이 오염된다.**
