#include "menu/CafeMenu.h"

CafeMenu::CafeMenu() {
	items_ = {
		{"베지 버거와 에어 프라이", "통밀빵, 상추, 토마토, 감자 튀김", true, 3.99},
		{"오늘의 스프", "샐러드와 함께 나오는 오늘의 스프", false, 3.69},
		{"부리토", "통 핀토콩과 살사, 구아카몰이 들어간 부리토", true, 4.29},
	};
}

CafeMenu::const_iterator CafeMenu::begin() const {
	return items_.begin();
}

CafeMenu::const_iterator CafeMenu::end() const {
	return items_.end();
}
