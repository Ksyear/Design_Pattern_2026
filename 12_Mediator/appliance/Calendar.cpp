#include "appliance/Calendar.h"

Calendar::Calendar() : Appliance("달력") {}

void Calendar::doAction(const std::string&) {}

bool Calendar::isWeekend() const {
	return weekend_;
}

bool Calendar::isTrashDay() const {
	return trashDay_;
}

void Calendar::setDay(bool weekend, bool trashDay) {
	weekend_ = weekend;
	trashDay_ = trashDay;
}
