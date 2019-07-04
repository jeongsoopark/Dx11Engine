#include "ErrLogger.h"
#include <comdef.h>

ErrLogger::ErrLogger()
{
}


ErrLogger::~ErrLogger()
{
}

void ErrLogger::Log(std::string msg)
{
	std::string err_msg = "Error : " + msg;
	MessageBoxA(NULL, err_msg.c_str(), "ERROR", MB_ICONERROR);
}

void ErrLogger::Log(HRESULT hr, std::string msg)
{
	_com_error error(hr);
	std::string errText = std::string(error.ErrorMessage());
	std::wstring err_msg = L"Error : " + StringConverter::StringToWideString(msg) + L"\n" + StringConverter::StringToWideString(errText);
	MessageBoxW(NULL, err_msg.c_str(), L"ERROR", MB_ICONERROR);
}

void ErrLogger::Log(HRESULT hr, std::wstring msg)
{
	_com_error error(hr);
	std::string errText = std::string(error.ErrorMessage());
	std::wstring err_msg = L"Error : " + msg + L"\n" + StringConverter::StringToWideString(errText);
	MessageBoxW(NULL, err_msg.c_str(), L"ERROR", MB_ICONERROR);
}



