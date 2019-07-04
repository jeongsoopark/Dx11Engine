#pragma once
#include "StringConverter.h"
#include <windows.h>

class ErrLogger
{
public:
	ErrLogger();
	~ErrLogger();

	static void Log(std::string msg);
	static void Log(HRESULT hr, std::string msg );
	static void Log(HRESULT hr, std::wstring msg );
};

