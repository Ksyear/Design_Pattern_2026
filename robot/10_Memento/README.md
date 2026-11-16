# 10. Memento - 주행 체크포인트와 복구

> 상태를 밖으로 빼서 보관하되, **보관하는 쪽은 그 내용을 볼 수 없다.**
> C++ 에서는 중첩 클래스 + `friend` 로 만든다.
>
> 책 예제 : [`../../10_Memento`](../../10_Memento) (RPG 세이브 슬롯)

## 1. 어떤 문제를 푸는가

긴 임무 도중 AMCL 파티클이 발산하면 추정 위치가 지도 밖으로 튄다.
그때 필요한 것은 **"마지막으로 확실했던 지점으로 되돌리기"** 다.

순진한 방법은 `Navigator` 의 좌표를 전부 `public` 으로 열고 밖에서 복사해 두는 것이다.
그러면 캡슐화가 무너진다 - 아무나 로봇의 추정 위치를 **직접 쓸 수 있게** 된다.

메멘토가 푸는 것이 정확히 이 긴장이다.

> 상태를 **밖으로 꺼내야 한다** ↔ 상태는 **감춰져 있어야 한다**

## 2. 폴더가 곧 패턴 역할

| 폴더 / 파일 | 패턴 역할 | 하는 일 |
|---|---|---|
| [`nav/Navigator.*`](nav/Navigator.h) | **Originator** | 상태를 갖고, 스냅샷을 떠 주고, 받아서 복원한다 |
| `Navigator::Snapshot` (중첩 클래스) | **Memento** | 좌표·경유지·배터리를 담는다. 전부 `private` |
| [`save/CheckpointStack.*`](save/CheckpointStack.h) | **Caretaker** | 스냅샷을 **보관만** 한다. 내용을 못 본다 |

## 3. 적용 방식 - 중첩 클래스 + `friend`

```cpp
// nav/Navigator.h
class Navigator {
public:
	class Snapshot {
	public:
		const std::string& label() const;   // 보관하는 쪽에 허락된 유일한 정보

	private:
		friend class Navigator;             // Navigator 만 만들고 읽을 수 있다
		Snapshot(std::string label, double x, double y, double yaw, int waypointIndex, double battery);

		std::string label_;
		double x_;
		double y_;
		...
	};
	...
};
```

세 가지가 동시에 성립한다.

1. 멤버가 `private` 이라 **아무도 내용을 못 본다**
2. `friend` 덕분에 **`Navigator` 만** 만들고 읽을 수 있다
3. 생성자도 `private` 이라 **`Navigator` 밖에서는 스냅샷을 만들 수조차 없다**

자바의 내부 클래스 접근 규칙을 C++ 에서 재현한 것이다.

```cpp
// nav/Navigator.cpp
void Navigator::restore(const Snapshot& snapshot)
{
	x_ = snapshot.x_;      // friend 라서 private 멤버에 손이 닿는다
	y_ = snapshot.y_;
	...
}
```

### Caretaker 가 볼 수 있는 것은 이름표 하나뿐

```cpp
// save/CheckpointStack.cpp
void CheckpointStack::list() const
{
	for (const Navigator::Snapshot& s : stack_) {
		std::cout << " [" << s.label() << ']';   // label() 말고는 부를 게 없다
	}
}
```

> **`CheckpointStack.cpp` 안에서 `s.x_` 를 읽으려고 하면 컴파일이 안 된다.**

`private` 이고 `friend` 도 아니기 때문이다.
"들고만 있을 수 있다" 가 문법으로 강제된다 - 규약이나 주석이 아니라.

## 4. 실행하면 보이는 것

```
===== 4. 주행 중 로컬라이제이션 발산 =====
    주행 -> (41.0, -3.0)
  AMCL 파티클 발산 - 추정 위치가 지도 밖으로 튐
  [상태] 위치 (41.0, -3.0)  방위 210.0  경유지 2  배터리 77%

===== 5. 마지막 확실한 지점으로 복구 =====
  보관 중인 체크포인트 : [복도 진입] [교차로]
    체크포인트 '교차로' 로 복원
  [상태] 위치 (5.0, 6.0)  방위 90.0  경유지 2  배터리 82%
```

복원된 것이 **좌표만이 아니다.** 경유지 번호도, 배터리 추정치(77% → 82%)도 같이 돌아갔다.
스냅샷은 "상태 한 벌" 이지 필드 하나가 아니다.

6번 장면에서는 스택을 한 번 더 꺼내 **더 이전 지점**으로 간다.
`CheckpointStack` 이 스택이라서 가능한 일이고, 이 자료구조 선택은 Caretaker 의 자유다.

## 5. 09_Command 의 `undo()` 와 무엇이 다른가

