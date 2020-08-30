#pragma once

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(CCalculationObjTest)
	{
	public:
		TEST_METHOD_INITIALIZE(InitTest);
		TEST_METHOD(CCalculationObj_AdditionTest);
		TEST_METHOD(CCalculationObj_SubtractionTest);
		TEST_METHOD_CLEANUP(CleanupTest);

	private:
		ICalculation* pCalculationObj;
	};
}