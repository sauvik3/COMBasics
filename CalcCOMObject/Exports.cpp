#include    <objbase.h>
#include    "CalculationFactory.h"
#include    "CalcObjGuid.h"

HMODULE g_hModule = nullptr;
long g_nComObjsInUse = 0;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		g_hModule = (HMODULE)hModule;
	}
	return TRUE;
}

STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, void** ppv)
{
	if (clsid == CLSID_CalcObject) {
		CCalculationFactory *pCalcFact = new CCalculationFactory();
		if (pCalcFact == nullptr)
			return E_OUTOFMEMORY;
		else
			return pCalcFact->QueryInterface(iid, ppv);
	}

	return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow()
{
	return (g_nComObjsInUse == 0) ? TRUE : FALSE;
}
