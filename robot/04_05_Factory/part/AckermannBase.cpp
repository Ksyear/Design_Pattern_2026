#include "part/AckermannBase.h"

#include <iostream>

std::string AckermannBase::spec() const
{
	return "애커만 조향 (자동차형, 최소 회전 반경 2.4m)";
}

bool AckermannBase::canRotateInPlace() const
{
	return false;
}

void AckermannBase::onConfigure()
{
	std::cout << "    구동계 설정 : CAN 버스(can0) 열기, 조향 모터 원점 맞추기\n";
}
