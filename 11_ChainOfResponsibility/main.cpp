// 책임 연쇄 패턴 (Chain of Responsibility) - 헤드 퍼스트 14장 주식회사 왕뽑기 메일 분류
//
// 이 파일은 "사슬 조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   mail/     요청     - Email.h
//   handler/  처리기   - Handler.*(사슬 뼈대) + 구상 핸들러 4개
//
// 핸들러끼리는 서로를 전혀 모른다. 순서를 정하는 코드는 이 파일에만 있다.
#include <iostream>
#include <memory>

#include "handler/ComplaintHandler.h"
#include "handler/FanHandler.h"
#include "handler/NewLocHandler.h"
#include "handler/SpamHandler.h"
#include "mail/Email.h"

int main() {
	// 사슬 조립 - 순서가 곧 우선순위다 (스팸을 먼저 걸러야 뒤가 편하다)
	auto chain = std::make_unique<SpamHandler>();
	Handler* p = chain.get();
	p = p->setNext(std::make_unique<FanHandler>());
	p = p->setNext(std::make_unique<ComplaintHandler>());
	p->setNext(std::make_unique<NewLocHandler>());

	const Email mails[] = {
		{"user1@x.com", "뽑기 기계 최고!", "기계 정말 최고예요 감사합니다"},
		{"parent@x.com", "기계 좀 옮겨 주세요", "아이가 뽑기에 중독됐습니다 항의합니다"},
		{"shop@x.com", "설치 문의", "저희 매장에 설치하고 싶습니다"},
		{"spam@x.com", "[광고] 초특급 할인", "지금 바로 클릭"},
		{"who@x.com", "안녕하세요", "그냥 인사드립니다"},
	};

	for (const auto& m : mails) {
		std::cout << "수신: " << m.subject << '\n';
		chain->handle(m);
	}

	return 0;
}
