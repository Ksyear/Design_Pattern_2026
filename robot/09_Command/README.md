# 09. Command - 텔레옵 명령 + 되돌리기 + 매크로

> 명령을 **객체로** 만들면 보낼 수 있고, 쌓을 수 있고, 취소할 수 있고, 로그로 남길 수 있다.
> 함수 호출로는 하나도 못 하는 일들이다.
>
> 책 예제 : [`../../09_Command`](../../09_Command) (IoT 리모컨)

## 1. 어떤 문제를 푸는가

텔레옵 콘솔의 버튼 하나를 누르면 로봇이 움직인다. 순진하게 짜면 이렇게 된다.

```cpp
void onButton0() { base.driveForward(1.0); }   // 콘솔이 장치를 직접 안다
```

여기서 막히는 것들.

- **버튼 재배치** : 슬롯에 다른 동작을 꽂으려면 콘솔 코드를 고쳐야 한다
- **되돌리기** : 무슨 일을 했는지 기록이 없다
- **매크로** : 여러 동작을 묶어 버튼 하나에 넣을 방법이 없다
- **원격 전송** : 함수 호출은 네트워크로 보낼 수 없다

그래서 **"무엇을 할지" 를 객체 하나에 담았다.** 받는 쪽 + 할 일 + 필요한 값을 함께.

## 2. 폴더가 곧 패턴 역할

| 폴더 / 파일 | 패턴 역할 | 하는 일 |
|---|---|---|
| [`console/TeleopConsole.*`](console/TeleopConsole.h) | **Invoker** | 슬롯 4개와 되돌리기 기록. 무슨 명령인지 모른다 |
| [`command/Command.h`](command/Command.h) | **Command 인터페이스** | `execute()` / `undo()` / `name()` |
| [`command/MoveCommand.*`](command/MoveCommand.h) | Concrete Command | 전진 (거리를 담는다) |
| [`command/TurnCommand.*`](command/TurnCommand.h) | Concrete Command | 회전 (각도를 담는다) |
| [`command/GripCommand.*`](command/GripCommand.h) | Concrete Command | 파지. **실행 직전 상태를 기억한다** |
| [`command/MacroCommand.*`](command/MacroCommand.h) | Concrete Command (복합) | 명령 여러 개를 하나처럼 |
| [`command/NoCommand.*`](command/NoCommand.h) | Null Object | 빈 슬롯. `if` 를 없앤다 |
| [`device/MobileBase.*`](device/MobileBase.h) | **Receiver** | 실제로 움직인다 |
| [`device/Gripper.*`](device/Gripper.h) | **Receiver** | 실제로 쥐고 논다 |

## 3. 적용 방식

### (1) Invoker 의 무지함

```cpp
// console/TeleopConsole.cpp
void TeleopConsole::press(std::size_t slot)
{
	slots_[slot]->execute();
	history_.push_back(slots_[slot].get());
}
```

이 파일 전체에 `MobileBase` / `Gripper` 라는 이름이 **없다.**
장치가 몇 개로 늘어나도 콘솔은 그대로고, 새 명령 클래스 하나만 생긴다.
조이스틱 노드든 웹 관제 화면이든 자동 스크립트든 **전부 이 자리에 온다.**

### (2) 소유권이 두 갈래다

```cpp
std::array<std::unique_ptr<Command>, kSlotCount> slots_;   // 소유
std::vector<Command*> history_;                            // 비소유
```

명령을 소유하는 것은 **슬롯**이고, 기록은 그것을 **가리키기만** 한다.
이 저장소의 규약 - 원시 포인터 = 비소유 참조 - 가 여기서도 그대로다.

같은 규약이 명령 → 장치 방향에도 적용된다.

```cpp
// command/MoveCommand.h
MobileBase* base_;   // 비소유 참조 - 명령이 장치를 소유하지는 않는다
```

### (3) 널 객체로 `if` 를 지웠다

```cpp
// 생성자에서 전부 NoCommand 로 채운다
for (std::unique_ptr<Command>& slot : slots_) {
	slot = std::make_unique<NoCommand>();
}
```

덕분에 `press()` 안에 "이 슬롯이 비었는가" 검사가 없다.
`nullptr` 검사를 타입으로 없앤 것이다.

## 4. 실행하면 보이는 것 - 되돌리기가 공짜가 아니다

```
===== 3. 되돌리기 - 마지막 동작을 반대로 =====
    되돌리기 (전진)
      [base] -1.00m 주행         ← "없던 일로" 가 아니라 반대로 움직인다
    현재 위치 (1.00, 0.00)  방위 90.0도
```

```cpp
// command/MoveCommand.cpp
void MoveCommand::undo()
{
	// 로봇에서 undo 는 "없던 일로" 가 아니라 "반대로 움직이기" 다.
	// 완벽하게 제자리로 돌아오지 않는다는 점(슬립, 오차)도 현실의 일부다.
	base_->driveForward(-meters_);
}
```

**텍스트 에디터의 Ctrl+Z 와 근본적으로 다르다.**
문서는 되돌리면 정말 원래대로 돌아오지만, 로봇은 바퀴가 미끄러지고 오차가 쌓인다.
이 예제는 시뮬레이션이라 좌표가 정확히 복구되지만, 실물에서는 그렇지 않다.

## 5. 6번 장면 - 매크로는 왜 역순이어야 하는가

