#include <objbase.h>
#include <iostream>
#import "CalcCOMObject.dll"

int main()
{
	int n1 = 100, n2 = 200;
	int nOutPut = 0;

	try
	{
		CoInitialize(NULL);
		MyMathLib::ICalculationPtr pCalculationObj;
		HRESULT hr = pCalculationObj.CreateInstance("MyCOMLibs.Calculation");
		_com_util::CheckError(hr);
		pCalculationObj->Addition(n1, n2, &nOutPut);
		std::cout << "Output after adding " << n1 << " and " << n2 << " is " << nOutPut << ".";
	}
	catch (const _com_error& e)
	{
		std::wcerr << L"Error : " << e.ErrorMessage();
	}

	return 0;
}
