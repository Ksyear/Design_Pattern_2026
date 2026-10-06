#include "filter/MedianFilter.h"

#include <algorithm>
#include <array>

LaserScan MedianFilter::read() const
{
	const LaserScan in = source_->read();
	LaserScan out = in;
	for (std::size_t i = 1; i + 1 < in.ranges.size(); ++i) {
		std::array<double, 3> window{in.ranges[i - 1], in.ranges[i], in.ranges[i + 1]};
		std::sort(window.begin(), window.end());
		out.ranges[i] = window[1];
	}
	return out;
}

double MedianFilter::latencyMs() const
{
	return source_->latencyMs() + 1.5;
}

std::string MedianFilter::pipeline() const
{
	return source_->pipeline() + " + median(3)";
}
