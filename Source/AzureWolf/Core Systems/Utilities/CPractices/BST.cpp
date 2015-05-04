#include "AzureWolfStd.h"
#include "BST.h"


PBST::PBST()
{
	root = NULL;
}

PBST::~PBST()
{
}


PBST::Node* PBST::CreateLeaf(int key)
{
	Node* n = new Node;
	n->keyValue = key;
	n->left = NULL;
	n->right = NULL;
	return n;
}

void PBST::Insert(int value)
{
	PInsert(value, root);
}

void PBST::PInsert(int value, Node* ptr)
{
	if (root == NULL)
	{
		root = CreateLeaf(value);
	}
	else if (value < ptr->keyValue)
	{
		if (ptr->left != NULL)
		{
			PInsert(value, ptr->left);
		}
		else
		{
			ptr->left = CreateLeaf(value);
		}
	}
	else if (value > ptr->keyValue)
	{
		if (ptr->right != NULL)
		{
			PInsert(value, ptr->right);
		}
		else
		{
			ptr->right = CreateLeaf(value);
		}
	}
	else
	{
		cout << "The key " << value << " has already been added to the list." << endl;
	}
}

void PBST::PInOrder(Node* ptr)
{
	if (root!=NULL)
	{
		if (ptr->left != NULL)
		{
			PInOrder(ptr->left);
		}
		cout << "Hello "<< ptr->keyValue << endl;
		if (ptr->right != NULL)
		{
			PInOrder(ptr->right);
		}
	}
	else
	{
		cout << "The tree is empty"<<endl;
	}
	return;
}

void PBST::PPreOrder(Node* ptr)
{
	if (root != NULL)
	{
		cout << "Hello " << ptr->keyValue << endl;
		if (ptr->left != NULL)
		{
			PInOrder(ptr->left);
		}
		if (ptr->right != NULL)
		{
			PInOrder(ptr->right);
		}
	}
	else
	{
		cout << "The tree is empty" << endl;
	}
	return;
}

void PBST::PPostOrder(Node* ptr)
{
	if (root != NULL)
	{
		if (ptr->left != NULL)
		{
			PInOrder(ptr->left);
		}
		if (ptr->right != NULL)
		{
			PInOrder(ptr->right);
		}
		cout << "Hello " << ptr->keyValue << endl;
	}
	else
	{
		cout << "The tree is empty" << endl;
	}
	return;
}

void PBST::PreOrder()
{
	PPreOrder(root);
}

void PBST::InOrder()
{
	PInOrder(root);
}

void PBST::PostOrder()
{
	PPostOrder(root);
}

void PBST::Display()
{
	cout<<"BST.h is initialized."<<endl;
	PreOrder();
	InOrder();
	PostOrder();
}