#pragma once

#include <iostream>

using namespace std;

class PLinkedList
{
public:
	PLinkedList();
	~PLinkedList();
	void Display();
};

class node 
{
public:
	int x;
	node *next;
	node *prev;
};