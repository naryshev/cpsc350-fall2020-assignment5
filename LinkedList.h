/*
Daniel Naryshev
2327209
dnaryshev@chapman.edu

Eshaan Vora
2318955
evora@chapman.edu

Assignment 5 - Student DB
*/
#include "ListNode.h"
#include <iostream>

using namespace std;

template <class T>
class LinkedList
{
	private:
		ListNode<T> *back;
		unsigned int size;

	public:
		LinkedList();
		~LinkedList();
		ListNode<T> *head;

		void insertFront(T d);
		T removeFront();
		void insertBack(T d);
		T removeBack();
		T peekHead();
		T peekBack();
		bool contains(T data);
		unsigned int getSize();
		bool isEmpty();
		bool remove(T d);
};

template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	back = NULL;
	size = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	ListNode<T> *temp = head;
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = NULL;
		temp->prev = NULL;
		delete head;
		head = temp;
	}
}

template <class T>
void LinkedList<T>::insertFront(T d)
{
	ListNode<T> *node = new ListNode<T>(d);
	if (size == 0)
		back = node;
	else
	{
		head->prev = node;
		node->next = head;
	}
	head = node;
	++size;
}

template <class T>
T LinkedList<T>::removeFront()
{
	ListNode<T> *temp = head;
	if (head->next == NULL)
		back = NULL;
	else
	{
		head->next->prev = NULL;
		head = head->next;
	}

	T val = temp->data;
	temp->next = NULL;
	delete temp;
	--size;
	return val;
}

template <class T>
void LinkedList<T>::insertBack(T d)
{
	ListNode<T> *node = new ListNode<T>(d);
	if (size == 0)
		head = node;
	else
	{
		back->next = node;
		node->prev = back;
	}
	back = node;
	++size;
}

template <class T>
T LinkedList<T>::removeBack()
{
	ListNode<T> *temp = back;
	if (back->prev == NULL)
		head = NULL;
	else
	{
		back->prev->next = NULL;
		back = back->prev;
	}

	T val = temp->data;
	temp->prev = NULL;
	delete temp;
	--size;
	return val;
}

template <class T>
T LinkedList<T>::peekHead()
{
	return head->data;
}

template <class T>
T LinkedList<T>::peekBack()
{
	return back->data;
}

template <class T>
bool LinkedList<T>::contains(T data)
{
	ListNode<T> *temp = head;
	while (temp != NULL)
	{
		if (temp->data == data)
			return true;
		else
			temp = temp->next;
	}
	return false;
}

template <class T>
unsigned int LinkedList<T>::getSize()
{
	return size;
}

template <class T>
bool LinkedList<T>::isEmpty()
{
	return (size == 0);
}

template <class T>
bool LinkedList<T>::remove(T d)
{
	ListNode<T> *node = head;
	while (node != NULL)
	{
		if (node->data == d)
		{

			if (node == head)
			{
				removeFront();
				return true;


			}
			else if (node == back)
			{
				removeBack();
				return true;


			}
			else
			{
				node->prev->next = node->next;
				node->next->prev = node->prev;
				delete node;
				--size;
				return true;
			}
		}

		node = node->next;
	}

	return false;
}
