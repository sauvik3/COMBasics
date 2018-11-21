#pragma once

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(CCalculationObjTest)
	{
	public:
		TEST_METHOD(CCalculationObj_AdditionTest);
		TEST_METHOD(CCalculationObj_SubtractionTest);
	};
}