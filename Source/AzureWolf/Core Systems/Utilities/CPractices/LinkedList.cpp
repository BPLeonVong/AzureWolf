#include "AzureWolfStd.h"
#include "LinkedList.h"


PLinkedList::PLinkedList()
{
	head = NULL;
	curr = NULL;
	temp = NULL;
}

void PLinkedList::PInsert(int data)
{
	nodePtr n = new node;
	n->next = NULL;
	n->prev = NULL;
	n->x = data;

	if (head != NULL)
	{
		n->prev = tail;
		tail->next = n;
		tail = n;
		tail->next = head;
		head->prev = tail;
	}
	else
	{
		head = n;
		tail = n;
	}
}

void PLinkedList::PDelete(int data)
{
	nodePtr delNode = NULL;
	temp = head;
	curr = head;
	while (curr != NULL && curr->x != data)
	{
		temp = curr;
		curr = curr->next;
	}
	if (curr == NULL)
	{
		cout << "The deletion you requested was not in the list"<<endl;
	}
	else
	{
		delNode = curr;
		if (curr == head)
		{
			head = curr->next;
			tail->next = head;
			head->prev = tail;
			curr = curr->next;
		}
		else if (curr == tail)
		{
			tail = curr->prev;
			head->prev = tail;
			tail->next = head;
			curr = curr->prev;
		}
		else
		{
			curr = curr->next;
			temp->next = curr;
			curr->prev = temp;
		}
		delete delNode;
	}
}

void PLinkedList::Insert(int data)
{
	PInsert(data);
}


void PLinkedList::Delete(int data)
{
	PDelete(data);
}


PLinkedList::~PLinkedList()
{
}

void PLinkedList::Display()
{
	DForward();
	DBackward();
	cout << "Head - " << head->prev->x << " " << head->x << " " << head->next->x << endl;
	cout << "Tail - " << tail->prev->x << " " << tail->x << " " << tail->next->x << endl;
}

void PLinkedList::DForward()
{
	curr = head;
	do
	{
		cout << curr->x << endl;
		curr = curr->next;
	} while (curr != head);
}

void PLinkedList::DBackward()
{
	curr = tail;
	do
	{
		cout << curr->x << endl;
		curr = curr->prev;
	} while (curr != tail);
}