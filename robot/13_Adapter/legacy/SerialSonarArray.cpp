#include "legacy/SerialSonarArray.h"

#include <array>
#include <iostream>

namespace {
// 보드가 돌려준다고 치는 값들 (cm, -1 은 측정 실패)
constexpr std::array<int, 4> kReadings{187, 243, -1, 96};
}

void SerialSonarArray::openPort(const char* device)
{
	open_ = true;
	std::cout << "    [legacy] " << device << " 9600bps 로 포트 열기\n";
}

int SerialSonarArray::sensorCount() const
{
	return static_cast<int>(kReadings.size());
}

int SerialSonarArray::pingCentimeters(int index) const
{
	if (!open_ || index < 0 || index >= sensorCount()) {
		return -1;
	}
	return kReadings[static_cast<std::size_t>(index)];
}
