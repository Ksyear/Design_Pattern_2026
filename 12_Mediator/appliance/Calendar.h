#ifndef APPLIANCE_CALENDAR_H
#define APPLIANCE_CALENDAR_H

#include <string>

#include "appliance/Appliance.h"

// 시키는 일은 없고 '물어보는 대상'인 가전. 중재자의 규칙이 이 값을 읽는다.
class Calendar : public Appliance {
public:
	Calendar();
	void doAction(const std::string&) override;

	bool isWeekend() const;
	bool isTrashDay() const;
	void setDay(bool weekend, bool trashDay);

private:
	bool weekend_ = false;
	bool trashDay_ = false;
};

#endif
