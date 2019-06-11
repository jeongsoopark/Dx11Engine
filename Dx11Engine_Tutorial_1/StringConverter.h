#pragma once
#include <string>
using namespace std;

class StringConverter
{
public:
	StringConverter();
	~StringConverter();

	static std::wstring StringToWideString(std::string str);

};

