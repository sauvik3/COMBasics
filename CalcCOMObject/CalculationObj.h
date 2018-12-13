#pragma once
#include "Calculation_h.h"
#include "CalcObjGuid.h"

extern long g_nComObjsInUse;

class CCalculationObj : public ICalculation
{
public:
	//IUnknown interface
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppObj);

	//ICalculation interface
	STDMETHOD(Addition)(int op1, int op2, int *result);
	STDMETHOD(Subtraction)(int op1, int op2, int *result);

private:
	long m_nRefCount;
};
