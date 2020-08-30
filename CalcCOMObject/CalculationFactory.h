#pragma once
#include <objbase.h>

extern long g_nComObjsInUse;

class CCalculationFactory : public IClassFactory
{
public:
	// constructor-destructor pair
	CCalculationFactory();
	virtual ~CCalculationFactory();

	//interface IUnknown methods 
	STDMETHOD_(ULONG, AddRef)() override;
	STDMETHOD_(ULONG, Release)() override;
	STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppObj) override;

	//interface IClassFactory methods 
	STDMETHOD(CreateInstance)(IUnknown* pUnknownOuter, const IID& iid, LPVOID *ppv) override;
	STDMETHOD(LockServer)(BOOL bLock) override;

private:
	long m_nRefCount;
};
