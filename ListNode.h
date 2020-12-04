/*
Daniel Naryshev
2327209
dnaryshev@chapman.edu

Eshaan Vora
2318955
evora@chapman.edu

Assignment 5 - Student DB
*/
#include <iostream>

using namespace std;

template <class T>
class ListNode
{
	public:
		ListNode();
		~ListNode();
		ListNode(T d);

		T data;
		ListNode *prev;
		ListNode *next;
};

template <class T>
ListNode<T>::ListNode()
{
	prev = NULL;
	next = NULL;
}

template <class T>
ListNode<T>::~ListNode()
{

}

template <class T>
ListNode<T>::ListNode(T d)
{
	data = d;
	prev = NULL;
	next = NULL;
}
