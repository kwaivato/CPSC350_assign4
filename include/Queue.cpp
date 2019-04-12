// Queue.cpp
// An implementation of the Queue ADT with doubly linked-list functionality.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0

#include "QueueInterface.h"
#include "DoublyList.h"

using namespace std;

#ifndef Queue_CPP
#define Queue_CPP

template <class E>
class Queue : public QueueInterface
{
  public:
    Queue();
    ~Queue();
    void insert(E e);
    E remove();
    E front();
    int getSize();
    bool isEmpty();
  private:
    int m_num_elements;
    DoublyList<E> m_queue;
};

template <class E>
Queue<E>::Queue()
{
  m_num_elements = 0;
}

template <class E>
Queue<E>::~Queue()
{

}

template <class E>
void Queue<E>::insert(E e)
{
  m_queue.insertBack(e);
  m_num_elements++;
}

template <class E>
E Queue<E>::remove()
{
  m_num_elements--;
  return (m_queue.removeFront());
}

template <class E>
E Queue<E>::front()
{
  return (m_queue.seeFront());
}

template <class E>
int Queue<E>::getSize()
{
  return m_num_elements;
}

template <class E>
bool Queue<E>::isEmpty()
{
  return (m_num_elements==0);
}

#endif
