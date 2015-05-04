#pragma once

class A
{
public:
	A(int n);

	~A();

protected:
	int m_i;
};

class B
	: public A
{
public:
	B(int n);

public:
	~B();

private:
	A m_a1;
	A m_a2;
};