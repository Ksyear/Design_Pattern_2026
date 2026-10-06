# 03. Decorator - 라이다 스캔 전처리 파이프라인

> 원본 스캔을 필터로 겹겹이 감싼다. 감싼 것도 여전히 "스캔을 내놓는 것" 이라서
> 또 감쌀 수 있다. **감싸는 순서가 곧 사양이다.**
>
> 책 예제 : [`../../03_Decorator`](../../03_Decorator) (커피 + 첨가물)

## 1. 어떤 문제를 푸는가

라이다 드라이버가 올려 주는 값은 지저분하다. 측정 실패(0.0), 튀는 값(41.7m), 범위 초과(55m).
내비게이션에 넣기 전에 몇 단계를 거쳐야 하는데, **그 조합이 로봇마다 다르다.**

- 실내 배송 로봇 : 이상치 제거 → 중앙값 → 범위 자르기
- 실외 순찰 로봇 : 중앙값 두 번 → 범위 자르기
- 디버깅 중 : 아무것도 안 함

조합마다 클래스를 만들면 끝이 없다. 상속으로는 **실행 중에 쌓을 수도** 없다.
그래서 "필터도 스캔 소스다" 로 만들어서 **런타임에 겹쳐 쌓게** 했다.

## 2. 폴더가 곧 패턴 역할

| 폴더 / 파일 | 패턴 역할 | 하는 일 |
|---|---|---|
| [`scan/ScanSource.h`](scan/ScanSource.h) | **Component** | `read()` / `latencyMs()` / `pipeline()` |
| [`scan/RawLidar.*`](scan/RawLidar.h) | **ConcreteComponent** | 드라이버가 올려 주는 날것. 일부러 지저분하다 |
| [`filter/ScanFilter.*`](filter/ScanFilter.h) | **Decorator (추상)** | `ScanSource` **이면서** `ScanSource` 를 하나 들고 있다 |
| [`filter/DropOutlier.*`](filter/DropOutlier.h) | Concrete Decorator | 0.0 과 범위 초과를 앞 값으로 메운다 (+0.8ms) |
| [`filter/MedianFilter.*`](filter/MedianFilter.h) | Concrete Decorator | 이웃 3개의 중앙값 (+1.5ms) |
| [`filter/RangeClamp.*`](filter/RangeClamp.h) | Concrete Decorator | 신뢰 구간 밖을 자른다 (+0.3ms) |
| [`msg/LaserScan.h`](msg/LaserScan.h) | (데이터) | 거리 배열 하나로 줄인 스캔 |

## 3. 적용 방식 - "이면서 동시에"

```cpp
// filter/ScanFilter.h
class ScanFilter : public ScanSource {   // (1) ScanSource 이다
public:
	explicit ScanFilter(std::unique_ptr<ScanSource> source);
protected:
	std::unique_ptr<ScanSource> source_;  // (2) ScanSource 를 하나 갖고 있다
};
```

이 두 줄이 데코레이터의 전부다.

- **상속하는 이유**는 형식을 맞추기 위해서다 - 필터를 필터로 감쌀 수 있게
- **들고 있는 이유**는 실제 일을 안쪽에 맡기기 위해서다

각 필터는 "안쪽에 먼저 맡기고, 내 몫을 더해서 내보낸다" 를 반복한다.

```cpp
// filter/DropOutlier.cpp
LaserScan DropOutlier::read() const
{
	LaserScan scan = source_->read();   // 안쪽에 먼저 맡기고
	...                                  // 내 일을 하고
	return scan;                         // 내보낸다
}
double DropOutlier::latencyMs() const { return source_->latencyMs() + 0.8; }  // 누적
std::string DropOutlier::pipeline() const { return source_->pipeline() + " + drop_outlier"; }
```

`latencyMs()` 가 책의 `cost()` 자리다. **쌓일수록 늘어나는 값**이라는 점이 같다.
커피는 돈이 쌓이고, 로봇은 **지연이 쌓인다.** 로봇에서는 이쪽이 훨씬 무섭다.

### `protected` 를 쓴 두 곳 중 하나

이 저장소는 멤버를 `private` 로 두는 것이 규약인데 `source_` 만 `protected` 다.
파생 필터가 안쪽 스캔을 **실제로 읽어야 하기** 때문이다.
책의 `CondimentDecorator` 가 `beverage` 를 `protected` 로 둔 것과 같은 이유다.

## 4. 실행하면 보이는 것 - 순서가 사양이다

```
===== 2. 필터를 하나씩 씌워 간다 =====
  RawLidar + drop_outlier + median(3) + clamp
    지연 4.6 ms
    ranges =   1.20   1.18   1.18   1.25   1.25   1.28   1.28   1.28

===== 3. 순서를 바꾸면 결과가 달라진다 =====
  RawLidar + median(3) + drop_outlier + clamp
    지연 4.6 ms
    ranges =   1.20   1.18   1.18   1.25   1.30   1.30   1.30   1.30
```

