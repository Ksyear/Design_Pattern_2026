#ifndef BOILER_CHOCOLATE_BOILER_H
#define BOILER_CHOCOLATE_BOILER_H

#include <mutex>

// 싱글턴
//
// 핵심: 인스턴스를 하나만 만들고 전역 접근점을 제공한다.
//       전역 변수와 다른 점은 '늦은 생성(lazy)'과 '접근 통제'가 가능하다는 것.
//
// C++에서 가장 중요한 사실
//   함수 지역 static 은 C++11부터 초기화가 스레드 안전하다고 표준이 보장한다 ([stmt.dcl]/4).
//   즉 자바에서 고생하는 DCL(Double-Checked Locking)이 C++에서는 필요 없다.
//   이것이 Meyers Singleton.
class ChocolateBoiler {
public:
	// 유일한 접근점. 첫 호출 때 딱 한 번 생성되고, 동시 호출도 안전하다
	static ChocolateBoiler& getInstance();

	// 복사/이동을 막지 않으면 "유일하다"는 약속이 깨진다
	ChocolateBoiler(const ChocolateBoiler&) = delete;
	ChocolateBoiler& operator=(const ChocolateBoiler&) = delete;
	ChocolateBoiler(ChocolateBoiler&&) = delete;
	ChocolateBoiler& operator=(ChocolateBoiler&&) = delete;

	void fill();
	void boil();
	void drain();

	bool isEmpty() const;
	bool isBoiled() const;

private:
	// 생성자를 숨겨서 밖에서 new/스택 생성을 못 하게 만든다
	ChocolateBoiler();

	bool empty_;
	bool boiled_;
	mutable std::mutex mutex_;
};

#endif
