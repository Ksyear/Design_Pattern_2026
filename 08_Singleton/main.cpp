// 싱글턴 패턴 (Singleton) - 헤드 퍼스트 5장 초콜릿 보일러
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   boiler/  유일 인스턴스 - ChocolateBoiler.*(Meyers Singleton)
//
// 싱글턴은 참여자가 하나뿐인 패턴이라 폴더도 하나다.
// 대신 "생성자가 헤더에서 안 보인다(private)"는 점이 파일을 나누니 더 또렷해진다.
#include <iostream>
#include <thread>
#include <vector>

#include "boiler/ChocolateBoiler.h"

int main() {
	std::cout << "--- 한 스레드에서 정상 흐름 ---\n";
	auto& boiler = ChocolateBoiler::getInstance();
	boiler.fill();
	boiler.boil();
	boiler.drain();

	std::cout << "\n--- 다른 곳에서 다시 가져와도 같은 객체 ---\n";
	auto& again = ChocolateBoiler::getInstance();
	std::cout << "  주소 비교: " << (&boiler == &again ? "동일 인스턴스" : "다른 인스턴스!") << '\n';

	std::cout << "\n--- 여러 스레드가 동시에 접근 ---\n";
	std::vector<std::thread> workers;
	for (int i = 0; i < 4; ++i) {
		workers.emplace_back([] {
			auto& b = ChocolateBoiler::getInstance();
			b.fill();   // 락 덕분에 '이미 차 있습니다'가 정확히 3번 나온다
		});
	}
	for (auto& t : workers) t.join();

	return 0;
}
