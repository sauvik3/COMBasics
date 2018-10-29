#include "CalculationFactory.h"
#include "CalculationObj.h"

CCalculationFactory::CCalculationFactory()
{
	m_nRefCount = 0;
	InterlockedIncrement(&g_nComObjsInUse);
}

CCalculationFactory::~CCalculationFactory()
{
	InterlockedDecrement(&g_nComObjsInUse);
}

HRESULT CCalculationFactory::QueryInterface(REFIID riid, void ** ppObj)
{
	*ppObj = NULL;
	if (riid == IID_IUnknown) {
		*ppObj = static_cast<void*>(this);
		AddRef();
		return S_OK;
	}
	if (riid == IID_IClassFactory) {
		*ppObj = static_cast<void*>(this);
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}

ULONG CCalculationFactory::AddRef()
{
	return InterlockedIncrement(&m_nRefCount);
}

ULONG CCalculationFactory::Release()
{
	long nRefCount = 0;
	nRefCount = InterlockedDecrement(&m_nRefCount);
	if (nRefCount == 0)
		delete this;
	return nRefCount;
}

HRESULT CCalculationFactory::CreateInstance(IUnknown * pUnknownOuter, const IID & iid, void ** ppv)
{
	if (pUnknownOuter != nullptr) {
		return CLASS_E_NOAGGREGATION;
	}

	CCalculationObj* pObject = new CCalculationObj();
	if (pObject == nullptr)
		return E_OUTOFMEMORY;

	return pObject->QueryInterface(iid, ppv);
}

HRESULT CCalculationFactory::LockServer(BOOL bLock)
{
	return E_NOTIMPL;
}
