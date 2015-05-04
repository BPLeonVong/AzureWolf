#pragma once

#include <iostream>

using namespace std;

class PBST
{
private:
	struct Node
	{
		int keyValue;
		Node* left;
		Node* right;
	};
	Node* root;

	void PPreOrder(Node* node);
	void PInOrder(Node* node);
	void PPostOrder(Node* node);
	void PInsert(int key, Node* ptr);
public:
	PBST();
	~PBST();

	Node *CreateLeaf(int key);
	void Display();
	void PreOrder();
	void InOrder();
	void PostOrder( );
	void Insert(int value);

};
