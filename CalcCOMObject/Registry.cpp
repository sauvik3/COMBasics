#include <iostream>
#include <objbase.h>
#include "Registry.h"
#include "CalcObjGuid.h"

#define CalcObjProgId "MyCOMLibs.Calculation"

extern HMODULE g_hModule;

LSTATUS HelperWriteKey(HKEY roothk, LPCSTR lpSubKey, LPCTSTR val_name, DWORD dwType, LPVOID lpvData, DWORD dwDataSize)
{
	HKEY hk;
	LSTATUS status;

	status = RegCreateKeyEx(roothk, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_QUERY_VALUE, NULL, &hk, NULL);
	if (status != ERROR_SUCCESS)
		return status;

	status = RegSetValueEx(hk, val_name, 0, dwType, (CONST BYTE *)lpvData, dwDataSize);
	if (status != ERROR_SUCCESS)
		return status;

	status = RegCloseKey(hk);

	return status;
}

HRESULT DllRegisterServer(HMODULE hModule, const CLSID & clsid, const char * szFriendlyName, const char * szVerIndProgID, const char * szProgID)
{
	WCHAR *lpwszClsid;
	char szBuff[MAX_PATH] = "";
	char szClsid[MAX_PATH] = "", szInproc[MAX_PATH] = "", szProgId[MAX_PATH];
	char szDescriptionVal[256] = "";
	LSTATUS status;

	StringFromCLSID(CLSID_CalcObject, &lpwszClsid);

	wsprintf(szClsid, "%S", lpwszClsid);
	wsprintf(szInproc, "%s\\%s\\%s", "clsid", szClsid, "InprocServer32");
	wsprintf(szProgId, "%s\\%s\\%s", "clsid", szClsid, "ProgId");

	//write default value 
	wsprintf(szBuff, "%s", "Calculation routines for basic arithmetic.");
	wsprintf(szDescriptionVal, "%s\\%s", "clsid", szClsid);

	status = HelperWriteKey(
		HKEY_CLASSES_ROOT,
		szDescriptionVal,
		NULL,//write to the "default" value
		REG_SZ,
		(LPVOID)szBuff,
		lstrlen(szBuff)
	);
	if (status != ERROR_SUCCESS)
		return E_FAIL;

	//
	//write the "InprocServer32" key data
	//
	GetModuleFileName(
		g_hModule,
		szBuff,
		sizeof(szBuff));
	status = HelperWriteKey(
		HKEY_CLASSES_ROOT,
		szInproc,
		NULL,//write to the "default" value
		REG_SZ,
		(LPVOID)szBuff,
		lstrlen(szBuff)
	);
	if (status != ERROR_SUCCESS)
		return E_FAIL;

	//
	//write the "ProgId" key data under HKCR\clsid\{---}\ProgId
	//
	lstrcpy(szBuff, CalcObjProgId);
	status = HelperWriteKey(
		HKEY_CLASSES_ROOT,
		szProgId,
		NULL,
		REG_SZ,
		(LPVOID)szBuff,
		lstrlen(szBuff)
	);
	if (status != ERROR_SUCCESS)
		return E_FAIL;


	//
	//write the "ProgId" data under HKCR\CodeGuru.FastAddition
	//
	wsprintf(szBuff, "%s", "Calculation routines for basic arithmetic.");
	status = HelperWriteKey(
		HKEY_CLASSES_ROOT,
		CalcObjProgId,
		NULL,
		REG_SZ,
		(void*)szBuff,
		lstrlen(szBuff)
	);
	if (status != ERROR_SUCCESS)
		return E_FAIL;


	wsprintf(szProgId, "%s\\%s", CalcObjProgId, "CLSID");
	status = HelperWriteKey(
		HKEY_CLASSES_ROOT,
		szProgId,
		NULL,
		REG_SZ,
		(void*)szClsid,
		lstrlen(szClsid)
	);
	if (status != ERROR_SUCCESS)
		return E_FAIL;

	return S_OK;
}

HRESULT DllUnregisterServer(const CLSID & clsid, const char * szVerIndProgID, const char * szProgID)
{
	//
	//As per COM guidelines, every self removable COM inprocess component
	//should export the function DllUnregisterServer for erasing all the 
	//information that was printed into the registry
	//
	//

	char szKeyName[256] = "", szClsid[256] = "";
	WCHAR *lpwszClsid;



	//
	//delete the ProgId entry
	//
	wsprintf(szKeyName, "%s\\%s", CalcObjProgId, "CLSID");
	RegDeleteKey(HKEY_CLASSES_ROOT, szKeyName);
	RegDeleteKey(HKEY_CLASSES_ROOT, CalcObjProgId);


	//
	//delete the CLSID entry for this COM object
	//
	StringFromCLSID(
		CLSID_CalcObject,
		&lpwszClsid);
	wsprintf(szClsid, "%S", lpwszClsid);
	wsprintf(szKeyName, "%s\\%s\\%s", "CLSID", szClsid, "InprocServer32");
	RegDeleteKey(HKEY_CLASSES_ROOT, szKeyName);

	wsprintf(szKeyName, "%s\\%s\\%s", "CLSID", szClsid, "ProgId");
	RegDeleteKey(HKEY_CLASSES_ROOT, szKeyName);

	wsprintf(szKeyName, "%s\\%s", "CLSID", szClsid);
	RegDeleteKey(HKEY_CLASSES_ROOT, szKeyName);

	return S_OK;
}
