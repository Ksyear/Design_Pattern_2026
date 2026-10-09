# 04·05. Factory Method + Abstract Factory - 현장 bringup 이 기종을 고르고, 부품 한 벌을 쥐여 준다

> 소스에는 주석이 없다. 설명은 전부 이 문서에 있다.
> 코드는 "무엇을 하는가"만 보이고, "왜 그렇게 했는가"는 여기서 읽는다.
>
> 책 예제 : [`../../04_FactoryMethod`](../../04_FactoryMethod) (피자 가게) · [`../../05_AbstractFactory`](../../05_AbstractFactory) (피자 원재료 공장) | 상위 문서 : [`../README.md`](../README.md)

---

## 0. 이 프로젝트는 정확히 무엇인가

**로봇을 현장에 띄우는 bringup 절차를, 팩토리 메소드와 추상 팩토리 두 패턴으로 짠 단일 실행 파일 예제다.**

한 문장으로 줄이면 이렇다.

> 창고와 캠퍼스, 두 현장이 같은 절차로 로봇을 띄우는데,
> **"어떤 기종을 만들지"** 는 임무에 따라 현장(서브클래스)이 정하고,
> **"어떤 부품 한 벌로 조립할지"** 는 현장이 들고 있는 부품 공장이 정한다.

책 4장이 두 패턴을 피자 가게(팩토리 메소드) + 원재료 공장(추상 팩토리) **한 예제**로 보여 주듯,
이 폴더도 둘을 한 프로그램에 합쳤다.

### 무엇인가 / 무엇이 아닌가

| 이것이다 | 이것이 아니다 |
|---|---|
| ROS 2 bringup 의 **구조**를 흉내 낸 학습용 예제 | 실제 ROS 2 패키지가 아니다. `rclcpp` 를 쓰지 않는다 |
| 표준 라이브러리만으로 빌드되는 `main()` 하나짜리 프로그램 | colcon / ament 빌드가 아니다 |
| 두 생성 패턴이 **한 절차 안에서 맞물리는 모습**을 보여 주는 자료 | pluginlib 로 `.so` 를 로드하지 않는다 (`make_unique` 로 대신한다) |
| 부품 사양은 **이야기가 서는 만큼만** 실제 제품에서 빌려 왔다 | 하드웨어 선정 가이드가 아니다 (9절 "카메라 짝은 예시 프로필이다") |

### 시뮬레이션하는 상황

현장 둘, 임무 둘.

| | 실내 창고 (`warehouse`) | 실외 캠퍼스 (`campus`) |
|---|---|---|
| 배송 (`delivery`) | 창고 배송 로봇 | 캠퍼스 배송 로봇 |
| 순찰 (`patrol`) | 창고 순찰 로봇 | 캠퍼스 순찰 로봇 |

`main()` 은 이 표에서 칸을 골라 5개 장면으로 재생한다.
1번 → 2번은 **임무만**, 2번 → 3번은 **현장만** 바꾼다. 두 축이 하나씩 움직이는 것을 보기 위해서다.

### 이 구조가 없으면 생기는 일

절차 한가운데에서 이렇게 짜면 두 가지가 무너진다.

```cpp
if (site == "warehouse" && mission == "delivery") { lidar = new Lidar2D(); localizer = new AmclLocalizer(); ... }
else if (site == "campus" && mission == "patrol") { lidar = new Lidar3D(); ... camera = new ThermalCamera(); }
...
```

- 기종이나 현장이 늘 때마다 **절차 파일을 연다.** 절차는 바뀐 적이 없는데도
- 부품을 하나씩 고르니 **"실내인데 GPS"** 같은 조합이 언젠가 반드시 만들어진다

그래서 달라지는 두 칸을 따로 뽑았다. 기종은 **상속**으로(팩토리 메소드), 부품 한 벌은 **구성**으로(추상 팩토리).
클래스 **2 + 2 개**로 로봇 **2 x 2 = 4가지**가 나온다.

---

## 1. 두 패턴을 어디에 썼는가

### 한눈에 - 패턴 역할 ↔ 실제 파일

| 폴더 / 파일 | 팩토리 메소드에서 | 추상 팩토리에서 |
|---|---|---|
| [`bringup/RobotBringup.*`](bringup/RobotBringup.h) | **Creator** | 팩토리를 소유하는 쪽 |
| [`bringup/WarehouseBringup.*`](bringup/WarehouseBringup.cpp) · [`CampusBringup.*`](bringup/CampusBringup.cpp) | Concrete Creator | 어느 Concrete Factory 를 쓸지 고르는 쪽 |
| [`platform/RobotPlatform.*`](platform/RobotPlatform.h) | **Product** | **Client** |
| [`platform/DeliveryRobot.*`](platform/DeliveryRobot.cpp) · [`PatrolRobot.*`](platform/PatrolRobot.cpp) | Concrete Product | Client |
| [`factory/PartsFactory.h`](factory/PartsFactory.h) | - | **Abstract Factory** |
| [`factory/IndoorPartsFactory.*`](factory/IndoorPartsFactory.cpp) · [`OutdoorPartsFactory.*`](factory/OutdoorPartsFactory.cpp) | - | Concrete Factory |
| [`part/Lidar.h`](part/Lidar.h) · [`Localizer.h`](part/Localizer.h) · [`DriveBase.h`](part/DriveBase.h) · [`Camera.h`](part/Camera.h) | - | Abstract Product 1~4 |
| `part/` 의 나머지 8개 | - | Concrete Product (4종 x 2벌) |
| [`main.cpp`](main.cpp) | Client (bringup 을 부르는 쪽) | - |

