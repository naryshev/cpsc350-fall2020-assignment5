/*
Daniel Naryshev
2327209
dnaryshev@chapman.edu

Eshaan Vora
2318955
evora@chapman.edu

Assignment 5 - Student DB
*/
#include "TreeNode.h"
#include "Faculty.h"
#include "Student.h"
#include <fstream>

using namespace std;

template <class T>
class BST
{
	private:

	public:
		BST();
		virtual ~BST();

		void insert(T val);
		bool contains(T val);
		void printNode(T val);
		T find(T val);
		bool isEmpty();

		T* getMax();
		T* getMin();
		TreeNode<T>* getSuccessor(TreeNode<T> *d); // used for deletion
		bool deleteNode(T k);
		void recursivePrint(TreeNode<T> *node);
		void printTree();
		void recursiveSerialize(ofstream &o, TreeNode<T> *node);
		void writeToFile(string fileName);
		void loadFromFile(string fileName);

	protected:
		TreeNode<T> *root;
};

class FacultyTable : public BST<Faculty>
{
	public:
		void recRemoveStudentId(TreeNode<Faculty> *node, bool &abortCmd, int id)
		{
			if (!abortCmd)
			{
				if (node == NULL) return;
				recursivePrint(node->left);
				// If faculty tree contains id, prompt the user then abort
				if (node->key.containsAdviseeID(id))
				{
					abortCmd = true;
					cout << "ERROR: Faculty member has advisee with ID " << id << endl;
					cout << "Remove any conflicting advisee IDs before removing a student" << endl;
				}
				recursivePrint(node->right);
			}
			else
				return;
		}

		bool removeAdviseeID(Faculty val, int adviseeId)
		{
			if (root == NULL)
				return false;
			else
			{
				TreeNode<Faculty> *curr = root; //start at the root
				while (curr->key != val)
				{
					if (val < curr->key)
						curr = curr->left;
					else
						curr = curr->right;
					if (curr == NULL)
						return false; //ID not found
				}
				curr->key.removeAdviseeID(adviseeId);
			}
		}

		//returns false if command was not aborted
		bool removeStudentId(int id)
		{
			bool abortCmd = false;
			recRemoveStudentId(root, abortCmd, id);
			return abortCmd;
		}

		bool replaceStudentId(Faculty oldVal, Faculty newVal, int studId)
		{
			if (root == NULL)
				return false;
			else
			{
				TreeNode<Faculty> *curr = root; //start at the root
				while (curr->key != oldVal)
				{
					if (oldVal < curr->key)
						curr = curr->left;
					else
						curr = curr->right;
					if (curr == NULL)
						return false; //ID not found
				}
				curr->key.removeAdviseeID(studId);
				curr = root; //start at the root
				while (curr->key != newVal)
				{
					if (newVal < curr->key)
						curr = curr->left;
					else
						curr = curr->right;
					if (curr == NULL)
						return false; //ID not found
				}
				curr->key.addAdviseeID(studId);
			}
		}
};

class StudentTable : public BST<Student>
{
	public:
		bool replaceAdvisorId(Student val)
		{
			if (root == NULL)
				return false;
			else
			{
				TreeNode<Student> *curr = root; //start at the root
				while (curr->key != val)
				{
					if (val < curr->key)
						curr = curr->left;
					else
						curr = curr->right;
					if (curr == NULL)
						return false; //ID not found
				}
				curr->key.advisorId = val.advisorId;
				return true;
			}
		}
};

template <class T>
BST<T>::BST()
{
	root = NULL;
}

template <class T>
BST<T>::~BST()
{
	delete root;
}

template <class T>
void BST<T>::insert(T val)
{
	TreeNode<T>* node = new TreeNode<T>(val);
	if (root == NULL)
		root = node;
	else
	{
		TreeNode<T> *curr = root; //start at the root
		TreeNode<T> *parent;
		while (true)
		{
			parent = curr;
			if (val < curr->key)
			{
				curr = curr->left;
				if (curr == NULL)
				{
					parent->left = node;
					break;
				}
			}
			else
			{
				curr = curr->right;
				if (curr == NULL)
				{
					parent->right = node;
					break;
				}
			}
		}
	}
}

template <class T>
bool BST<T>::contains(T val)
{
	if (root == NULL)
		return false;
	else
	{
		TreeNode<T> *curr = root; //start at the root
		while (curr->key != val)
		{
			if (val < curr->key)
				curr = curr->left;
			else
				curr = curr->right;
			if (curr == NULL)
				return false; //value not found
		}
		return true;
	}
}

