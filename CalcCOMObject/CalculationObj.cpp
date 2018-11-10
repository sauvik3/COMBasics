#include <objbase.h>
#include "CalculationObj.h"
#include "Calculation_i.c"

STDMETHODIMP CCalculationObj::QueryInterface(REFIID riid, LPVOID *ppObj) {
	if ((riid == IID_IUnknown) || (riid == IID_ICalculation)) {
		*ppObj = static_cast<ICalculation *>(this);
	}
	else {
		*ppObj = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppObj)->AddRef();

	return S_OK;
}

STDMETHODIMP_(ULONG) CCalculationObj::AddRef()
{
	return ::InterlockedIncrement(&m_nRefCount);
}

STDMETHODIMP_(ULONG) CCalculationObj::Release()
{
	if (::InterlockedDecrement(&m_nRefCount) == 0) {
		delete this;
		return 0;
	}
	return m_nRefCount;
}

STDMETHODIMP CCalculationObj::Addition(int op1, int op2, int * result)
{
	try
	{
		*result = op1 + op2;
	}
	catch (...)
	{
		return E_FAIL;
	}
	return S_OK;
}

STDMETHODIMP CCalculationObj::Subtraction(int op1, int op2, int * result)
{
	try
	{
		*result = op1 - op2;
	}
	catch (...)
	{
		return E_FAIL;
	}
	return S_OK;
}
