#include "Heap.h"
#include <algorithm> // std::swap (funcion basica, no es un contenedor STL)

template <typename T>
void Heap<T>::agrandarSiEsNecesario()
{
  if (cantidad < capacidad)
  {
    return;
  }

  int nuevaCapacidad = capacidad * 2;
  Node<T> **nuevoList = new Node<T> *[nuevaCapacidad];

  for (int i = 0; i < cantidad; i++)
  {
    nuevoList[i] = list[i];
  }

  delete[] list;
  list = nuevoList;
  capacidad = nuevaCapacidad;
}

template <typename T>
void Heap<T>::heapify(int indice, int heapSize)
{
  int largest = indice;
  int izq = 2 * indice + 1;
  int der = 2 * indice + 2;

  auto mayorQue = [](Cancion *a, Cancion *b) -> bool
  {
    if (a->getCantReproducciones() != b->getCantReproducciones())
    {
      return a->getCantReproducciones() > b->getCantReproducciones();
    }
    if (a->getTitulo() != b->getTitulo())
    {
      return a->getTitulo() < b->getTitulo(); // alfabetico: menor va primero
    }
    return a->getAutor() < b->getAutor();
  };

  if (izq < heapSize && mayorQue(this->list[izq]->getData(), this->list[largest]->getData()))
    largest = izq;

  if (der < heapSize && mayorQue(this->list[der]->getData(), this->list[largest]->getData()))
    largest = der;

  if (largest != indice)
  {
    std::swap(this->list[indice], this->list[largest]);
    heapify(largest, heapSize);
  }
}

template <typename T>
void Heap<T>::cancionSort()
{
  int size = this->cantidad;

  for (int i = size / 2 - 1; i >= 0; i--)
  {
    heapify(i, size);
  }

  for (int i = size - 1; i > 0; i--)
  {
    std::swap(this->list[0], this->list[i]);
    heapify(0, i);
  }
}

template <typename T>
void Heap<T>::artistaSort()
{
  // agrupar canciones por nombre de artista, acumulando
  //    el total de reproducciones
  if (artistas != nullptr)
  {
    for (int i = 0; i < cantidadArtistas; i++)
    {
      delete artistas[i].cancionesDelArtista;
    }
    delete[] artistas;
  }

  int capacidadArtistas = cantidad > 0 ? cantidad : 1;
  artistas = new ArtistaStat[capacidadArtistas];
  cantidadArtistas = 0;

  for (int i = 0; i < cantidad; i++)
  {
    Cancion *c = list[i]->getData();
    string nombreArtista = c->getAutor();

    int posicion = -1;
    for (int j = 0; j < cantidadArtistas; j++)
    {
      if (artistas[j].nombreArtista == nombreArtista)
      {
        posicion = j;
        break;
      }
    }

    if (posicion == -1)
    {
      artistas[cantidadArtistas].nombreArtista = nombreArtista;
      artistas[cantidadArtistas].totalReproducciones = c->getCantReproducciones();
      artistas[cantidadArtistas].cancionesDelArtista->append(c);
      cantidadArtistas++;
    }
    else
    {
      artistas[posicion].totalReproducciones += c->getCantReproducciones();
      artistas[posicion].cancionesDelArtista->append(c);
    }
  }

  // ordenar el arreglo de artistas por total de reproducciones
  
  for (int i = 0; i < cantidadArtistas - 1; i++)
  {
    int mejorIndice = i;

    for (int j = i + 1; j < cantidadArtistas; j++)
    {
      bool jEsMejor;

      if (artistas[j].totalReproducciones != artistas[mejorIndice].totalReproducciones)
      {
        jEsMejor = artistas[j].totalReproducciones > artistas[mejorIndice].totalReproducciones;
      }
      else
      {
        jEsMejor = artistas[j].nombreArtista < artistas[mejorIndice].nombreArtista;
      }

      if (jEsMejor)
      {
        mejorIndice = j;
      }
    }

    if (mejorIndice != i)
    {
      ArtistaStat temp = artistas[i];
      artistas[i] = artistas[mejorIndice];
      artistas[mejorIndice] = temp;
    }
  }
}

template <typename T>
LinkedList<Cancion *> *Heap<T>::getCancionesDeArtista(int posicion)
{
  if (artistas == nullptr || posicion < 1 || posicion > cantidadArtistas)
  {
    return nullptr;
  }

  return artistas[posicion - 1].cancionesDelArtista;
}

template <typename T>
Cancion *Heap<T>::getCancionEnPosicion(int posicion)
{
  if (posicion < 1 || posicion > cantidad)
  {
    return nullptr;
  }

  // mostrarTop('C') muestra la posicion 1 como list[cantidad - 1],
  // la posicion 2 como list[cantidad - 2], etc. 
  return list[cantidad - posicion]->getData();
}

template <typename T>
string Heap<T>::mostrarTop(char s)
{
  int limit;
  string salida = "Ranking TOP ";

  if (s == 'C')
  {
    this->cancionSort();
    limit = cantidad > 10 ? 10 : cantidad;
    salida += to_string(limit) + " Canciones más escuchadas:\n";

    // cancionSort() usa heapsort con max-heap, lo que deja el arreglo
    
    for (int i = 0; i < limit; i++)
    {
      Cancion *c = list[cantidad - 1 - i]->getData();
      salida += to_string(i + 1) + ". [" + to_string(c->getCantReproducciones()) + "] ";
      salida += c->getTitulo() + " - " + c->getAutor() + "\n";
    }
  }
  else if (s == 'A')
  {
    this->artistaSort();
    limit = cantidadArtistas > 10 ? 10 : cantidadArtistas;
    salida += to_string(limit) + " Artistas más escuchados:\n";

    for (int i = 0; i < limit; i++)
    {
      salida += to_string(i + 1) + ". [" + to_string(artistas[i].totalReproducciones) + "] ";
      salida += artistas[i].nombreArtista + "\n";
    }
  }

  return salida;
}
