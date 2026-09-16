// 프록시 패턴 (Proxy) - 헤드 퍼스트 11장 앨범 커버 뷰어(가상 프록시) + 보호 프록시
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   image/   RealSubject 1 - Image.h(인터페이스) + RealImage.*(비싼 객체)
//   person/  RealSubject 2 - Person.h(인터페이스) + PersonImpl.*(권한을 모른다)
//   proxy/   대리인들      - ImageProxy(가상) / LoggingImageProxy(로깅) /
//                            OwnerProxy, NonOwnerProxy(보호)
//
// 프록시를 전부 한 폴더에 모아 두면 "종류는 달라도 하는 일은 같다 = 접근 통제"가 보인다.
//
// 프록시의 종류 (refactoring.guru 기준)
//   가상(virtual)  : 비싼 객체 생성을 미룬다
//   보호(protection): 권한에 따라 접근을 막는다
//   원격(remote)   : 네트워크 너머 객체를 대리한다     (자바 RMI, gRPC 스텁)
//   로깅/캐싱/스마트 레퍼런스 : 호출 기록, 결과 캐시, 참조 관리
//
// 데코레이터와 구분
//   - 데코레이터: 기능을 '더한다'. 생성은 클라이언트가 한다
//   - 프록시   : 접근을 '통제한다'. 생명주기를 프록시가 직접 쥔다
#include <exception>
#include <iostream>
#include <memory>

#include "person/PersonImpl.h"
#include "proxy/ImageProxy.h"
#include "proxy/LoggingImageProxy.h"
#include "proxy/NonOwnerProxy.h"
#include "proxy/OwnerProxy.h"

int main() {
	std::cout << "===== 가상 프록시 =====\n";
	std::cout << "프록시 생성 (이 시점에 디스크 접근 없음)\n";
	ImageProxy cover("album_cover.jpg");
	std::cout << "아직 아무 로딩도 안 일어났다\n\n";

	std::cout << "첫 display() 호출:\n";
	cover.display();
	std::cout << "\n두 번째 display() 호출 (이미 로딩됨):\n";
	cover.display();

	std::cout << "\n===== 보호 프록시 =====\n";
	auto joe = std::make_shared<PersonImpl>("조");
	OwnerProxy owner(joe);
	NonOwnerProxy other(joe);

	owner.setInterests("자전거, 수영");
	std::cout << "  본인이 관심사 수정: 성공\n";
	try {
		owner.setHotOrNotRating(10);
	} catch (const std::exception& e) {
		std::cout << "  본인이 자기 점수 주기: " << e.what() << '\n';
	}

	other.setHotOrNotRating(8);
	other.setHotOrNotRating(6);
	std::cout << "  타인이 점수 주기: 성공 (평균 " << other.getHotOrNotRating() << ")\n";
	try {
		other.setInterests("해킹");
	} catch (const std::exception& e) {
		std::cout << "  타인이 관심사 수정: " << e.what() << '\n';
	}

	std::cout << "\n===== 프록시를 겹쳐 쓰기 (로깅 + 가상) =====\n";
	LoggingImageProxy logged(std::make_unique<ImageProxy>("second.jpg"));
	logged.display();
	logged.display();

	return 0;
}
