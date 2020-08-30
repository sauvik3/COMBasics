#pragma once
#include "Calculation_h.h"
#include "CalcObjGuid.h"

extern long g_nComObjsInUse;

class CCalculationObj : public ICalculation
{
public:
	CCalculationObj();
	virtual ~CCalculationObj() = default;

	//IUnknown interface
	STDMETHOD_(ULONG, AddRef)() override;
	STDMETHOD_(ULONG, Release)() override;
	STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppObj) override;

	//ICalculation interface
	STDMETHOD(Addition)(int op1, int op2, int *result) override;
	STDMETHOD(Subtraction)(int op1, int op2, int *result) override;

private:
	long m_nRefCount;
};
