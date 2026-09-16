// [연습] 빌더 패턴 - 텔레스코핑 생성자 없애기
//
// 아래 HttpRequest는 선택 매개변수가 많아 생성자가 끝없이 늘어난다 (telescoping constructor).
//
//   HttpRequest(url)
//   HttpRequest(url, method)
//   HttpRequest(url, method, headers)
//   HttpRequest(url, method, headers, body)
//   HttpRequest(url, method, headers, body, timeoutMs)   <- 여기서 이미 무너진다
//
// TODO 1. HttpRequest는 빌더만 생성할 수 있게 할 것 (생성자를 private로 두고 friend 선언)
// TODO 2. HttpRequestBuilder를 만들고 method/header/body/timeout을 각각의 단계 메소드로 분리
// TODO 3. 각 단계가 *this를 반환하게 해서 메소드 체이닝이 되게 할 것
//         req = HttpRequestBuilder("https://x").method("POST").header("A","B").build();
// TODO 4. build()에서 필수 값(url)이 비었으면 예외를 던지도록 검증 로직을 넣을 것
//
// 생각해 볼 것
//   - C++에는 이름 있는 인자가 없어서 빌더가 특히 유용하다
//   - 반대로 designated initializer(C++20)나 옵션 struct로 대체할 수 있는 경우도 많다
//     -> 단계 수가 적고 순서 제약이 없다면 빌더는 과잉 설계다

#include <iostream>

int main() {
	std::cout << "TODO: HttpRequestBuilder를 만들어 보세요\n";
	return 0;
}