**`RobotPlatform` 은 역할이 둘이다.** 팩토리 메소드가 만들어 내는 제품이면서,
추상 팩토리에게 부품을 주문하는 클라이언트다. 두 패턴이 맞물리는 톱니가 이 클래스다.

### 적용 지점 ① - `launch()` 의 두 줄

[`bringup/RobotBringup.cpp:15-23`](bringup/RobotBringup.cpp#L15-L23)

```cpp
	std::unique_ptr<RobotPlatform> robot = createRobot(mission);
	if (!robot) {
		std::cout << "    이 현장에는 이 임무를 맡을 기종이 없다 - 중단\n";
		return nullptr;
	}
	std::cout << "    [팩토리 메소드] 기종       -> " << robot->name() << "\n";

	std::cout << "    [추상 팩토리]   부품 한 벌 -> " << parts_->profile() << "\n";
	robot->assemble(*parts_);
```

첫 줄(15행)이 **팩토리 메소드**, 마지막 줄(23행)이 **추상 팩토리**다. 나란히 놓으면 차이가 선명하다.

| | `createRobot(mission)` - 15행 | `assemble(*parts_)` - 23행 |
|---|---|---|
| 패턴 | 팩토리 메소드 | 추상 팩토리 |
| 고르는 것 | 기종 - 제품 **하나** | 부품 **한 벌** - 제품 **여러 개** |
| 수단 | **상속** - 서브클래스가 재정의한다 | **구성** - 생성자로 받은 `parts_` |
| 정해지는 때 | `launch()` 를 부를 때마다 (임무별) | bringup 을 만들 때 한 번 |

이 파일에는 구상 기종 이름도, 구상 부품 이름도 없다. 11절의 `grep` 이 증명이다.

### 적용 지점 ② - 절차는 닫고, 생성 한 칸만 연다

[`bringup/RobotBringup.h:15-22`](bringup/RobotBringup.h#L15-L22)

```cpp
	std::unique_ptr<RobotPlatform> launch(const std::string& mission) const;

protected:
	virtual std::unique_ptr<RobotPlatform> createRobot(const std::string& mission) const = 0;

private:
	std::string site_;
	std::unique_ptr<PartsFactory> parts_;
```

- `launch()` 에 **일부러 `virtual` 을 붙이지 않았다.** 서브클래스가 절차 자체를 바꿔 버리면 이 패턴의 의미가 없어진다.
  "절차는 닫고, 생성만 연다" 를 타입으로 강제한 것이다 (자바의 `final` 자리)
- `createRobot()` 은 `protected` 순수 가상 - 서브클래스는 **반드시** 채워야 하고, 바깥은 절차를 건너뛰고 기종만 만들 수 없다
- `parts_` 는 `private` - 서브클래스도 팩토리를 바꿔 끼울 수 없다. 생성자에서 한 번 넘기고 끝이다

### 적용 지점 ③ - 두 선택이 만나는 자리

[`bringup/WarehouseBringup.cpp:7-21`](bringup/WarehouseBringup.cpp#L7-L21)

```cpp
WarehouseBringup::WarehouseBringup()
	: RobotBringup("warehouse", std::make_unique<IndoorPartsFactory>())
{
}

std::unique_ptr<RobotPlatform> WarehouseBringup::createRobot(const std::string& mission) const
{
	if (mission == "delivery") {
		return std::make_unique<DeliveryRobot>("창고 배송 로봇");
	}
	if (mission == "patrol") {
		return std::make_unique<PatrolRobot>("창고 순찰 로봇");
	}
	return nullptr;
}
```

- **생성자(8행)** 가 부품 한 벌을 고른다 → 추상 팩토리 축
- **`createRobot()`(12-21행)** 이 기종을 고른다 → 팩토리 메소드 축

두 패턴의 **선택**이 이 클래스 하나에 모인다. 책의 `NYPizzaStore` 자리다.
이 클래스가 아는 구상 이름은 `IndoorPartsFactory` · `DeliveryRobot` · `PatrolRobot` **셋뿐**이고,
`Lidar2D` 같은 부품 이름은 모른다. [`CampusBringup.cpp`](bringup/CampusBringup.cpp) 는 8행의 팩토리와 기종 이름만 다르다.

### 적용 지점 ④ - 무엇을 주문할지는 기종이, 무엇이 올지는 팩토리가

[`platform/PatrolRobot.cpp:5-11`](platform/PatrolRobot.cpp#L5-L11)

```cpp
void PatrolRobot::assemble(const PartsFactory& parts)
{
	lidar_ = parts.createLidar();
	localizer_ = parts.createLocalizer();
	driveBase_ = parts.createDriveBase();
	camera_ = parts.createCamera();
}
```

[`DeliveryRobot.cpp`](platform/DeliveryRobot.cpp#L3-L8) 에는 10행(`createCamera`)이 없다. 차이는 그 한 줄뿐이다.

- **"카메라를 단다"** 는 기종이 정한다 → 팩토리 메소드 축
- **"RGB-D 냐 열화상이냐"** 는 팩토리가 정한다 → 추상 팩토리 축

책에서 `ClamPizza` 만 조개를 주문하고, 조개가 신선한지 냉동인지는 원재료 공장이 정하는 것과 같다.
팩토리는 인자로 **빌려 쓰고 돌려준다.** 로봇이 팩토리를 멤버로 들지 않는 이유는 9절에 있다.

### 적용 지점 ⑤ - 일관성이 보장되니까 판단이 안전해진다

[`platform/RobotPlatform.cpp:25-32`](platform/RobotPlatform.cpp#L25-L32)

```cpp
void RobotPlatform::planPath() const
{
	if (driveBase_->canRotateInPlace()) {
		std::cout << "    경로계획 : 제자리 회전을 써서 좁은 통로도 통과 (NavFn + DWB)\n";
	} else {
		std::cout << "    경로계획 : 최소 회전 반경을 지키는 곡선 경로 (Smac Hybrid-A*)\n";
	}
}
```

이 `if` 가 안전한 이유는 **부품군이 일관되기 때문**이다.
부품을 따로 고를 수 있었다면 "GPS 로 측위하는데 제자리 회전 가능" 같은
앞뒤 안 맞는 상태가 들어올 수 있고, 그러면 이 분기의 전제가 깨진다.

### 적용 지점 ⑥ - `main` 은 현장 둘만 안다

[`main.cpp:10-11`](main.cpp#L10-L11)

```cpp
	const WarehouseBringup warehouse;
	const CampusBringup campus;
```

`main.cpp` 에 나오는 구상 이름은 이 둘이 전부다. 기종도, 부품도, 팩토리도 모른다.
나머지는 [`main.cpp:29-32`](main.cpp#L29-L32) 처럼 `RobotPlatform` 하나로 다룬다.

---

## 2. 왜 축이 둘인가 - 그리고 왜 한 벌로 묶나

| 축 | 값 | 무엇으로 정해지나 | 패턴 |
|---|---|---|---|
| **기종** - 무엇을 만드나 | 배송 / 순찰 | 임무 (`launch("patrol")`) | 팩토리 메소드 |
| **현장** - 어떤 부품 한 벌로 | 실내 / 실외 | 어느 bringup 을 쓰나 | 추상 팩토리 |

두 축은 서로 독립이다. 둘 다 상속으로 골랐다면 "실내 배송" "실외 배송" "실내 순찰" "실외 순찰" 처럼
**조합마다** 클래스가 필요했다. 한 축을 구성으로 빼서 **곱셈을 덧셈으로** 바꿨다 ([`../15_Bridge`](../15_Bridge) 와 같은 발상).

부품을 한 벌로 묶는 이유는 **로봇 부품이 서로 어울려야 하기** 때문이다. 이건 취향이 아니라 물리적 제약이다.

| | 센서 | 측위 | 구동계 | 카메라 (순찰 로봇만) |
|---|---|---|---|---|
| 실내 | 2D 라이다 | AMCL (지도 기반) | 차동 구동 (제자리 회전 가능) | RGB-D (근거리 깊이) |
| 실외 | 3D 라이다 | RTK-GPS + IMU | 애커만 조향 (제자리 회전 불가) | 열화상 (야간 순찰) |

가로줄을 섞으면 실제로 고장 난다.

- 실내 로봇에 GPS 를 달면 **신호가 안 잡힌다**
- 애커만 차량에 제자리 회전을 전제한 경로 계획기를 물리면 **경로를 못 따라간다**
- 실외에서 2D 라이다만 쓰면 **경사와 웅덩이를 못 본다**

부품을 하나씩 고르는 API 를 만들면 이런 조합이 **언젠가 반드시 만들어진다.**
그래서 고르는 단위를 부품이 아니라 **"한 벌"** 로 올렸다.

---

## 3. 두 패턴의 관계 - 그리고 전략 패턴과의 차이

### 둘은 사실 친척이다

[`PartsFactory.h:16-19`](factory/PartsFactory.h#L16-L19) 의 `create...()` 하나하나가 **팩토리 메소드 모양**이다.
"무엇을 만들지" 를 서브클래스(`IndoorPartsFactory`)가 정한다는 점이 같다.
추상 팩토리는 그런 메소드 여러 개를 **"한 벌" 이라는 규칙으로 묶은 것**이다.

갈리는 지점은 **그 생성 메소드를 누가 부르느냐**다.

| | 생성 메소드를 부르는 쪽 |
|---|---|
| 팩토리 메소드 | **Creator 자신** - `launch()` 가 자기 `createRobot()` 을 부른다 |
| 추상 팩토리 | **바깥 클라이언트** - `RobotPlatform` 이 넘겨받은 팩토리의 `create...()` 를 부른다 |

### 전략 패턴과 헷갈릴 때

[`../01_Strategy`](../01_Strategy) 와 구조가 비슷해 보이지만 **결정 주체와 시점**이 다르다.

| | 누가 정하나 | 언제 갈리나 |
|---|---|---|
| Strategy (01) | 바깥(클라이언트)이 정해서 **넣어 준다** | 실행 중에도 교체 가능 |
| Factory Method (이 예제의 기종 축) | **서브클래스가 스스로** 정한다 | 어느 서브클래스를 쓰느냐로 갈린다 |
| Abstract Factory (이 예제의 부품 축) | 생성자에서 **한 번** 넘겨받는다 | bringup 을 만들 때 고정 |

`ControllerServer` 는 전략을 세터로 갈아 끼울 수 있었다.
`WarehouseBringup` 은 실외 부품 한 벌로 바꿀 수 없다 - 그게 이 현장의 정체성이다.

---

## 4. 파일별 설명

### `part/` - 부품 (Abstract Product 4종 + Concrete Product 8개)

| 추상 제품 | 실내 | 실외 | 메소드 |
|---|---|---|---|
| `Lidar` | `Lidar2D` - `/scan` (LaserScan) | `Lidar3D` - `/points` (PointCloud2) | `spec()` / `topic()` |
| `Localizer` | `AmclLocalizer` - 기준 좌표계 `map` | `GpsLocalizer` - 기준 좌표계 `utm` | `spec()` / `frame()` |
| `DriveBase` | `DiffDriveBase` - 시리얼 | `AckermannBase` - CAN 버스 | `spec()` / `canRotateInPlace()` / `onConfigure()` |
| `Camera` | `RgbdCamera` | `ThermalCamera` | `spec()` / `topic()` |

- **`DriveBase::onConfigure()`** ([`DriveBase.h:11`](part/DriveBase.h#L11)) 는 ros2_control 의
  `hardware_interface::SystemInterface::on_configure()` 자리다. 포트를 열고 파라미터를 반영한다.
  어떤 구동계든 이 이름으로 설정하면 bringup 절차가 똑같이 다룰 수 있다
- **`AckermannBase::canRotateInPlace()`** 가 `false` 를 돌려주는 것([`AckermannBase.cpp:10-13`](part/AckermannBase.cpp#L10-L13))이
  경로 계획기를 바꾸는 근거가 된다 (적용 지점 ⑤)
- **`Camera`** 는 순찰 로봇만 주문한다 (책의 `Clams` 자리).
  이 "종류" 하나를 추가하느라 `PartsFactory` 와 구상 팩토리 둘을 **전부 열었다** - 추상 팩토리의 대가다 (8절)
- 측위가 바뀌면 **좌표계도 따라 바뀐다**(`map` → `utm`). 이것도 "어울림" 의 일부다

### `factory/` - Abstract Factory + Concrete Factory 2개

- **`PartsFactory`** - `createLidar` / `createLocalizer` / `createDriveBase` / `createCamera` 네 개와 `profile()`
- **`IndoorPartsFactory`** - 2D 라이다 + AMCL + 차동 구동 + RGB-D, 프로필 `"실내 창고형"`
- **`OutdoorPartsFactory`** - 3D 라이다 + RTK-GPS + 애커만 조향 + 열화상, 프로필 `"실외 캠퍼스형"`

구상 부품 이름(`Lidar2D` 등)이 나오는 곳은 **이 폴더의 `.cpp` 두 개뿐**이다.
모든 생성 메소드가 `const` 다 - 팩토리는 **상태가 없고**, 만드는 방법만 안다.

### `platform/` - 기종 (팩토리 메소드의 Product = 추상 팩토리의 Client)

- **`RobotPlatform`** - 구상 부품 이름을 전혀 모른다.
  어떤 부품 **종류**를 주문할지는 기종(서브클래스)이, 그 부품이 **어떤 모델**인지는 팩토리가 정한다
  - `assemble()` 은 순수 가상 (책의 `Pizza::prepare()`)
  - `printBom()` 은 가상 - 순찰 로봇이 카메라 두 줄을 덧붙인다
  - `configure()` / `planPath()` 는 비가상 - 모든 기종이 같다
  - 부품 멤버 3개(`lidar_` 등)는 `protected` - 기종이 채워야 하므로 통로를 열었다 ([`RobotPlatform.h:22-25`](platform/RobotPlatform.h#L22-L25))
- **`DeliveryRobot`** - 부품 3종만 주문한다 (책의 `CheesePizza`)
- **`PatrolRobot`** - 3종 + 카메라. 카메라는 이 기종만 쓰므로 자기 `private` 멤버로 든다 (책의 `ClamPizza`)

### `bringup/` - Creator + Concrete Creator 2개

- **`RobotBringup`** - 절차 `launch()` 와 팩토리 메소드 `createRobot()`, 그리고 부품 한 벌 `parts_`.
  절차는 `기종 생성 → 부품 조립 → 구동계 설정 → 부품 목록 보고 → 경로계획 확인 → 활성 보고` 순서로 고정이다.
  모르는 임무면 아무것도 만들지 않고 `nullptr` 을 돌려준다 ([`RobotBringup.cpp:16-19`](bringup/RobotBringup.cpp#L16-L19))
- **`WarehouseBringup`** - 실내 한 벌 + 배송 / 순찰 기종 (책의 `NYPizzaStore`)
- **`CampusBringup`** - 실외 한 벌 + 배송 / 순찰 기종 (책의 `ChicagoPizzaStore`)

### `main.cpp` - 조립과 호출만

- 현장 둘을 `const` 로 만든다 - `launch()` 와 `createRobot()` 이 `const` 라서 가능하다
- `launch()` 가 돌려준 로봇은 `fleet` 이 **받아 든다** (소유권이 호출자에게 넘어온다)
- 4번 장면의 `mowing` 은 `fleet` 에 넣지 않는다. `nullptr` 이므로 5번 루프에서 역참조하면 터진다

---

## 5. 실행하면 보이는 것

```
===== 1. 창고 배송 로봇 =====
  [warehouse] bringup 시작 - 임무 delivery
    [팩토리 메소드] 기종       -> 창고 배송 로봇
    [추상 팩토리]   부품 한 벌 -> 실내 창고형
    구동계 설정 : /dev/ttyUSB0 열기, 115200bps, 휠 반경 0.033m 반영
    센서   : 2D 라이다 (RPLIDAR A2, 평면 360도, 12m)
             퍼블리시 /scan (sensor_msgs/LaserScan)
    측위   : AMCL (미리 만든 점유 격자 지도에 스캔을 맞춘다)
             기준 좌표계 map
    구동계 : 차동 구동 (좌우 바퀴 + 캐스터)
    경로계획 : 제자리 회전을 써서 좁은 통로도 통과 (NavFn + DWB)
    활성 완료 : 창고 배송 로봇

===== 2. 임무만 바꾼다 - 팩토리 메소드 축 (카메라가 붙는다) =====
  [warehouse] bringup 시작 - 임무 patrol
    [팩토리 메소드] 기종       -> 창고 순찰 로봇
    [추상 팩토리]   부품 한 벌 -> 실내 창고형
    ... (1번과 같은 부품 줄)
    카메라 : RGB-D 카메라 (RealSense D435, 0.3~3m 근거리 깊이)
             퍼블리시 /camera/color/image_raw (sensor_msgs/Image)
    경로계획 : 제자리 회전을 써서 좁은 통로도 통과 (NavFn + DWB)
    활성 완료 : 창고 순찰 로봇

===== 3. 현장만 바꾼다 - 추상 팩토리 축 (부품이 한 벌째 바뀐다) =====
  [campus] bringup 시작 - 임무 patrol
    [팩토리 메소드] 기종       -> 캠퍼스 순찰 로봇
    [추상 팩토리]   부품 한 벌 -> 실외 캠퍼스형
    구동계 설정 : CAN 버스(can0) 열기, 조향 모터 원점 맞추기
    센서   : 3D 라이다 (Velodyne VLP-16, 16채널, 100m)
             퍼블리시 /points (sensor_msgs/PointCloud2)
    측위   : RTK-GPS + IMU 융합 (robot_localization 의 navsat_transform)
             기준 좌표계 utm
    구동계 : 애커만 조향 (자동차형, 최소 회전 반경 2.4m)
    카메라 : 열화상 카메라 (FLIR Boson, 조명 없는 야간에도 사람을 본다)
             퍼블리시 /thermal/image_raw (sensor_msgs/Image)
    경로계획 : 최소 회전 반경을 지키는 곡선 경로 (Smac Hybrid-A*)
    활성 완료 : 캠퍼스 순찰 로봇

===== 4. 현장이 모르는 임무 =====
  [campus] bringup 시작 - 임무 mowing
    이 현장에는 이 임무를 맡을 기종이 없다 - 중단
  결과 : nullptr - 아무것도 만들지 않았다

===== 5. 가동 중인 로봇 3대 =====
  창고 배송 로봇
    경로계획 : 제자리 회전을 써서 좁은 통로도 통과 (NavFn + DWB)
  창고 순찰 로봇
    경로계획 : 제자리 회전을 써서 좁은 통로도 통과 (NavFn + DWB)
  캠퍼스 순찰 로봇
    경로계획 : 최소 회전 반경을 지키는 곡선 경로 (Smac Hybrid-A*)
```

장면을 **둘씩 짝지어** 볼 것.

| 비교 | 바꾼 것 | 바뀐 출력 | 그대로인 출력 |
|---|---|---|---|
| 1 → 2 | 임무만 (`delivery` → `patrol`) | 기종 줄, **카메라 두 줄이 새로 생김** | 부품 한 벌, 센서·측위·구동계 전부 |
| 2 → 3 | 현장만 (`warehouse` → `campus`) | 부품 한 벌 줄, 센서·측위·구동계·**카메라 모델**·경로계획 | 카메라가 **있다**는 사실 (기종이 같으므로) |

- 4번은 임무를 문자열로 받는 대가다. 없는 임무는 **실행해 봐야** 안다
- 5번은 bringup 이 끝난 로봇들을 `RobotPlatform` 하나로만 돌린다. 로봇이 팩토리를 들고 있지 않으므로 조립 뒤에도 혼자 일한다

**`RobotBringup.cpp` 와 `RobotPlatform.cpp` 는 어느 장면을 위해서도 한 글자도 바뀌지 않았다.**
바뀐 것은 `main.cpp` 에서 부른 bringup 과 임무 문자열뿐이다.

---

## 6. 대응표

### 책 예제 ↔ 이 예제

| 책 (4장) | 이 예제 |
|---|---|
| `PizzaStore` / `orderPizza()` | `RobotBringup` / `launch()` |
| `createPizza(type)` | `createRobot(mission)` |
| `NYPizzaStore` / `ChicagoPizzaStore` | `WarehouseBringup` / `CampusBringup` |
| `PizzaIngredientFactory` | `PartsFactory` |
| `NYPizzaIngredientFactory` / `ChicagoPizzaIngredientFactory` | `IndoorPartsFactory` / `OutdoorPartsFactory` |
| `Dough` / `Sauce` / `Cheese` / `Clams` | `Lidar` / `Localizer` / `DriveBase` / `Camera` |
| `Pizza::prepare()` | `RobotPlatform::assemble()` |
| `CheesePizza` / `ClamPizza` | `DeliveryRobot` / `PatrolRobot` |

공장을 쥐는 방식은 **일부러 바꿨다** - 9절 "왜 로봇은 팩토리를 들고 있지 않나".

### 이 예제 ↔ 실제 ROS 2

| 이 예제 | 실제 ROS 2 |
|---|---|
| `launch()` | 런치 파일 + `controller_manager` 의 로드 → 설정 → 활성 순서 |
| `createRobot(mission)` | 기종 인자로 어느 URDF / xacro 를 올릴지 고르는 자리 (예: TurtleBot3 의 `TURTLEBOT3_MODEL=burger` / `waffle` / `waffle_pi`) |
| `PartsFactory` | 로봇 프로필 - 센서·측위·구동계를 묶은 한 벌 |
| `IndoorPartsFactory` | `indoor_robot.yaml` + 대응하는 URDF / xacro 매크로 |
| `profile()` | `robot_type` 파라미터 |
| `createDriveBase()` | pluginlib 이 `robot_description` 의 `<ros2_control>` 태그를 읽고 하드웨어 플러그인을 올리는 자리 |
| `DriveBase::onConfigure()` | `hardware_interface::SystemInterface` 의 `on_configure()` (실제 인터페이스는 `on_init` / `on_configure` / `on_activate` / `read` / `write`) |
| `planPath()` 의 분기 | 기종에 따라 다른 플래너 플러그인을 고르는 launch 로직 (Nav2 의 Smac Hybrid-A* 는 애커만 차량을 지원한다) |

실제로는 런치 인자·YAML·xacro 조건부가 이 역할을 나눠 맡는다.
**"절차는 하나, 기종은 인자로, 부품은 한 벌로" 라는 발상 자체는 같다.**

---

## 7. C++ 문법 메모

- **`virtual` 을 안 붙인 `launch()`** - "이 절차는 못 바꾼다" 를 타입으로 강제한다. 자바의 `final` 에 해당한다
- **`protected` 순수 가상 `createRobot()`** - 서브클래스는 반드시 채우고, 바깥은 부를 수 없다
- **`unique_ptr` 반환** - "소유권이 호출자에게 넘어간다" 는 선언. `main` 의 `fleet` 이 받아 든다
- **`unique_ptr<PartsFactory>` 멤버 + `const PartsFactory&` 인자** - bringup 은 팩토리를 **소유**하고, 로봇은 **빌려 쓴다**
- **`using RobotPlatform::RobotPlatform;`** - 상속 생성자. 기종 클래스는 생성자를 다시 쓰지 않는다 (`explicit` 도 그대로 물려받는다)
- **`virtual ~...() = default`** - 모든 추상 타입에 있다. 없으면 `unique_ptr<RobotPlatform>` 이 파생 객체를 지울 때 미정의 동작이다
- **`const` 객체와 `const` 멤버 함수** - `main` 의 현장 둘이 `const` 인 것은 `launch()` / `createRobot()` 이 `const` 라서 가능하다
- **`configure()` 는 비 `const`** - `onConfigure()` 가 장치 상태를 바꾸는 동작이기 때문이다.
  `unique_ptr` 의 `->` 는 얕은 `const` 라 `const` 함수에서도 컴파일은 되지만, 그렇게 쓰면 약속이 거짓말이 된다
- **`if (!robot)`** - 팩토리 메소드가 `nullptr` 을 돌려줄 수 있으면 절차가 그 경우를 막아야 한다 (책의 `orderPizza()` 도 같다)

---

## 8. OOP 원칙

| 원칙 | 이 예제에서 어떻게 했나 |
|---|---|
| **DIP** - 추상에 의존하라 | `RobotBringup` 은 `RobotPlatform` · `PartsFactory` 에만, `RobotPlatform` 은 추상 부품 4종에만 의존한다 |
| **캡슐화** | `make_unique` 가 나오는 자리를 두 곳으로 몰았다 - 기종은 구상 bringup, 부품은 구상 팩토리 |
| **할리우드 원칙** | 서브클래스가 `launch()` 를 부르지 않는다. `launch()` 가 `createRobot()` 을 부른다 |
| **구성 > 상속** | 부품 한 벌을 상속이 아니라 `parts_` 로 받아 기종 축과 곱해지지 않게 했다 (2절) |
| **OCP** | 방향에 따라 다르다 - 아래 표 |

OCP 를 지켰는지는 **추가할 때 여는 기존 파일 수**로 센다.

| 추가하는 것 | 새로 만드는 파일 | 여는(고치는) 기존 파일 |
|---|---|---|
| **새 현장 + 부품 한 벌** (예: Gazebo 시뮬) | `SimBringup`, `SimPartsFactory`, 시뮬 부품 4개 | **없다** (`main.cpp` 에서 쓰는 줄만) |
| **새 기종** (예: 점검 로봇) | `InspectionRobot` | `WarehouseBringup.cpp`, `CampusBringup.cpp` - `createRobot()` 에 `if` 하나씩 |
| **새 부품 종류** (카메라 - **이번에 실제로 했다**) | `Camera.h` + 구상 2개 | `PartsFactory.h`, `IndoorPartsFactory.*`, `OutdoorPartsFactory.*` 전부 |

마지막 줄이 추상 팩토리의 값이다. 부품 *군*을 추가하는 것은 쉽고, 부품 *종류*를 추가하는 것은 비싸다.
가운데 줄은 기종을 문자열로 고르는 데서 오는 비용이다 - **모든 현장의 `createRobot()` 을 연다.**

---

## 9. 설계 판단과 한계

### 왜 로봇은 팩토리를 들고 있지 않나 - 책과 일부러 다르게 한 곳

| | 책 ([`../../05_AbstractFactory`](../../05_AbstractFactory)) | 이 예제 |
|---|---|---|
| 공장을 누가 갖고 있나 | 구상 가게(`NYPizzaStore`)가 멤버로 | 기반 Creator(`RobotBringup`)가 `unique_ptr<PartsFactory>` 로 |
| 제품이 공장을 어떻게 쓰나 | `Pizza` 가 `const PizzaIngredientFactory&` 를 **멤버로 들고** `prepare()` 에서 쓴다 | `assemble(const PartsFactory&)` **인자로 빌려 쓰고 끝낸다** |

피자는 상자에 담기면 끝이지만 **로봇은 bringup 이 끝난 뒤에도 오래 일한다.**
제품이 참조 멤버로 팩토리를 들고 있으면, 팩토리 주인(bringup)이 먼저 사라질 때 **매달린 참조**가 남는다.
빌려 쓰고 돌려주면 그 위험이 구조적으로 없다. 기반 클래스가 팩토리를 쥔 덕분에
`launch()` 안에서 두 패턴이 **가까운 두 줄**로 보이게 된 것은 덤이다.

### 카메라 짝은 예시 프로필이다

실내에 RGB-D, 실외에 열화상을 짝지은 것은 **"순찰은 실외 야간에도 돌아야 한다"** 는 시나리오 때문이다.
RGB-D 카메라가 실외에서 안 된다는 뜻이 **아니다** - RealSense D400 계열은 햇빛 아래에서도 동작한다.
라이다·GPS 짝처럼 물리적으로 강제되는 조합이 아니라, **요구사항이 고른 조합**이라는 점을 구분해서 읽을 것.

### 이 예제의 한계

- **임무가 문자열이다.** 오타나 없는 임무는 4번 장면처럼 실행해야 드러난다.
  `enum class` 로 바꾸면 컴파일러가 잡는다 ([`../12_Mediator`](../12_Mediator) 의 `Event` 처럼)
- **두 현장의 `createRobot()` 이 이름만 빼고 같다.** 책의 `NYPizzaStore` / `ChicagoPizzaStore` 도 그렇다.
  거슬린다고 기종 선택을 기반 클래스로 올리면 팩토리 메소드가 사라진다 -
  "현장마다 기종 구성이 달라질 수 있다" 는 여지를 남긴 값이다
- 부품 간 호환성을 **타입으로 강제하지는 않는다.** 팩토리를 새로 쓰면 여전히 엉뚱한 조합을 만들 수 있다.
  이 패턴이 막는 것은 "실수로 섞이는 것" 이지 "작정하고 섞는 것" 이 아니다
- 부품 멤버가 `protected` 다. 책의 `Pizza` 도 같지만, 이 저장소에서 `protected` 는 예외적으로만 쓴다
- 기종마다 `assemble()` 에 같은 세 줄이 반복된다 (책의 `CheesePizza` / `ClamPizza` 도 같다)
- 상속 축(기종)은 **런타임 교체가 불가능하다** (그게 필요하면 [`../01_Strategy`](../01_Strategy))
- 소스 파일 38개. 패턴 둘을 보여 주는 값이지만, **작은 프로그램에서는 손해다**

### 이 예제가 하지 않는 것

- pluginlib 도 `.so` 로딩도 없다. `make_unique` 로 대신한다
- `read()` / `write()` 제어 주기가 없다 (그쪽은 [`../16_TemplateMethod`](../16_TemplateMethod) 가 다룬다)
- 라이프사이클 전이 실패 처리가 없다 (그쪽은 [`../21_State`](../21_State) 가 다룬다)
- **합치면서 뺀 것** : 합치기 전 04 에는 6축 팔(UR5, EtherCAT) 드라이버와 Gazebo 시뮬 드라이버가 있었다.
  이야기를 이동 로봇 한 계열로 모으느라 뺐다. 시뮬은 "부품 한 벌" 로 다시 넣을 수 있다 - 11절 문제 2

---

## 10. 실행

### 이 폴더만 단독으로

```sh
cd robot/04_05_Factory
make          # build/04_05_Factory 에 실행 파일 생성
make run      # 빌드하고 바로 실행
make clean    # build/ 삭제
```

### 저장소 루트에서 (다른 패턴과 함께)

```sh
make robot                        # 로봇 예제 전부 빌드 -> build/bin/robot_*
make run-robot-04_05_Factory      # 이 예제만 빌드하고 실행
make run-robot-all                # 전부 순서대로 실행
```

두 경로의 빌드 옵션은 같다 - `-std=c++20 -Wall -Wextra -Wpedantic -O1`, **경고 0개**를 유지한다.
산출물 위치만 다르다 - 단독은 `04_05_Factory/build/`, 루트는 `build/bin/`.

---

## 11. 확인 문제

> **1.** `RobotBringup.*` 과 `RobotPlatform.*` 에 구상 기종·부품·팩토리 이름이 몇 번 나오는가?
> 구상 bringup 은 구상 이름을 몇 개 아는가?

0번, 3개(기종 2 + 팩토리 1)다. 기종이나 현장이 늘어도 앞의 0 은 변하지 않는다.
주석이 없으니 `grep` 이 곧 증명이다.

```sh
grep -n "DeliveryRobot\|PatrolRobot\|Lidar2D\|GpsLocalizer\|IndoorPartsFactory" \
	bringup/RobotBringup.* platform/RobotPlatform.*      # 0건이어야 한다
```

> **2.** Gazebo 시뮬레이션 현장을 추가하려면 기존 파일을 몇 개 열어야 하는가?

`SimPartsFactory`(시뮬 라이다 · 시뮬 측위 · 시뮬 구동계 · 시뮬 카메라)와 `SimBringup` 을 **새로 만들 뿐**,
기존 파일은 `main.cpp` 말고 열지 않는다. 합치기 전 04 의 `SimDriver` 가 하던 이야기 -
**"같은 인터페이스라서 실기와 시뮬을 같은 코드로 돌린다"** - 가 부품 한 벌 추가로 돌아온다.

> **3.** 배송 로봇에도 카메라를 달고 싶다. 어느 파일을 고치는가?

`DeliveryRobot.*` 한 곳이다 (`camera_` 멤버, `assemble()` 에 한 줄, `printBom()` 재정의).
팩토리는 이미 카메라를 만들 줄 알고, 실내냐 실외냐에 맞는 카메라는 **알아서** 따라온다.
두 축이 독립이라는 말이 이것이다.

> **4.** `launch()` 에 `virtual` 을 붙이면 어떤 원칙이 깨지는가?

할리우드 원칙과 "절차는 닫고 생성만 연다" 는 약속이다. 서브클래스가 `launch()` 를 재정의하면
부품 조립을 건너뛰거나 순서를 바꾼 bringup 이 생길 수 있다. 그 순간 적용 지점 ⑤의 `if` 가 기대던 전제도 같이 흔들린다.
