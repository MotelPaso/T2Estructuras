#include "Heap.h"

template <typename T>
void Heap<T>::heapify(int indice, int heapSize)
{
  int largest = indice;
  int izq = 2 * indice + 1;
  int der = 2 * indice + 2;

  if (izq < heapSize && this->list[izq]->getData()->getCantReproducciones() < this->list[largest]->getData()->getCantReproducciones())
    largest = izq;

  if (der < heapSize && this->list[der]->getData()->getCantReproducciones() < this->list[largest]->getData()->getCantReproducciones())
    largest = der;

  if (largest != indice)
  {
    swap(this->list[indice], this->list[largest]);
    heapify(largest, heapSize);
  }
}

template <typename T>
void Heap<T>::cancionSort()
{
  int size = this->list.size();

  for (int i = size / 2 - 1; i >= 0; i--)
  {
    heapify(i, size);
  }

  for (int i = size - 1; i > 0; i--)
  {
    swap(this->list[0], this->list[i]);
    heapify(0, i);
  }
}
template <typename T>
void Heap<T>::artistaSort()
{
  return;
}