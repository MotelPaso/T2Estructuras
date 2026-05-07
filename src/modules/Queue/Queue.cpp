#include "Queue.h"

template <typename T>
void Queue<T>::push(T data)
{
  Node<T> *temp = new Node<T>(data);
  this->size++;
  if (this->isEmpty())
  {
    this->first = temp;
    this->last = temp;
    return;
  }
    last->setNext(temp);  
    last = temp;
  return;
}
template <typename T>
void Queue<T>::pop()
{
    if (this->isEmpty())
  {
    return;
  }

  Node<T> *temp = first->getNext();  
  delete first;
  first = temp;
  this->size--;

    if (this->size == 0)
  {
    last = nullptr;
  }

  return;
}
template <typename T>
T *Queue<T>::front()
{
  if (this->isEmpty())
{
    return nullptr;
}

return this->first->getData();
}

template <typename T>
bool Queue<T>::isEmpty()
{
  return this->size == 0;
}

template <typename T>
int Queue<T>::lentejas()
{
  return this->size;
};