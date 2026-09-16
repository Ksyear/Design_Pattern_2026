// [연습] 어댑터 패턴 - 레거시 로그 API를 새 인터페이스에 맞추기
//
// 시나리오
//   새 코드는 ILogger { void log(Level, const std::string&); } 를 기대한다.
//   그런데 사내 레거시 라이브러리는 이렇게 생겼고, 수정할 수 없다.
//
//     class LegacyLog {
//     public:
//       void writeInfo(const char* msg);
//       void writeWarn(const char* msg);
//       void writeError(const char* msg, int code);   // code가 필수다
//     };
//
// TODO 1. ILogger 인터페이스와 Level enum(Info/Warn/Error)을 정의
// TODO 2. LegacyLogAdapter : public ILogger 를 만들어 LegacyLog를 감쌀 것
//         - Level에 따라 writeInfo/writeWarn/writeError로 분기
//         - Error일 때 없는 code는 무엇으로 채울지 결정하고 그 판단을 주석으로 남길 것
//           (어댑터가 '정보를 지어내야 하는' 지점 = 어댑터 패턴의 실제 난점)
// TODO 3. 반대 방향 어댑터도 만들 것 (새 ILogger를 레거시 코드에 꽂기)
//
// 어댑터 / 퍼사드 / 프록시 / 데코레이터 구분 연습
//   - 인터페이스를 '바꾸면'          -> 어댑터
//   - 인터페이스를 '단순하게 새로'   -> 퍼사드
//   - 인터페이스를 '그대로' 두고 통제 -> 프록시
//   - 인터페이스를 '그대로' 두고 기능 추가 -> 데코레이터

#include <iostream>

int main() {
	std::cout << "TODO: 레거시 로그 API 어댑터를 만들어 보세요\n";
	return 0;
}
