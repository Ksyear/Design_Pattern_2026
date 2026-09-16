// [연습] 프록시 패턴 - 캐싱 프록시와 스마트 레퍼런스
//
// 1단계: 캐싱 프록시
// TODO 1. interface IWeatherService { std::string fetch(const std::string& city); }
//         RealWeatherService::fetch는 "네트워크 왕복 500ms" 를 흉내내고 실제 값을 만든다
// TODO 2. CachingProxy를 만들어 같은 도시를 다시 물으면 캐시에서 즉시 답하게 할 것
// TODO 3. TTL(예: 10초)을 넣어 오래된 캐시는 무효화할 것
// TODO 4. 캐시 적중률을 세어 출력할 것
//
// 2단계: 스마트 레퍼런스
// TODO 5. 무거운 객체를 참조하는 클라이언트 수를 세는 프록시를 만들 것
//         - 마지막 클라이언트가 떠나면 진짜 객체를 해제한다
//         - std::shared_ptr이 이미 이 일을 한다는 점을 확인하고,
//           표준 라이브러리에 들어 있는 패턴을 찾아볼 것
//
// 3단계: 네 사촌 패턴 구분 확정
// TODO 6. 같은 Image 인터페이스에 대해 네 가지를 모두 만들고 나란히 비교할 것
//         - ImageAdapter    : 인터페이스가 다른 레거시 이미지 클래스를 Image로 번역
//         - ImageProxy      : 인터페이스 동일, 로딩 시점 통제
//         - WatermarkDecorator : 인터페이스 동일, display()에 워터마크 기능 추가
//         - GalleryFacade   : 여러 이미지/캐시/로더를 묶은 단순 인터페이스
//         네 개를 한 파일에 두고 보면 차이가 확실해진다
//
// C++ 메모
//   - std::shared_ptr / std::unique_ptr : 스마트 레퍼런스 프록시
//   - std::vector<bool>::reference      : 비트 접근을 대리하는 프록시 객체
//   - 표현식 템플릿(Eigen 등)           : 지연 평가 프록시

#include <iostream>

int main() {
	std::cout << "TODO: 캐싱 프록시와 스마트 레퍼런스를 만들어 보세요\n";
	return 0;
}
