#pragma once
#include "../ListaReproduccion/ListaReproduccion.h"
#include "../List/LinkedList.h"
#include "../Node.h"

#include <vector>
#include <string>

template <typename T>
class Heap
{
  // Esto debe ser un max Heap
  // Para que los mayores esten arriba

  vector<Node<T> *> list;

private:
  void heapify(int indice, int heapSize);

public:
  Heap(LinkedList<T> *canciones)
  {
    for (int i = 0; i < canciones->lentejas(); i++)
    {
      list.push_back(canciones->getPunteroAt(i));
    }
  };
  ~Heap()
  {
    delete list;
  }

  void cancionSort();
  void artistaSort();
  std::string mostrarTop(char s)
  {

    int limit = list.size();
    if (limit > 10)
    {
      limit = 10;
    }
    std::string salida = "Ranking TOP " + std::to_string(limit);
    if (s == 'C')
    {
      salida += " Canciones más escuchadas:\n";
      this->cancionSort();
    }
    if (s == 'A')
    {
      salida += " Artistas más escuchados:\n";
      this->artistaSort();
    }
    for (int i = 0; i < limit; i++)
    {
      salida += std::to_string(i + 1);
      salida += ". [";
      salida += std::to_string(list[i]->getData()->getCantReproducciones());
      salida += "] ";
      if (s == 'C')
        salida += list[i]->getData()->getTitulo();
      salida += list[i]->getData()->getAutor();
      salida += '\n';
    }
    return salida;
  };
};

#include "Heap.cpp"