```
===== 5. 매크로 - 집품 시퀀스를 버튼 하나에 =====
      [매크로 집품 시작]
      [base] +0.50m 주행
      [gripper] 닫힘 (파지)
      [base] +180.0도 회전

===== 6. 매크로 되돌리기 - 역순이어야 하는 이유 =====
      [매크로 집품 되돌리기 - 역순]
      [base] -180.0도 회전
      [gripper] 열림
      [base] -0.50m 주행
```

```cpp
// command/MacroCommand.cpp
for (auto it = steps_.rbegin(); it != steps_.rend(); ++it) {   // 역방향 반복자
	(*it)->undo();
}
```

**앞에서부터 되돌리면 물건을 쥔 채로 후진하게 된다.**
그러면 선반의 물건이 끌려 나오거나 그리퍼가 부러진다.

> 이 저장소의 로봇 예제가 공유하는 주제 중 하나 - **순서가 곧 안전이다.**
> [`../03_Decorator`](../03_Decorator) 의 필터 순서, [`../14_Facade`](../14_Facade) 의 시동 순서도 같은 이야기다.

`MacroCommand` 자체가 `Command` 라서 콘솔은 그것이 하나인지 여럿인지 모른다
([`../18_Composite`](../18_Composite) 와 같은 발상).

## 6. 실제 ROS 2 대응

| 이 예제 | 실제 ROS 2 |
|---|---|
| `Command` 객체 | **액션(action)의 goal** - 직렬화해서 네트워크로 보낸다 |
| `execute()` | goal 을 액션 서버에 전송 |
| 취소 | 액션의 `cancel_goal` (여기서는 `undo()` 로 대신했다) |
| `MacroCommand` | 비헤이비어 트리의 `Sequence` 노드, MoveIt 의 다구간 궤적 |
| `history_` | 액션 goal 로그 / rosbag |
| `TeleopConsole` | `teleop_twist_joy`, 웹 관제 대시보드 |

**"명령을 객체로 만든다" 는 것이 분산 로봇 시스템의 전제 조건**이다.
함수 호출은 프로세스 경계를 못 넘지만, 객체는 직렬화해서 보낼 수 있다.

## 7. 10_Memento 로 이어지는 지점

```cpp
// command/GripCommand.h
bool previousClosed_ = false;   // 실행 직전 상태를 적어 둔다
```

파지를 되돌리려면 "원래 열려 있었는지 닫혀 있었는지" 를 알아야 한다.
**명령이 상태를 기억하기 시작하는 순간**이고, 이걸 제대로 다루는 것이
[`../10_Memento`](../10_Memento) 다.

## 8. 이 예제가 하지 않는 것

- 명령을 직렬화하지 않는다. 같은 프로세스 안의 객체일 뿐이다
- 비동기 실행이 없다. `execute()` 는 즉시 끝난다 (실제 액션은 오래 걸리고 피드백을 보낸다)
- `history_` 를 파일로 저장하지 않는다.
  **저장하면 그대로 재생 가능한 작업 스크립트가 된다** - 커맨드 패턴의 큰 이득 중 하나인데 생략했다
- 슬립·오차가 없는 완벽한 `undo` 다. 실물과 다른 지점

## 9. 객체지향 관점 - 어떤 원칙을 어떻게 지켰나

| 원칙 | 이 예제에서 어떻게 했나 |
|---|---|
| **캡슐화** | 요청(수신자 + 동작 + 인자)을 객체 하나에 담았다 |
| **느슨한 결합** | Invoker 와 Receiver 가 서로를 모른다. 사이에 `Command` 만 있다 |
| **OCP** | 명령을 추가해도 `console/` 은 0줄 바뀐다 |
| **널 객체** | 빈 슬롯을 `NoCommand` 로 채워 `if (slot)` 분기를 타입으로 없앴다 |

**C++ 문법으로 지킨 것**

- **한 클래스 안에서 소유와 비소유를 구분해 쓴다** :
  `array<unique_ptr<Command>> slots_`(소유) vs `vector<Command*> history_`(비소유)
- 명령 → 장치도 원시 포인터. 생성자에서 `nullptr` 거부
- 매크로 되돌리기에 역방향 반복자 `rbegin()` / `rend()`

**거스른 것 / 대가**

- 명령 하나에 클래스 하나. 작은 동작에도 파일이 둘 생긴다
- **`undo()` 를 모든 명령이 의미 있게 정의할 수 있다는 가정**이 깔려 있다.
  로봇에서는 거짓에 가깝다 - 되돌리기는 "반대로 움직이기" 라 오차가 남는다

## 10. 실행

### 이 폴더만 단독으로

```sh
cd robot/09_Command
make          # build/09_Command 에 실행 파일 생성
make run      # 빌드하고 바로 실행
make clean    # build/ 삭제
```

### 저장소 루트에서 (다른 패턴과 함께)

```sh
make robot                    # 로봇 예제 22개 전부 빌드 -> build/bin/robot_*
make run-robot-09_Command    # 이 예제만 빌드하고 실행
make run-robot-all            # 22개를 순서대로 실행
```

두 경로의 빌드 옵션은 같다 - `-std=c++20 -Wall -Wextra -Wpedantic -O1`, **경고 0개**를 유지한다.
산출물 위치만 다르다 - 단독은 `09_Command/build/`, 루트는 `build/bin/`.

## 11. 확인 질문

> `TeleopConsole.cpp` 에 장치 이름이 나오는가? `history_` 를 파일로 저장하면 무엇이 되는가?

이름은 안 나온다. 그리고 기록을 저장하면 **재생 가능한 작업 스크립트**가 된다 -
명령이 객체이기 때문에 가능한 일이다.
