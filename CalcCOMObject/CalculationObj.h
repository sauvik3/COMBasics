#pragma once
#include "Calculation_h.h"

extern long g_nComObjsInUse;

class CCalculationObj : public ICalculation
{
public:
	//IUnknown interface
	HRESULT __stdcall QueryInterface(REFIID riid, void **ppObj);
	ULONG   __stdcall AddRef();
	ULONG   __stdcall Release();

	//ICalculation interface
	HRESULT __stdcall Addition(int op1, int op2, int *result);
	HRESULT __stdcall Subtraction(int op1, int op2, int *result);

private:
	long m_nRefCount;
};