| | 09 Command `undo()` | 10 Memento `restore()` |
|---|---|---|
| 방식 | **역연산** (앞으로 1m → 뒤로 1m) | **상태 덮어쓰기** |
| 필요한 것 | 반대 동작을 정의할 수 있어야 한다 | 상태를 통째로 떠 둘 수 있어야 한다 |
| 되돌림 범위 | 한 단계씩 | **임의 지점으로 점프** |
| 비용 | 실제로 움직여야 한다 | 메모리에 상태 한 벌 |

`GripCommand` 가 `previousClosed_` 를 들고 있던 것은 **작은 메멘토**다.
그게 커지면 이 패턴이 된다.

## 6. 실제 로봇에서의 자리 - 그리고 큰 한계

| 이 예제 | 실무 |
|---|---|
| `save()` / `restore()` | nav2 웨이포인트 재시도, 임무 롤백 |
| 복원 지점 | AMCL 의 `/initialpose` 재설정 |
| `CheckpointStack` | 작업 셀의 공정 롤백 기록 |

**그런데 여기서 중요한 한계가 있다.**

```cpp
// main.cpp 끝의 주석
// 복원은 "추정 상태" 만 되돌린다.
// 로봇의 실제 물리 위치는 그대로다.
```

5번 장면에서 좌표가 (5.0, 6.0) 으로 돌아갔지만, **로봇은 실제로 움직이지 않았다.**
되돌린 것은 "내가 어디 있다고 믿는가" 뿐이다.

진짜 시스템에서는 복원 후 반드시 이 단계가 따라붙는다.

1. 센서로 주변을 다시 관측한다
2. 복원된 추정치가 관측과 맞는지 검증한다
3. 안 맞으면 전역 위치 추정(global localization)을 다시 돌린다

**메멘토는 "소프트웨어 상태" 를 되돌릴 뿐, 물리 세계는 되돌리지 못한다.**
[`../09_Command`](../09_Command) 의 `undo()` 가 슬립을 남기는 것과 같은 종류의 한계다.

## 7. 이 예제가 하지 않는 것

- 스냅샷을 파일로 저장하지 않는다. 프로세스가 죽으면 체크포인트도 사라진다
- 복원 후 검증 단계가 없다 (위에서 말한 그 단계)
- 스냅샷 크기가 작다. 실제로는 코스트맵이나 파티클 전체를 떠야 할 수도 있고,
  그러면 **메모리와 복사 비용**이 실제 문제가 된다
- `pop()` 은 비었을 때 예외를 던진다. `empty()` 로 먼저 확인하는 것은 호출한 쪽 책임이다

## 8. 객체지향 관점 - 어떤 원칙을 어떻게 지켰나

| 원칙 | 이 예제에서 어떻게 했나 |
|---|---|
| **캡슐화** | 이 패턴의 존재 이유. 상태를 **밖으로 내보내되 들여다보지 못하게** 한다 |
| **SRP** | 상태를 가진 쪽(`Navigator`)과 보관하는 쪽(`CheckpointStack`)을 나눴다 |
| **최소 지식** | Caretaker 가 스냅샷에 대해 아는 것은 `label()` 하나뿐이다 |

**C++ 문법으로 지킨 것**

- **중첩 클래스 + `friend class Navigator`** - 자바 내부 클래스 접근 규칙의 C++ 판
- `Snapshot` 의 생성자도 `private` - Originator 말고는 **만들 수조차 없다**
- 값 복사로 스냅샷을 벡터에 보관 (포인터가 아니라서 수명 문제가 없다)

**거스른 것 / 대가**

- **`friend` 는 캡슐화에 낸 구멍이다.** 딱 한 클래스에만 여는 것이 전제이고,
  friend 가 둘 이상이 되는 순간 이 설계는 무너진다
- 스냅샷이 커지면 복사 비용이 그대로 든다 (코스트맵·파티클 전체라면 문제가 된다)

## 9. 실행

### 이 폴더만 단독으로

```sh
cd robot/10_Memento
make          # build/10_Memento 에 실행 파일 생성
make run      # 빌드하고 바로 실행
make clean    # build/ 삭제
```

### 저장소 루트에서 (다른 패턴과 함께)

```sh
make robot                    # 로봇 예제 22개 전부 빌드 -> build/bin/robot_*
make run-robot-10_Memento    # 이 예제만 빌드하고 실행
make run-robot-all            # 22개를 순서대로 실행
```

두 경로의 빌드 옵션은 같다 - `-std=c++20 -Wall -Wextra -Wpedantic -O1`, **경고 0개**를 유지한다.
산출물 위치만 다르다 - 단독은 `10_Memento/build/`, 루트는 `build/bin/`.

## 10. 확인 질문

> `CheckpointStack.cpp` 에서 스냅샷의 배터리 값을 로그로 찍으려면 어떻게 해야 하는가?

**못 한다.** `Navigator` 에 게터를 추가하거나 `Snapshot` 에 `public` 메소드를 열어야 하고,
그 순간 "보관만 한다" 는 보장이 약해진다. 그 선택을 의식적으로 하게 만드는 것이 이 패턴이다.
