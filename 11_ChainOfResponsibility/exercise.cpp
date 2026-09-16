// [연습] 책임 연쇄 패턴 - HTTP 미들웨어 파이프라인
//
// refactoring.guru가 드는 대표 사례는 '인증 -> 검증 -> 속도 제한 -> 캐시' 순서 검사다.
// 이건 웹 프레임워크의 미들웨어와 정확히 같은 구조다.
//
// TODO 1. struct Request { std::string user, path; bool authenticated; } 를 정의
// TODO 2. Middleware 기반 클래스에 bool check(Request&) 를 두고
//         "true면 다음으로 진행, false면 사슬을 끊는다" 의미로 쓸 것
//         (main.cpp와 반대 방향의 흐름 - CoR에는 두 변형이 다 있다)
// TODO 3. 구상 미들웨어 4개
//         - AuthMiddleware   : authenticated가 false면 거부
//         - ThrottleMiddleware: 같은 user가 3회 넘게 오면 거부
//         - CacheMiddleware  : 캐시에 있으면 즉시 응답하고 사슬을 끊는다
//         - RouteMiddleware  : 마지막에서 실제 처리
// TODO 4. 사슬의 순서를 바꿔 보고 동작이 어떻게 달라지는지 확인할 것
//         -> "핸들러가 특정 순서로 실행되어야 할 때" 라는 적용 조건을 체감
//
// 생각해 볼 것
//   - 데코레이터와 구조가 거의 같은데 무엇이 다른가?
//     데코레이터는 반드시 다음으로 흘려보내고, CoR은 도중에 끊을 수 있다

#include <iostream>

int main() {
	std::cout << "TODO: HTTP 미들웨어 사슬을 만들어 보세요\n";
	return 0;
}
