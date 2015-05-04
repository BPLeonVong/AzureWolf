#pragma once

#include <iostream>

using namespace std;

class PLinkedList
{
private:

	typedef class node
	{
	public:
		int x;
		node *next;
		node *prev;
	}* nodePtr;

	nodePtr head;
	nodePtr tail;
	nodePtr curr;
	nodePtr temp;

	void PInsert(int data);
	void PDelete(int data);
public:
	PLinkedList();
	~PLinkedList();
	void Display();
	void Insert(int data);
	void Delete(int data);
	void DForward();
	void DBackward();
};
