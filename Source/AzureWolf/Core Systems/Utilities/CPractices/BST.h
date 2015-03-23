#pragma once

#include <iostream>

using namespace std;

class PBST
{
public:
	PBST();
	~PBST();
	void Display();
};

class BSTreeNode
{
	int keyValue;
	BSTreeNode *left;
	BSTreeNode *right;
};