#ifndef FILTER_SPEEDFILTER_H
#define FILTER_SPEEDFILTER_H

#include <string>

#include "msg/Types.h"

// 두 번째 전략 축 - 계산된 속도를 내보내기 전에 걸러 내는 정책.
//
// 책의 오리가 fly 와 quack 두 축을 따로 들고 있던 것과 같은 자리다.
// 실제 Nav2 에도 있다 : nav2_costmap_2d 의 Speed Filter 플러그인이
// 지도에 칠해 둔 구역에 따라 속도 상한을 내린다.
//
// 축을 둘로 나눈 이유는 조합 폭발을 막기 위해서다.
// 컨트롤러 3종 x 속도 정책 3종 을 상속으로 만들면 클래스가 9개 필요하지만,
// 구성으로 들고 있으면 3 + 3 = 6개로 끝나고 조합은 실행 중에 만들어진다.
class SpeedFilter {
public:
	virtual ~SpeedFilter() = default;

	virtual Twist apply(const Twist& raw) const = 0;
	virtual std::string name() const = 0;
};

#endif
