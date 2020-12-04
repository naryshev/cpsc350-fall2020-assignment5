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
#include <string>

using namespace std;

template <class T>
class GenStack
{
  public:
    GenStack(int maxSize); //constructor
    ~GenStack(); //destructor
    int topStack, max;//member variables
    T *userArray;
    T *tempArray;

    bool isFull(); //checks if stack is full
    bool isEmpty(); //checks if stack is empty

    void push(T data); //adds to top of the stack
    T pop(); //removes data from the top of the stack
    T peek(); //shows the top element of the stack

    void expand(); //++size of stack if the stack T is full
};

//constructor
template <class T>
GenStack<T>::GenStack(int maxSize)
{
  userArray = new T[maxSize];
  max = maxSize;
  topStack = -1;
  tempArray = new T[max];
}

//destructor
template <class T>
GenStack<T>::~GenStack()
{
  delete []userArray;
  delete []tempArray;
  cout << "Arrays have been cleared." << endl;
}

template <class T>
bool GenStack<T>::isEmpty()
{
  return (topStack == -1);
}

template <class T>
bool GenStack<T>::isFull()
{
  return (topStack == max - 1);
}

template <class T>
void GenStack<T>::push(T data)
{
  //checks if stack full before adding onto it
  if (isFull() == true)
  {
    expand();
    push(data);
  }
  else
    userArray[++topStack] = data;
}

template <class T>
T GenStack<T>::peek()
{
  if (topStack == -1)
    return 0;
  else
    return userArray[topStack];
}

template <class T>
T GenStack<T>::pop()
{
  //checks if the stack is empty before removing from it
  if (isEmpty() == true)
  {
    cout << "Stack array is empty." << endl;
    return 0;
  }
  else
    return userArray[topStack--];
}

template <class T>
void GenStack<T>::expand()
{
  tempArray = new T[max];
  for (int i = topStack; i > -1; --i)
  {
    tempArray[i] = userArray[i];
  }
  max += 1;
  userArray = new T[max];
  for (int i = topStack; i > -1; --i)
  {
    userArray[i] = tempArray[i];
  }
}
