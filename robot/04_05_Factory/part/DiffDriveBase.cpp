#include "part/DiffDriveBase.h"

#include <iostream>

std::string DiffDriveBase::spec() const
{
	return "차동 구동 (좌우 바퀴 + 캐스터)";
}

bool DiffDriveBase::canRotateInPlace() const
{
	return true;
}

void DiffDriveBase::onConfigure()
{
	std::cout << "    구동계 설정 : /dev/ttyUSB0 열기, 115200bps, 휠 반경 0.033m 반영\n";
}