**지연은 4.6ms 로 같은데 값이 다르다.**

원본의 5번째 값이 `41.70` 이다.

- 2번 : 이상치를 **먼저** 지우고 중앙값을 돌린다 → 41.70 이 사라진 뒤 평활화
- 3번 : 중앙값을 **먼저** 돌린다 → 41.70 이 이웃 칸으로 번진 뒤에 지운다

커피 첨가물은 모카와 휘핑의 순서를 바꿔도 값이 같다.
**스캔 필터는 다르다.** 이것이 데코레이터를 로봇에 쓸 때 가장 크게 걸리는 지점이다.

4번 장면은 **같은 필터를 두 번** 씌운다 (책의 모카 두 번). 더 매끈해지는 대신 지연이 5.8ms 로 는다.

## 5. 실제 ROS 2 대응

| 이 예제 | 실제 ROS 2 |
|---|---|
| 필터를 감싸는 코드 | `laser_filters` 의 YAML 필터 체인 - 나열 순서대로 감싸진다 |
| `ScanSource` | `filters::FilterBase<sensor_msgs::msg::LaserScan>` |
| 파이프라인 전체 | `image_pipeline` 의 노드 체인, PCL 필터 조합 |
| `latencyMs()` 누적 | 체인이 길어질수록 늘어나는 실제 처리 지연 |

`laser_filters` 는 YAML 에 필터 이름을 나열하면 그 순서대로 체인이 만들어진다.
**YAML 한 줄의 위치를 바꾸면 결과가 바뀐다** - 위 3번 장면이 실무에서 나타나는 방식이다.

## 6. 이 예제가 하지 않는 것

- `DropOutlier` 는 양옆 보간이 아니라 **바로 앞 값으로 메운다.** 실제로는 양옆을 쓴다
- 실제 `LaserScan` 의 `angle_min` / `angle_increment` / `intensities` 를 뺐다
- 시간(타임스탬프)이 없다. 시간 축 필터(예: 이동 평균)는 표현할 수 없다

## 7. 객체지향 관점 - 어떤 원칙을 어떻게 지켰나

| 원칙 | 이 예제에서 어떻게 했나 |
|---|---|
| **OCP** | 이 패턴의 교과서적 예. 기존 센서·필터를 고치지 않고 기능을 더한다 |
| **상속보다 구성** | 상속은 **형식을 맞추는 용도로만** 쓰고, 실제 일은 감싼 객체에 위임한다 |
| **구현이 아닌 인터페이스** | 원본도 10겹 파이프라인도 똑같이 `ScanSource` 다 |

**C++ 문법으로 지킨 것**

- `protected source_` - 이 저장소에서 `private` 규약을 깬 두 곳 중 하나.
  파생 필터가 안쪽 스캔을 실제로 읽어야 하므로 의도적으로 열었다
- `unique_ptr` 체인 = 바깥이 안쪽을 소유. 맨 바깥 하나만 살아 있으면 전체가 산다
- 생성자에서 `nullptr` 거부 - 감쌀 대상이 없는 필터는 태어나지 못한다

**거스른 것 / 대가**

- 객체 수가 늘고 호출 스택이 깊어져 디버깅이 어렵다
- **순서 의존성이 타입에 드러나지 않는다.** "이상치 제거를 먼저" 라는 요구를 컴파일러가 못 막는다

## 8. 실행

### 이 폴더만 단독으로

```sh
cd robot/03_Decorator
make          # build/03_Decorator 에 실행 파일 생성
make run      # 빌드하고 바로 실행
make clean    # build/ 삭제
```

### 저장소 루트에서 (다른 패턴과 함께)

```sh
make robot                    # 로봇 예제 22개 전부 빌드 -> build/bin/robot_*
make run-robot-03_Decorator    # 이 예제만 빌드하고 실행
make run-robot-all            # 22개를 순서대로 실행
```

두 경로의 빌드 옵션은 같다 - `-std=c++20 -Wall -Wextra -Wpedantic -O1`, **경고 0개**를 유지한다.
산출물 위치만 다르다 - 단독은 `03_Decorator/build/`, 루트는 `build/bin/`.

## 9. 확인 질문

> `RawLidar` 는 자기를 누가 감쌌는지 아는가? 필터는 자기가 무엇을 감쌌는지 아는가?

둘 다 모른다. 필터가 아는 것은 `ScanSource` 라는 형식뿐이다.
그래서 새 필터를 추가해도 기존 파일은 한 줄도 바뀌지 않는다 (OCP).
