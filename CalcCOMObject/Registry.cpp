#include <iostream>
#include <objbase.h>
#include "strsafe.h"
#include "Tchar.h"
#include "Registry.h"
#include "CalcObjGuid.h"

#define CalcObjProgId TEXT("MyCOMLibs.Calculation")

extern HMODULE g_hModule;

STDAPI DllRegisterServer(void)
{
	LPOLESTR		lpwszClsid;
	TCHAR			szBuff[MAX_PATH] = TEXT("");
	CHAR			szClsid[MAX_PATH] = "",
					szInproc[MAX_PATH] = "",
					szProgId[MAX_PATH] = "";
	CHAR			szDescriptionVal[MAX_PATH] = "";
	const size_t	sz0 = MAX_PATH * sizeof(CHAR);
	const size_t	sz = MAX_PATH * sizeof(TCHAR);
	LSTATUS			status;

	::StringFromCLSID(CLSID_CalcObject, &lpwszClsid);
	// Convert wchar_t * to CHAR *
	{
		const size_t origLen = wcslen(lpwszClsid) + 1;
		const size_t newsize = origLen * sizeof(CHAR);
		WideCharToMultiByte(CP_UTF8, 0, lpwszClsid, (int)origLen, szClsid, (int)newsize, nullptr, nullptr);
	}

	StringCbPrintfA(szInproc, sz0, "%s\\%s\\%s", "clsid", szClsid, "InprocServer32");
	StringCbPrintfA(szProgId, sz0, "%s\\%s\\%s", "clsid", szClsid, "ProgId");

	//write default value 
	StringCbPrintf(szBuff, sz, TEXT("%s"), TEXT("Calculation routines for basic arithmetic."));
	StringCbPrintfA(szDescriptionVal, sz0, "%s\\%s", "clsid", szClsid);
	{
		HKEY hk;
		status = RegCreateKeyExA(HKEY_CLASSES_ROOT, szDescriptionVal, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_QUERY_VALUE, nullptr, &hk, nullptr);
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);

		status = RegSetValueEx(hk, nullptr, 0, REG_SZ, (CONST BYTE *)szBuff, (DWORD)((_tcslen(szBuff) + 1) * sizeof(TCHAR)));
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);

		status = RegCloseKey(hk);
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);
	}

	//
	//write the "InprocServer32" key data
	//
	GetModuleFileName(g_hModule, szBuff, MAX_PATH);
	{
		HKEY hk;
		status = RegCreateKeyExA(HKEY_CLASSES_ROOT, szInproc, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_QUERY_VALUE, nullptr, &hk, nullptr);
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);

		status = RegSetValueEx(hk, nullptr, 0, REG_SZ, (CONST BYTE *)szBuff, (DWORD)((_tcslen(szBuff) + 1) * sizeof(TCHAR)));
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);

		status = RegCloseKey(hk);
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);
	}

	//
	//write the "ProgId" key data under HKCR\clsid\{---}\ProgId
	//
	StringCbPrintf(szBuff, sz, TEXT("%s"), CalcObjProgId);
	{
		HKEY hk;
		status = RegCreateKeyExA(HKEY_CLASSES_ROOT, szProgId, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_QUERY_VALUE, nullptr, &hk, nullptr);
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);

		status = RegSetValueEx(hk, nullptr, 0, REG_SZ, (CONST BYTE *)szBuff, (DWORD)((_tcslen(szBuff) + 1) * sizeof(TCHAR)));
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);

		status = RegCloseKey(hk);
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);
	}

	//
	//write the "ProgId" data under HKCR\MyCOMLibs.Calculation
	//
	StringCbPrintf(szBuff, sz, TEXT("%s"), TEXT("Calculation routines for basic arithmetic."));
	{
		HKEY hk;
		status = RegCreateKeyEx(HKEY_CLASSES_ROOT, CalcObjProgId, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_QUERY_VALUE, nullptr, &hk, nullptr);
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);

		status = RegSetValueEx(hk, nullptr, 0, REG_SZ, (CONST BYTE *)szBuff, (DWORD)((_tcslen(szBuff) + 1) * sizeof(TCHAR)));
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);

		HKEY hk1;
		status = RegCreateKeyExA(hk, "CLSID", 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_QUERY_VALUE, nullptr, &hk1, nullptr);
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);

		status = RegSetValueExA(hk1, nullptr, 0, REG_SZ, (CONST BYTE *)szClsid, (DWORD)((strlen(szClsid) + 1) * sizeof(CHAR)));
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);

		status = RegCloseKey(hk1);
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);

		status = RegCloseKey(hk);
		if (status != ERROR_SUCCESS)
			return HRESULT_FROM_WIN32(status);
	}

	return S_OK;
}

STDAPI DllUnregisterServer()
{
	LPOLESTR		lpwszClsid;
	CHAR			szKeyName0[MAX_PATH] = "";
	TCHAR			szKeyName[MAX_PATH] = TEXT("");
	CHAR			szClsid[MAX_PATH] = "";
	const size_t	sz0 = MAX_PATH * sizeof(CHAR);
	const size_t	sz = MAX_PATH * sizeof(TCHAR);
	LSTATUS			status;

	::StringFromCLSID(CLSID_CalcObject, &lpwszClsid);
	// Convert wchar_t * to CHAR *
	{
		const size_t origLen = wcslen(lpwszClsid) + 1;
		const size_t newsize = origLen * sizeof(CHAR);
		WideCharToMultiByte(CP_UTF8, 0, lpwszClsid, (int)origLen, szClsid, (int)newsize, nullptr, nullptr);
	}

	//
	//delete the ProgId entry
	//
	StringCbPrintf(szKeyName, sz, TEXT("%s\\%s"), CalcObjProgId, TEXT("CLSID"));
	status = RegDeleteKey(HKEY_CLASSES_ROOT, szKeyName);
	if (status != ERROR_SUCCESS)
		return HRESULT_FROM_WIN32(status);

	status = RegDeleteKey(HKEY_CLASSES_ROOT, CalcObjProgId);
	if (status != ERROR_SUCCESS)
		return HRESULT_FROM_WIN32(status);

	//
	//delete the CLSID entry for this COM object
	//
	StringCbPrintfA(szKeyName0, sz0, "%s\\%s\\%s", "clsid", szClsid, "InprocServer32");
	status = RegDeleteKeyA(HKEY_CLASSES_ROOT, szKeyName0);
	if (status != ERROR_SUCCESS)
		return HRESULT_FROM_WIN32(status);

	StringCbPrintfA(szKeyName0, sz0, "%s\\%s\\%s", "clsid", szClsid, "ProgId");
	status = RegDeleteKeyA(HKEY_CLASSES_ROOT, szKeyName0);
	if (status != ERROR_SUCCESS)
		return HRESULT_FROM_WIN32(status);

	StringCbPrintfA(szKeyName0, sz0, "%s\\%s", "clsid", szClsid);
	status = RegDeleteKeyA(HKEY_CLASSES_ROOT, szKeyName0);
	if (status != ERROR_SUCCESS)
		return HRESULT_FROM_WIN32(status);

	return S_OK;
}
