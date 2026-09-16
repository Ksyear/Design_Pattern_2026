// 옵저버 패턴 (Observer) - 헤드 퍼스트 2장 기상 스테이션
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   observer/  통보받는 쪽의 계약 - Observer.h, DisplayElement.h
//   subject/   통보하는 쪽       - Subject.h(인터페이스) + WeatherData.*(구상 주제)
//   display/   화면 출력 기능    - 구상 옵저버 3개
//
// subject/ 는 observer/ 의 인터페이스만 알고, display/ 를 전혀 모른다.
// 그래서 디스플레이를 몇 개 더 만들어도 subject/ 는 한 줄도 바뀌지 않는다.
#include <iostream>
#include <memory>

#include "display/CurrentConditionsDisplay.h"
#include "display/ForecastDisplay.h"
#include "display/StatisticsDisplay.h"
#include "subject/WeatherData.h"

int main() {
	WeatherData weatherData;

	auto current = std::make_shared<CurrentConditionsDisplay>();
	auto stats = std::make_shared<StatisticsDisplay>();
	auto forecast = std::make_shared<ForecastDisplay>();

	weatherData.registerObserver(current);
	weatherData.registerObserver(stats);
	weatherData.registerObserver(forecast);

	std::cout << "--- 1차 측정 ---\n";
	weatherData.setMeasurements(80, 65, 30.4f);
	std::cout << "--- 2차 측정 ---\n";
	weatherData.setMeasurements(82, 70, 29.2f);

	// 옵저버는 언제든 빠질 수 있다 - 주제 코드는 전혀 바뀌지 않는다
	weatherData.removeObserver(forecast);
	std::cout << "--- 3차 측정 (예보 디스플레이 해지 후) ---\n";
	weatherData.setMeasurements(78, 90, 29.2f);

	return 0;
}
