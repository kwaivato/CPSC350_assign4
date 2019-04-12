// DoublyList.h
// A node-based doubly-linked list class.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0

#include <iostream>
#include <string>
#include "ListEmpty.cpp"

using namespace std;

#ifndef DoublyList_H
#define DoublyList_H

//Doubly LinkedList Node Interface
template <class E>
class DoublyListNode
{
  public:
    DoublyListNode();
    DoublyListNode(const E e);
    ~DoublyListNode();
    E m_data;
    DoublyListNode<E> *next;
    DoublyListNode<E> *prev;
  private:
};

//Doubly LinkedList Node Implementation
template <class E>
DoublyListNode<E>::DoublyListNode()
{
  next = NULL;
  prev = NULL;
}

template <class E>
DoublyListNode<E>::DoublyListNode(const E e)
{
  m_data = e;
  next = NULL;
  prev = NULL;
}

template <class E>
DoublyListNode<E>::~DoublyListNode()
{

}

//Doubly LinkedList Interface
template <class E>
class DoublyList
{
  public:
    DoublyList();
    ~DoublyList();
    void insertFront(const E e);
    void insertBack(const E e);
    E seeFront() throw (ListEmpty);
    E removeFront() throw (ListEmpty);
    E removeBack() throw (ListEmpty);
    E deletePosition(int pos);
    void printList();
    int find(const E e);
    void remove(const E e);
    bool isEmpty();
    unsigned int getSize();

  private:
    DoublyListNode<E> *m_front;
    DoublyListNode<E> *m_back;
    unsigned int m_size;
};

//Doubly LinkedList Implementation
template <class E>
DoublyList<E>::DoublyList()
{
  m_front = NULL;
  m_back = NULL;
  m_size = 0;
}

template <class E>
DoublyList<E>::~DoublyList()
{
  if (m_front == NULL)
  {
    delete m_front;
  }
  else
  {
    while (m_front->next != NULL)
    {
      DoublyListNode<E> *nextNode = m_front->next;
  		m_front->next = nextNode->next;
  		delete nextNode;
    }
    delete m_front;
  }
}

template <class E>
void DoublyList<E>::insertFront(const E e)
{
  DoublyListNode<E> *node = new DoublyListNode<E>(e);
  if (m_size == 0)
  {
    m_back = node;
  }
  else
  {
    m_front->prev = node;
    node->next = m_front;
  }
  m_front = node;
  ++m_size;
}

template <class E>
void DoublyList<E>::insertBack(const E e)
{
  DoublyListNode<E> *node = new DoublyListNode<E>(e);
  if (m_size == 0)
  {
    m_front = node;
  }
  else
  {
    m_back->next = node;
    node->prev = m_back;
  }
  m_back = node;
  ++m_size;
}

template <class E>
E DoublyList<E>::seeFront() throw (ListEmpty)
{
  if(isEmpty())
  {
    throw ListEmpty("Your list is empty! No elements to remove.");
  }
  return m_front->m_data;
}

template <class E>
E DoublyList<E>::removeFront() throw (ListEmpty)
{
  if(isEmpty())
  {
    throw ListEmpty("Your list is empty! No elements to remove.");
  }
  E& temp = m_front->m_data;
  DoublyListNode<E> *ft = m_front;
  m_front = m_front->next;
  ft->next = NULL;
  delete ft;
  --m_size;
  return temp;
}

template <class E>
E DoublyList<E>::removeBack() throw (ListEmpty)
{
  if(isEmpty())
  {
    throw ListEmpty("Your list is empty! No elements to remove.");
  }
  E& temp = m_back->m_data;
  DoublyListNode<E> *bk = m_back;
  m_back = m_back->prev;
  bk->prev = NULL;
  delete bk;
  --m_size;
  return temp;
}

template <class E>
E DoublyList<E>::deletePosition(int pos)
{
  int idx = 0;
  if (pos > m_size - 1 || pos < 0)
  {
    cout << "Invalid Position!" << endl;
    return NULL;
  }
  else
  {
    DoublyListNode<E> *curr = m_front;
    DoublyListNode<E> *prev = m_front;

    while(idx != pos)
    {
      prev = curr;
      curr = curr->next;
      ++idx;
    }
    prev->next = curr->next;
    curr->next = NULL;
    E& temp = curr->m_data;
    delete curr;
    m_size--;
    return temp;
  }
}

template <class E>
void DoublyList<E>::printList()
{
  DoublyListNode<E> *curr;
  while ((curr->next) != NULL)
  {
    cout << (curr->m_data) << endl;
    curr = curr->next;
  }
}

template <class E>
int DoublyList<E>::find(const E e)
{
  int idx = -1;
  DoublyListNode<E> *curr = m_front;
  while ((curr->m_data != NULL))
  {
    ++idx;
    if (curr->m_data == e)
    {
      break;
    }
    else
    {
      curr = curr->next;
    }
  }

  if(curr == NULL)
  {
    idx = -1;
  }
  return idx;
}

template <class E>
void DoublyList<E>::remove(const E e)
{
  int pos = find(e);
  deletePosition(pos);
}

template <class E>
bool DoublyList<E>::isEmpty()
{
  if (m_front == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <class E>
unsigned int DoublyList<E>::getSize()
{
  return m_size;
}

#endif
