#include "AzureWolfStd.h"
#include "Structors.h"


A::A(int n = 2) : m_i(n)
{
	std::cout << "A Type Contructor " << m_i << std::endl;
}

A::~A()
{
	std::cout << "A Type Destructor " << m_i << std::endl;
}

B::B(int n) : m_a1(m_i + 1), m_a2(n) 
{
	std::cout << "B Type Contructor " << m_i << std::endl;
}

B::~B()
{
	std::cout << "B Type Destructor " << m_i<<std::endl;
	--m_i;
}