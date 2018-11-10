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
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppObj);

	//interface IClassFactory methods 
	STDMETHOD(CreateInstance)(IUnknown* pUnknownOuter, const IID& iid, LPVOID *ppv);
	STDMETHOD(LockServer)(BOOL bLock);

private:
	long m_nRefCount;
};
