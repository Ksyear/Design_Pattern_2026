#ifndef BEVERAGE_CAFFEINE_BEVERAGE_H
#define BEVERAGE_CAFFEINE_BEVERAGE_H

// 알고리즘의 골격을 쥐고 있는 상위 클래스
//
// 핵심: 알고리즘의 '골격'을 상위 클래스에 못 박고, 일부 단계만 서브클래스가 채운다.
//       - 추상 단계(abstract step) : 반드시 구현해야 함
//       - 구상 단계(concrete step) : 공통 구현을 물려받음
//       - 후크(hook)              : 기본 구현이 비어 있고, 필요할 때만 재정의
//
// 할리우드 원칙: "먼저 연락하지 마세요. 저희가 연락 드리겠습니다."
//   저수준(서브클래스)이 고수준(추상 클래스)을 부르는 게 아니라, 반대로 불린다.
class CaffeineBeverage {
public:
	virtual ~CaffeineBeverage() = default;

	// 템플릿 메소드 : 알고리즘의 순서를 고정한다.
	// 서브클래스가 못 바꾸게 virtual 을 붙이지 않는 것이 핵심 (자바의 final 과 같은 의도)
	void prepareRecipe();

protected:
	// 공통 단계 : 모두가 똑같이 한다
	void boilWater() const;
	void pourInCup() const;

	// 추상 단계 : 반드시 서브클래스가 구현
	virtual void brew() const = 0;
	virtual void addCondiments() const = 0;

	// 후크 : 기본값이 있으므로 재정의는 선택
	virtual bool customerWantsCondiments() const;
};

#endif
