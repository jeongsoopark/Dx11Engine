#include "StringConverter.h"



StringConverter::StringConverter()
{
}


StringConverter::~StringConverter()
{
}


std::wstring StringConverter::StringToWideString(std::string str)
{
	std::wstring ret(str.begin(), str.end());
	return ret;
}
