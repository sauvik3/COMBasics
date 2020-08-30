#include <comdef.h>
#include <iostream>
#include "CalculationObj.h"

int main()
{
	const int n1 = 100;
	const int n2 = 200;
	int nOutPut = 0;

	try
	{
		ICalculation* pCalculationObj;

		CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
		const HRESULT hr = CoCreateInstance(CLSID_CalcObject, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pCalculationObj));
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
