#include "adapter/SonarToScanAdapter.h"

#include <stdexcept>
#include <utility>

SonarToScanAdapter::SonarToScanAdapter(std::unique_ptr<SerialSonarArray> board)
	: board_(std::move(board))
{
	if (!board_) {
		throw std::invalid_argument("어댑터에 감쌀 보드가 필요합니다");
	}
}

LaserScan SonarToScanAdapter::scan() const
{
	LaserScan out;
	out.frameId = "sonar_link";
	const int n = board_->sensorCount();
	for (int i = 0; i < n; ++i) {
		const int cm = board_->pingCentimeters(i);
		// 번역이 일어나는 딱 두 줄
		out.ranges.push_back(cm < 0 ? 0.0 : cm / 100.0);
	}
	return out;
}

std::string SonarToScanAdapter::name() const
{
	return "SonarArray (어댑터 경유)";
}
