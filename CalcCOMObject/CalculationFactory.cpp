#include "CalculationFactory.h"
#include "CalculationObj.h"

CCalculationFactory::CCalculationFactory() : m_nRefCount(1) {}

CCalculationFactory::~CCalculationFactory()
{
	::InterlockedDecrement(&g_nComObjsInUse);
}

HRESULT CCalculationFactory::QueryInterface(REFIID riid, LPVOID *ppObj)
{
	if ((riid == IID_IUnknown) || (riid == IID_IClassFactory)) {
		*ppObj = static_cast<IClassFactory *>(this);
	}
	else {
		*ppObj = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppObj)->AddRef();
	return S_OK;
}

ULONG CCalculationFactory::AddRef()
{
	return ::InterlockedIncrement(&m_nRefCount);
}

ULONG CCalculationFactory::Release()
{
	if (::InterlockedDecrement(&m_nRefCount) == 0) {
		delete this;
		return 0;
	}
	return m_nRefCount;
}

HRESULT CCalculationFactory::CreateInstance(IUnknown * pUnknownOuter, const IID & iid, LPVOID *ppv)
{
	HRESULT hr;
	if (pUnknownOuter != nullptr) {
		return CLASS_E_NOAGGREGATION;
	}

	CCalculationObj* pObject = new CCalculationObj();
	if (pObject == nullptr)
		return E_OUTOFMEMORY;

	hr = pObject->QueryInterface(iid, ppv);
	if (FAILED(hr))
		pObject->Release();

	return hr;
}

HRESULT CCalculationFactory::LockServer(BOOL bLock)
{
	return E_NOTIMPL;
}
