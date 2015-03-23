#include "AzureWolfStd.h"
#include "Recursion.h"

int rRecursiveNumberTest = 10;

PRecursion::PRecursion()
{
}

PRecursion::~PRecursion()
{
}

void PRecursion::Display()
{
	cout<<"Recursion.h is initialized."<<endl;
	RecursiveFunction(rRecursiveNumberTest);
}

void PRecursion::RecursiveFunction(int numberSize)
{
	if (numberSize < 0)
		return;

	cout << numberSize << endl;
	RecursiveFunction(numberSize-1);
}