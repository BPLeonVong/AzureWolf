#include "AzureWolfStd.h"
#include "LinkedList.h"

node *root;
node *root1;
node *root2;
node *root3;

PLinkedList::PLinkedList()
{


  root = new node;
  root1 = new node;
  root2 = new node;
  root3 = new node;

  root->next = root1;
  root->prev = root3;
  root->x = 1;
       
  root1->next = root2;
  root1->prev = root;
  root1->x = 2;
       

  root2->next = root3;
  root2->prev = root1;
  root2->x = 3;
       

  root3->next = root;
  root3->prev = root2;
  root3->x = 4;
       
}

PLinkedList::~PLinkedList()
{
}

void PLinkedList::Display()
{
	cout << "LinkedList.h is initialized." << endl;
	cout << root->prev->x << endl;
	cout << root->x << endl;
	cout << root->next->x << endl;
	cout << root1->prev->x << endl;
	cout << root1->x << endl;
	cout << root1->next->x << endl;
	cout << root2->prev->x << endl;
	cout << root2->x << endl;
	cout << root2->next->x << endl;
	cout << root3->prev->x << endl;
	cout << root3->x << endl;
	cout << root3->next->x << endl;

}