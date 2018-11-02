#pragma once
#include "Calculation_h.h"

extern long g_nComObjsInUse;

class CCalculationObj : public ICalculation
{
public:
	//IUnknown interface
	virtual HRESULT __stdcall QueryInterface(REFIID riid, LPVOID *ppObj);
	virtual ULONG   __stdcall AddRef();
	virtual ULONG   __stdcall Release();

	//ICalculation interface
	HRESULT __stdcall Addition(int op1, int op2, int *result);
	HRESULT __stdcall Subtraction(int op1, int op2, int *result);

private:
	long m_nRefCount;
};
