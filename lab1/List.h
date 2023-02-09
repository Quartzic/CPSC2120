/*
 * Name: Nathan Goller-Deitsch
 * Date Submitted: 1/23/2023
 * Lab Section: 003
 * Assignment Name: Lab 1: Linked List Based Stacks and Queues
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

// This class represents a linked list of node objects
// Do not modify anything in the class interface
template <class T>
class List
{

private:
  Node<T> *start; // pointer to the first node in this list
  int mySize;     // size (or length) of this list

public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  // Print the name and this list's size and values to stdout
  // This function is already implemented (no need to change it)
  void print(string name)
  {
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> *iterator = start;
    while (iterator != nullptr)
    {
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; // end of class interface (you may modify the code below)

// Implement all of the functions below
// Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List()
{
  // an empty list has no nodes and a size of 0
  start = nullptr;
  mySize = 0;
}

// Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List()
{
  // use current node to track the node we are about to delete
  Node<T> *currentNode = start;

  // use next node to track the next node in the list so we can still access it after deleting currentnode
  Node<T> *nextNode = nullptr;

  // loop through all nodes, deleting them until reaching nullptr
  while (currentNode != nullptr)
  {
    // to delete a node, keep track of the next node (so we can keep walking the list), then delete it with `delete` keyword
    nextNode = currentNode->next;
    delete currentNode;
    currentNode = nextNode;
  }
}

// Return the size of this list
template <class T>
int List<T>::size()
{
  return mySize;
}

// Return true if this list is empty
// Otherwise, return false
template <class T>
bool List<T>::empty()
{
  return mySize == 0;
}

// Create a new node with value, and insert that new node
// into this list at start
template <class T>
void List<T>::insertStart(T value)
{
  // create the new node
  Node<T> *newNode = new Node<T>(value);

  // insert the new node at the start
  newNode->next = start;
  start = newNode;

  // update size;
  mySize++;
}

// Create a new node with value, and insert that new node
// into this list at end
template <class T>
void List<T>::insertEnd(T value)
{
  // variable that will refer to the last element we have seen
  Node<T> *lastElement = start;

  // create the new node
  Node<T> *newNode = new Node<T>(value);
  if (mySize > 0)
  {
    // if the list has elements, walk until we find the last node and insert the new node as its child
    while (lastElement->next != nullptr)
    {
      lastElement = lastElement->next;
    }
    lastElement->next = newNode;
  }
  else
  {
    // otherwise set the list start to the newNode
    start = newNode;
  }

  // update size;
  mySize++;
}

// Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j)
{

  if (j == 0)
  {
    // if we are inserting at the start, run insertStart
    insertStart(value);
  }
  else if (j >= mySize)
  {
    // if we are inserting at the end or past the end, run insertEnd
    insertEnd(value);
  }
  else
  {
    // otherwise insert partially through the list

    // find the element at j where we will perform the insertion, and its parent
    Node<T> *soughtElementParent = start;
    Node<T> *soughtElement = start->next;
    Node<T> *newNode = new Node<T>(value);

    // walk the list until we find the requested element and its parent
    for (int i = 1; i < j; i++)
    {
      soughtElementParent = soughtElementParent->next;
      soughtElement = soughtElementParent->next;
    }

    // insert the newNode before soughtElement
    // newNode should point to soughtElement
    // soughtElementParent node should point to newNode
    // soughtElement should not change its next
    newNode->next = soughtElement;
    soughtElementParent->next = newNode;

    // update size
    mySize++;
  }
}

// Remove node at start
// Make no other changes to list
template <class T>
void List<T>::removeStart()
{
  // Make the linked list point to the second element
  Node<T> *toDelete = start;
  start = start->next;
  delete toDelete;

  // update size
  mySize--;
}

// Remove node at end
// Make no other changes to list
template <class T>
void List<T>::removeEnd()
{
  // walk the list, keeping track of the second to last element (so we can update its pointer when we delete the last element)
  Node<T> *secondToLastElement = start;
  while (secondToLastElement->next->next != nullptr)
  {
    secondToLastElement = secondToLastElement->next;
  }
  Node<T> *lastElement = secondToLastElement->next;

  // update the second to last element, and delete the last element
  secondToLastElement->next = nullptr;
  delete lastElement;

  // update size
  mySize--;
}

// Remove node at position j
// Make no other changes to list
template <class T>
void List<T>::removeAt(int j)
{
  if (j == 0)
  {
    // if we are removing at the start, run removeStart
    removeStart();
  }
  else if (j >= mySize)
  {
    // if we are removing at the end or past the end, run removeEnd
    removeEnd();
  }
  else
  {
    // otherwise remove partially through the list

    // find the element at j which we will remove, and its parent
    Node<T> *soughtElementParent = start;
    Node<T> *soughtElement = start->next;

    // walk the list until we find the requested element and its parent
    for (int i = 1; i < j; i++)
    {
      soughtElementParent = soughtElementParent->next;
      soughtElement = soughtElementParent->next;
    }

    // the parent should skip over the element, and the element will be deleted
    soughtElementParent->next = soughtElement->next;
    delete soughtElement;

    // update size
    mySize--;
  }
}

// Return the value of the first node in the Linked List,
// If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst()
{
  // return default constructed value if list is empty
  if (this->empty())
  {
    return T();
  }

  return start->value;
}

// Return the value of the last node in the Linked List,
// If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast()
{

  // return default constructed value if list is empty
  if (this->empty())
  {
    return T();
  }

  // walk the list until we find the last element and return its value
  Node<T> *lastElement = start;
  while (lastElement->next != nullptr)
  {
    lastElement = lastElement->next;
  }
  return lastElement->value;
}

// Return the value of the node at position j in the Linked List,
// If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j)
{
  // return default constructed value if list is empty
  if (this->empty())
  {
    return T();
  }

  // walk the list until we find the sought element and return its value
  Node<T> *soughtElement = start;
  for (int i = 0; i < j; i++)
  {
    soughtElement = soughtElement->next;
  }
  return soughtElement->value;
}

// Return the position of the (first) node whose value is equal to the key
// Otherwise, return -1
template <class T>
int List<T>::find(T key)
{
  Node<T> *iterator = start;
  int position = 0;
  // walk the list until we find the value that matches the search key
  while (iterator != nullptr)
  {
    if (iterator->value == key)
    {
      // if found, return position
      return position;
    }
    iterator = iterator->next;
    // keep track of the position
    position++;
  }
  // if it wasn't found, return -1
  return -1;
}
