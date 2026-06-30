#pragma once

#include <string>
#include "../Cancion/Cancion.h"
#include "../List/LinkedList.h"

using namespace std;

// cada nodo del Trie guarda hasta 27 hijos posibles (26 letras y el espacio"
// y una lista de canciones cuyo titulo o autor contiene la cadena formada
// hasta este nodo (cuando esFinDePalabra es true).
class TrieNodo
{
public:
  TrieNodo *hijos[27];
  bool esFinDePalabra;
  LinkedList<Cancion *> *canciones;

  TrieNodo()
  {
    esFinDePalabra = false;
    canciones = new LinkedList<Cancion *>();
    for (int i = 0; i < 27; i++)
    {
      hijos[i] = nullptr;
    }
  }

  ~TrieNodo()
  {
    delete canciones;
    for (int i = 0; i < 27; i++)
    {
      if (hijos[i] != nullptr)
      {
        delete hijos[i];
      }
    }
  }
};

class Trie
{
private:
  TrieNodo *raiz;

  int indiceDe(char c);

  string aMinuscula(string texto);

  void insertarSufijo(string sufijo, Cancion *c);

public:
  Trie();
  ~Trie();

  // inserta todos los sufijos del titulo y del autor de la cancion
  void insertarCancion(Cancion *c);

  // busca un texto en el trie y hace return con las canciones que lo contienen
  LinkedList<Cancion *> *buscar(string texto);
};

#include "Trie.cpp"
