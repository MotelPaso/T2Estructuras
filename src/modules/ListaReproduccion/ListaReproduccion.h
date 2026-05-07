#pragma once

#include <string>
#include "../Cancion/Cancion.h"

class DNodo
{
public:
  Cancion *cancion;
  DNodo *next;
  DNodo *prev;
  DNodo(Cancion *c) : next(nullptr), prev(nullptr), cancion(c) {};

  ~DNodo() {};
};

class ListaReproduccion
{

  DNodo *head;
  DNodo *actual;
  DNodo *end;
  std::string tipoRepeticion;
  bool reproduciendo = false;
  bool aleatorio = false;
  int size = 0;
  // Esta clase funciona similar a una lista enlazada, pero con enlace doble
  // para poder avanzar y retroceder.
public:
  ListaReproduccion() : head(nullptr), actual(nullptr), end(nullptr), tipoRepeticion("R0") {};
  ~ListaReproduccion();
  // Agrega una cancion al final de la lista
  void append(Cancion *c);
  // Quita la ultima cancion de la lista
  void remove();
  // Activa o desactiva el modo aleatorio.
  void activarAleatorio();
  // Cambia la forma de repetir y devuelve el tipo de repeticion
  // R0 -> no se repite
  // R1 -> se repite uno
  // RA -> se repite todo
  std::string repetir(std::string r);
  std::string getEstadoActual();
  // Cambia el estado de la primera cancion a sonando.
  void togglePlayStop();
  // Avanza una cancion en la lista
  void avanzar();
  // Retrocede una cancion en la lista
  void retroceder();
  void clear();
  std::string mostrarListaActual();
  void saltarA(int posicion);
  int lentejas();
  bool estaReproduciendo();
  bool esAleatorio();
  string getTipoRepeticion();
  int getIndiceActual();
  void setReproduciendo(bool estado);
  void setAleatorio(bool estado);
  void moverAIndice(int indice);
  void eliminarCancion(Cancion *c);

};

#include "ListaReproduccion.cpp"