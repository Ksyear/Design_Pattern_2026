// [연습] 옵저버 패턴 - 헤드 퍼스트 2장 HeatIndexDisplay + 풀(pull) 방식
//
// TODO 1. HeatIndexDisplay(체감 온도) 옵저버를 추가할 것
//         heatIndex 공식은 책 2장 그대로 써도 되고, 간단히 (t + h) / 2로 대체해도 된다
// TODO 2. update(temp, humidity, pressure) 푸시 방식을 update(Subject&) 풀 방식으로 바꿀 것
//         - 주제에 getTemperature() / getHumidity() / getPressure() 게터를 추가
//         - 옵저버가 필요한 값만 직접 당겨 가게 한다
// TODO 3. 옵저버를 하나 더 추가해도 WeatherData 코드가 한 줄도 안 바뀌는지 확인할 것 (OCP)

#include <iostream>

int main() {
	std::cout << "TODO: 체감 온도 디스플레이를 추가하고 풀 방식으로 바꿔 보세요\n";
	return 0;
}
