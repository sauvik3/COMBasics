#include <objbase.h>
#include "Registry.h"
#include "CalcObjGuid.h"

#define CalcObjProgId "MyCOMLibs.Calculation"

extern HMODULE g_hModule;

BOOL HelperWriteKey(HKEY roothk, const char *lpSubKey, LPCTSTR val_name, DWORD dwType, void *lpvData, DWORD dwDataSize)
{
	HKEY hk;
	if (ERROR_SUCCESS != RegCreateKey(roothk, lpSubKey, &hk))
		return FALSE;

	if (ERROR_SUCCESS != RegSetValueEx(hk, val_name, 0, dwType, (CONST BYTE *)lpvData, dwDataSize))
		return FALSE;

	if (ERROR_SUCCESS != RegCloseKey(hk))
		return FALSE;

	return TRUE;
}

HRESULT DllRegisterServer(HMODULE hModule, const CLSID & clsid, const char * szFriendlyName, const char * szVerIndProgID, const char * szProgID)
{
	WCHAR *lpwszClsid;
	char szBuff[MAX_PATH] = "";
	char szClsid[MAX_PATH] = "", szInproc[MAX_PATH] = "", szProgId[MAX_PATH];
	char szDescriptionVal[256] = "";

	StringFromCLSID(CLSID_CalcObject, &lpwszClsid);

	wsprintf(szClsid, "%S", lpwszClsid);
	wsprintf(szInproc, "%s\\%s\\%s", "clsid", szClsid, "InprocServer32");
	wsprintf(szProgId, "%s\\%s\\%s", "clsid", szClsid, "ProgId");

	//write default value 
	wsprintf(szBuff, "%s", "Calculation routines for basic arithmetic.");
	wsprintf(szDescriptionVal, "%s\\%s", "clsid", szClsid);

	HelperWriteKey(
		HKEY_CLASSES_ROOT,
		szDescriptionVal,
		NULL,//write to the "default" value
		REG_SZ,
		(void*)szBuff,
		lstrlen(szBuff)
	);


	//
	//write the "InprocServer32" key data
	//
	GetModuleFileName(
		g_hModule,
		szBuff,
		sizeof(szBuff));
	HelperWriteKey(
		HKEY_CLASSES_ROOT,
		szInproc,
		NULL,//write to the "default" value
		REG_SZ,
		(void*)szBuff,
		lstrlen(szBuff)
	);

	//
	//write the "ProgId" key data under HKCR\clsid\{---}\ProgId
	//
	lstrcpy(szBuff, CalcObjProgId);
	HelperWriteKey(
		HKEY_CLASSES_ROOT,
		szProgId,
		NULL,
		REG_SZ,
		(void*)szBuff,
		lstrlen(szBuff)
	);


	//
	//write the "ProgId" data under HKCR\CodeGuru.FastAddition
	//
	wsprintf(szBuff, "%s", "Calculation routines for basic arithmetic.");
	HelperWriteKey(
		HKEY_CLASSES_ROOT,
		CalcObjProgId,
		NULL,
		REG_SZ,
		(void*)szBuff,
		lstrlen(szBuff)
	);


	wsprintf(szProgId, "%s\\%s", CalcObjProgId, "CLSID");
	HelperWriteKey(
		HKEY_CLASSES_ROOT,
		szProgId,
		NULL,
		REG_SZ,
		(void*)szClsid,
		lstrlen(szClsid)
	);

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