template <class T>
void BST<T>::printNode(T val)
{
	if (root == NULL)
		cout << "ERROR. Node not found." << endl;
	else
	{
		TreeNode<T> *curr = root; //start at the root
		while (curr->key != val)
		{
			if (val < curr->key)
				curr = curr->left;
			else
				curr = curr->right;
			if (curr == NULL)
				cout << "ERROR. Node not found." << endl;
		}
		cout << curr->key;
	}
}

template <class T>
T BST<T>::find(T val)
{
	if (root == NULL)
		return T();
	else
	{
		TreeNode<T> *curr = root; //start at the root
		while (curr->key != val)
		{
			if (val < curr->key)
				curr = curr->left;
			else
				curr = curr->right;
			if (curr == NULL)
				return T(); //node not found
		}
		return curr->key;
	}
}

template <class T>
bool BST<T>::isEmpty()
{
	return (root == NULL);
}

template <class T>
T* BST<T>::getMax()
{
	TreeNode<T> *curr = root;
	if (root == NULL)
		return NULL;
	while (curr->right != NULL)
	{
		curr = curr->right(); //continues along to the right-most node
	}
	return &(curr->key);
}

template <class T>
T* BST<T>::getMin()
{
	TreeNode<T> *curr = root;
	if (root == NULL)
		return NULL;
	while (curr->left != NULL)
	{
		curr = curr->left(); //continues along to the left-most node
	}
	return &(curr->key);
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d)
{
	TreeNode<T>* sp = d;
	TreeNode<T>* successor = d;
	TreeNode<T>* curr = d->right;
	while (curr != NULL)
	{
		sp = successor;
		successor = curr;
		curr = curr->left;
	}
	if (successor != d->right)
	{
		sp->left = successor->right;
		successor->right = d->right;
	}
	return successor;
}

template <class T>
bool BST<T>::deleteNode(T k)
{
	if (root == NULL) //checks if the tree is empty
		return false;
	TreeNode<T> *curr = root;
	TreeNode<T> *parent = root;
	bool isLeft = true;
	while ((curr->key) != k) //searches for the node to be deleted
	{
		parent = curr;
		if (k<curr->key)
		{
			isLeft = true;
			curr = curr->left;
		}
		else
		{
			isLeft = false;
			curr = curr->right;
		}
		if (curr == NULL) //node not found
			return false;
	}
	if (curr->left == NULL && curr->right == NULL)
	{
		if (curr == root)
			root = NULL;
		else if (isLeft)
			parent->left = NULL;
		else
			parent->right = NULL;
	}
	else if (curr->right == NULL)
	{
		if (curr == root)
			root = curr->left;
		else if (isLeft)
			parent->left = curr->left;
		else
			parent->right = curr->left;
	}
	else if (curr->left == NULL)
	{
		if (curr == root)
			root = curr->right;
		else if
			(isLeft) parent->left = curr->right;
		else
			parent->right = curr->right;
	}
	else
	{
		TreeNode<T> *succ = getSuccessor(curr);
		if (curr == parent)
		{
			curr = parent->left;
			succ->left = curr;
			root = succ;
		}
		else
		{
			if (isLeft)
				parent->left = succ; //checks if node to be deleted is to the left of parent
			else
				parent->right = succ; //checks if node to be deleted is to the right of parent
			succ->left = curr->left; //links successor to curr's left child
		}
	}
}

template <class T>
void BST<T>::recursivePrint(TreeNode<T> *node)
{
	if (node == NULL)
		return;
	recursivePrint(node->left);
	cout << node->key << endl;
	recursivePrint(node->right);
}

template <class T>
void BST<T>::printTree()
{
	recursivePrint(root);
}

template <class T>
void BST<T>::recursiveSerialize(ofstream &o, TreeNode<T> *node)
{
	if (node == NULL)
		return;
	o << node->key.serialize() << "\n";
	recursiveSerialize(o, node->left);
	recursiveSerialize(o, node->right);
}

template <class T>
void BST<T>::writeToFile(string fileName)
{
	ofstream o;
	o.open(fileName.c_str(), ofstream::out | ofstream::trunc);
	recursiveSerialize(o, root);
	o.close();
}

template <class T>
void BST<T>::loadFromFile(string fileName)
{
	ifstream f;
	f.open(fileName.c_str());
	string line;
	while (getline(f, line))
	{
		T node = T(line);
		insert(node);
	}
	f.close();
}
