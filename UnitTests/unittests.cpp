#include "CppUnitTestLogger.h"
#include "CalculationObj.h"
#include "unittests.h"
#include <comutil.h>
#include <comdef.h>
#include <Tchar.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void UnitTests::CCalculationObjTest::InitTests()
{
	Logger::WriteMessage("Initializing COM Library...");
	try
	{
		CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
		const HRESULT hr = CoCreateInstance(CLSID_CalcObject, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pCalculationObj));
		_com_util::CheckError(hr);
	}
	catch (const _com_error& e)
	{
		const size_t string_size = 80;
		TCHAR value[string_size] = _T("COM Error: ");
		_tcscat_s(value, string_size, e.ErrorMessage());
		Logger::WriteMessage(value);
	}
	Assert::IsNotNull(pCalculationObj);
}

void UnitTests::CCalculationObjTest::CleanupTests()
{
	Logger::WriteMessage("Releasing COM Library...");
	try
	{
		Assert::IsNotNull(pCalculationObj);
		pCalculationObj->Release();
	}
	catch (const _com_error& e)
	{
		const size_t string_size = 80;
		TCHAR value[string_size] = _T("COM Error: ");
		_tcscat_s(value, string_size, e.ErrorMessage());
		Logger::WriteMessage(value);
	}
}

void UnitTests::CCalculationObjTest::CCalculationObj_AdditionTest()
{
	const int n1 = 100;
	const int n2 = 200;
	int nOutPut = 0;
	try
	{
		pCalculationObj->Addition(n1, n2, &nOutPut);
		Assert::AreEqual(nOutPut, 300);
	}
	catch (const std::exception& e)
	{
		Logger::WriteMessage(e.what());
	}
}

void UnitTests::CCalculationObjTest::CCalculationObj_SubtractionTest()
{
	const int n1 = 500;
	const int n2 = 200;
	int nOutPut = 0;
	try
	{
		pCalculationObj->Subtraction(n1, n2, &nOutPut);
		Assert::AreEqual(nOutPut, 300);
	}
	catch (const std::exception& e)
	{
		Logger::WriteMessage(e.what());
	}
}
