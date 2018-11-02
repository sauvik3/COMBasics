#pragma once
#include <objbase.h>

extern long g_nComObjsInUse;

class CCalculationFactory : public IClassFactory
{
public:
	// constructor-destructor pair
	CCalculationFactory();
	~CCalculationFactory();

	//interface IUnknown methods 
	virtual HRESULT __stdcall QueryInterface(REFIID riid, LPVOID *ppObj);
	virtual ULONG   __stdcall AddRef();
	virtual ULONG   __stdcall Release();

	//interface IClassFactory methods 
	virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, LPVOID *ppv);
	virtual HRESULT __stdcall LockServer(BOOL bLock);

private:
	long m_nRefCount;
};
