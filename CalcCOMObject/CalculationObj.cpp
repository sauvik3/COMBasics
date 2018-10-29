#include "CalculationObj.h"
#include "Calculation_i.c"

HRESULT CCalculationObj::QueryInterface(REFIID riid, void ** ppObj) {
	*ppObj = NULL;
	if (riid == IID_IUnknown) {
		*ppObj = static_cast<void*>(this);
		AddRef();
		return S_OK;
	}
	if (riid == IID_ICalculation) {
		*ppObj = static_cast<void*>(this);
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}

ULONG CCalculationObj::AddRef()
{
	return InterlockedIncrement(&m_nRefCount);
}

ULONG CCalculationObj::Release()
{
	long nRefCount = InterlockedDecrement(&m_nRefCount);
	if (nRefCount == 0)
		delete this;
	return nRefCount;
}

HRESULT CCalculationObj::Addition(int op1, int op2, int * result)
{
	try {
		*result = op1 + op2;
	}
	catch (...) {
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCalculationObj::Subtraction(int op1, int op2, int * result)
{
	try {
	*result = op1 - op2;
	}
	catch (...) {
		return E_FAIL;
	}
	return S_OK;
}
