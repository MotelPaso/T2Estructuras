#pragma once
#include "../ListaReproduccion/ListaReproduccion.h"
#include "../List/LinkedList.h"
#include "../Node.h"

#include <string>

using namespace std;

// para acumular las reproducciones totales por artista.
// Se usa solo dentro del Heap para el ranking de artistas, no se guarda

class ArtistaStat
{
public:
  string nombreArtista;
  int totalReproducciones;
  LinkedList<Cancion *> *cancionesDelArtista;

  ArtistaStat()
  {
    nombreArtista = "";
    totalReproducciones = 0;
    cancionesDelArtista = new LinkedList<Cancion *>();
  }
};

template <typename T>
class Heap
{
  // max heap
 
  Node<T> **list;
  int cantidad;
  int capacidad;

  // arreglo de estadisticas por artista, usado solo para el ranking de artistas
  ArtistaStat *artistas;
  int cantidadArtistas;

private:
  void heapify(int indice, int heapSize);
  void agrandarSiEsNecesario();

public:
  Heap(LinkedList<T> *canciones)
  {
    cantidad = canciones->lentejas();
    capacidad = cantidad > 0 ? cantidad : 1;
    list = new Node<T> *[capacidad];

    for (int i = 0; i < cantidad; i++)
    {
      list[i] = canciones->getPunteroAt(i);
    }

    artistas = nullptr;
    cantidadArtistas = 0;
  };

  ~Heap()
  {
    delete[] list;

    if (artistas != nullptr)
    {
      for (int i = 0; i < cantidadArtistas; i++)
      {
        delete artistas[i].cancionesDelArtista;
      }
      delete[] artistas;
    }
  }

  void cancionSort();
  void artistaSort();

  LinkedList<Cancion *> *getCancionesDeArtista(int posicion);

  Cancion *getCancionEnPosicion(int posicion);

  string mostrarTop(char s);
};

#include "Heap.cpp"
