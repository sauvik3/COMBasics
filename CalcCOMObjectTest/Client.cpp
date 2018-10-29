#include <objbase.h>
#include <stdio.h>
#import "CalcCOMObject.dll"
//
//Here we do a #import on the DLL ,you can also do a #import on the .TLB 
//The #import directive generates two files (.tlh/.tli) in the output folders.
//

int main()
{

	int n1 = 100, n2 = 200;
	int nOutPut = 0;

	CoInitialize(NULL);
	MyMathLib::ICalculationPtr pCalculationObj;
	//
	//ICalculationPtr is not the actual interface ICalculation, but a template C++ class (_com_ptr_t)
	//that contains an embedded instance of the raw ICalculation pointer
	//While destructing , the destructor makes sure to invoke Release() on the internal
	//raw interface pointer. Further, the operator -> has been overloaded to direct all
	//method invocations to the internal raw interface pointer.
	//
	pCalculationObj.CreateInstance("MyCOMLibs.Calculation");

	pCalculationObj->Addition(n1, n2, &nOutPut);//"->" overloading in action

	printf("\nOutput after adding %d & %d is %d\n", n1, n2, nOutPut);

	return 0;
}