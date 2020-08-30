#include <comdef.h>
#include <iostream>
#include "CalculationObj.h"

int main()
{
	int n1 = 100, n2 = 200;
	int nOutPut = 0;

	try
	{
		HRESULT hr;
		ICalculation* pCalculationObj;

		CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
		hr = CoCreateInstance(CLSID_CalcObject, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pCalculationObj));
		_com_util::CheckError(hr);

		pCalculationObj->Addition(n1, n2, &nOutPut);
		std::cout << "Output after adding " << n1 << " and " << n2 << " is " << nOutPut << ".";
		pCalculationObj->Release();
	}
	catch (const _com_error& e)
	{
		std::wcerr << L"Error : " << e.ErrorMessage();
	}

	return 0;
}
