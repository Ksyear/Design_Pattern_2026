#include <iomanip>
#include <iostream>
#include <memory>

#include "filter/DropOutlier.h"
#include "filter/MedianFilter.h"
#include "filter/RangeClamp.h"
#include "scan/RawLidar.h"

namespace {

void report(const ScanSource& source)
{
	std::cout << "  " << source.pipeline() << '\n';
	std::cout << "    지연 " << std::fixed << std::setprecision(1) << source.latencyMs() << " ms\n";
	std::cout << "    ranges =";
	for (double r : source.read().ranges) {
		std::cout << ' ' << std::setw(6) << std::setprecision(2) << r;
	}
	std::cout << "\n\n";
}

}

int main()
{
	std::cout << "===== 1. 원본 스캔 =====\n";
	report(RawLidar{});

	std::cout << "===== 2. 필터를 하나씩 씌워 간다 =====\n";
	auto pipeline = std::make_unique<RangeClamp>(
		std::make_unique<MedianFilter>(
			std::make_unique<DropOutlier>(std::make_unique<RawLidar>())),
		0.10, 10.0);
	report(*pipeline);

	std::cout << "===== 3. 순서를 바꾸면 결과가 달라진다 =====\n";
	auto wrongOrder = std::make_unique<RangeClamp>(
		std::make_unique<DropOutlier>(
			std::make_unique<MedianFilter>(std::make_unique<RawLidar>())),
		0.10, 10.0);
	report(*wrongOrder);

	std::cout << "===== 4. 같은 필터를 두 번 씌우기 =====\n";
	report(MedianFilter{std::make_unique<MedianFilter>(
		std::make_unique<DropOutlier>(std::make_unique<RawLidar>()))});

	return 0;
}
