#pragma once
#include <windows.h>

HRESULT DllRegisterServer(HMODULE hModule,
	const CLSID& clsid,
	const char* szFriendlyName,
	const char* szVerIndProgID,
	const char* szProgID);

HRESULT DllUnregisterServer(const CLSID& clsid,
	const char* szVerIndProgID,
	const char* szProgID);
