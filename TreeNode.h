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
class TreeNode
{
	public:
		TreeNode();
		TreeNode(T key);
		virtual ~TreeNode();

		T key;
		TreeNode<T> *left;
		TreeNode<T> *right;
};

template <class T>
TreeNode<T>::TreeNode()
{
	left = NULL;
	right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T k)
{
	left = NULL;
	right = NULL;
	key = k;
}

template <class T>
TreeNode<T>::~TreeNode()
{
	delete left;
	delete right;
}
