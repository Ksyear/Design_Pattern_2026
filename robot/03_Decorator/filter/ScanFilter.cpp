#include "filter/ScanFilter.h"

#include <stdexcept>
#include <utility>

ScanFilter::ScanFilter(std::unique_ptr<ScanSource> source)
	: source_(std::move(source))
{
	if (!source_) {
		throw std::invalid_argument("감쌀 ScanSource 는 nullptr 일 수 없습니다");
	}
}
