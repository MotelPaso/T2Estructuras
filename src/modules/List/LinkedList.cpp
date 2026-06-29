#include "LinkedList.h"
#include "../Node.h"
#include <string>

template <typename T>
LinkedList<T>::~LinkedList()
{
  while (head != nullptr)
  {
    Node<T> *temp = head;
    head = head->getNext();
    delete temp;
  };
};

template <typename T>
int LinkedList<T>::lentejas()
{
  return this->size;
}

template <typename T>
T LinkedList<T>::get(int index)
{
  if (index < 0 || index >= this->size)
    throw std::out_of_range("Indice fuera de rango");

  Node<T> *temp = this->head;

  for (int i = 0; i < index; i++)
  {
    temp = temp->getNext();
  }

  return temp->getData();
};

template <typename T>
Node<T> *LinkedList<T>::getPunteroAt(int index)
{
  if (index < 0 || index >= this->size)
    throw std::out_of_range("Indice fuera de rango");

  Node<T> *temp = this->head;

  for (int i = 0; i < index; i++)
  {
    temp = temp->getNext();
  }

  return temp;
}

template <typename T>
void LinkedList<T>::removeAt(int index)
{
  if (index < 0 || index >= this->size)
  {
    throw std::out_of_range("Indice fuera de rango");
  }

  Node<T> *temp = head;

  if (index == 0)
  {
    head = head->getNext();
    delete temp;
    size--;
    return;
  }

  Node<T> *prev = nullptr;

  for (int i = 0; i < index; i++)
  {
    prev = temp;
    temp = temp->getNext();
  }

  prev->setNext(temp->getNext());
  delete temp;
  size--;
}

template <typename T>
void LinkedList<T>::append(T data)
{
  Node<T> *newNode = new Node<T>(data);
  if (this->isEmpty())
  {
    head = newNode;
    this->size = 1;
    return;
  }
  Node<T> *temp = head;
  while (temp->hasNext())
  {
    temp = temp->getNext();
  }
  temp->setNext(newNode);
  this->size += 1;
};

template <typename T>
bool LinkedList<T>::isEmpty()
{
  return head == nullptr;
};

template <typename T>
std::string LinkedList<T>::mostrar()
{
  Node<T> *temp = head;
  std::string datos = "";
  int contador = 1;

  while (temp != nullptr)
  {
    datos += std::to_string(contador) + ". ";
    datos += temp->getData()->mostrar() + "\n";
    temp = temp->getNext();
    contador++;
  }

  return datos;
};