#include "command/NoCommand.h"

#include <iostream>

void NoCommand::execute()
{
	std::cout << "      (빈 슬롯)\n";
}

void NoCommand::undo()
{
	std::cout << "      (되돌릴 것 없음)\n";
}

std::string NoCommand::name() const
{
	return "빈 슬롯";
}
