#include "CppUnitTestLogger.h"
#include "CalculationObj.h"
#include "unittests.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void UnitTests::CCalculationObjTest::CCalculationObj_AdditionTest()
{
	int n1 = 100, n2 = 200;
	int nOutPut = 0;
	try
	{
		CCalculationObj calcObj;
		calcObj.Addition(n1, n2, &nOutPut);
		Assert::AreEqual(nOutPut, 300);
	}
	catch (const std::exception& e)
	{
		Logger::WriteMessage(e.what());
	}
}

void UnitTests::CCalculationObjTest::CCalculationObj_SubtractionTest()
{
	int n1 = 500, n2 = 200;
	int nOutPut = 0;
	try
	{
		CCalculationObj calcObj;
		calcObj.Subtraction(n1, n2, &nOutPut);
		Assert::AreEqual(nOutPut, 300);
	}
	catch (const std::exception& e)
	{
		Logger::WriteMessage(e.what());
	}
}
