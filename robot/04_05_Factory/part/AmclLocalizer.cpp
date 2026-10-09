#include "part/AmclLocalizer.h"

std::string AmclLocalizer::spec() const
{
	return "AMCL (미리 만든 점유 격자 지도에 스캔을 맞춘다)";
}

std::string AmclLocalizer::frame() const
{
	return "map";
}
