#include "Trie.h"
#include <cctype>

Trie::Trie()
{
  raiz = new TrieNodo();
}

Trie::~Trie()
{
  delete raiz;
}

int Trie::indiceDe(char c)
{
  c = tolower(c);

  if (c == ' ')
  {
    return 26;
  }
  if (c >= 'a' && c <= 'z')
  {
    return c - 'a';
  }

  return -1; // caracter no valido 
}

string Trie::aMinuscula(string texto)
{
  string resultado = "";

  for (int i = 0; i < (int)texto.size(); i++)
  {
    resultado += tolower(texto[i]);
  }

  return resultado;
}

void Trie::insertarSufijo(string sufijo, Cancion *c)
{
  TrieNodo *actual = raiz;

  for (int i = 0; i < (int)sufijo.size(); i++)
  {
    int idx = indiceDe(sufijo[i]);

    if (idx == -1)
    {
      continue; // ignorar caracteres invalidos 
    }

    if (actual->hijos[idx] == nullptr)
    {
      actual->hijos[idx] = new TrieNodo();
    }

    actual = actual->hijos[idx];
    actual->esFinDePalabra = true;
    actual->canciones->append(c);
  }
}

void Trie::insertarCancion(Cancion *c)
{
  string titulo = aMinuscula(c->getTitulo());
  string autor = aMinuscula(c->getAutor());

  // insertamos todos los sufijos del titulo.
  // ej: "hola" genera "hola", "ola", "la", "a"
  
  for (int i = 0; i < (int)titulo.size(); i++)
  {
    insertarSufijo(titulo.substr(i), c);
  }

  // lo mismo para el nombre del autor
  for (int i = 0; i < (int)autor.size(); i++)
  {
    insertarSufijo(autor.substr(i), c);
  }
}

LinkedList<Cancion *> *Trie::buscar(string texto)
{
  LinkedList<Cancion *> *resultado = new LinkedList<Cancion *>();

  string textoBuscado = aMinuscula(texto);
  TrieNodo *actual = raiz;

  // recorrer trie
  for (int i = 0; i < (int)textoBuscado.size(); i++)
  {
    int idx = indiceDe(textoBuscado[i]);

    if (idx == -1 || actual->hijos[idx] == nullptr)
    {
      return resultado; // no hay coincidencias
    }

    actual = actual->hijos[idx];
  }

  // llegamos al nodo que representa el texto q estamos buscando
  for (int i = 0; i < actual->canciones->lentejas(); i++)
  {
    Cancion *candidata = actual->canciones->get(i);
    bool yaEsta = false;

    for (int j = 0; j < resultado->lentejas(); j++)
    {
      if (resultado->get(j) == candidata)
      {
        yaEsta = true;
        break;
      }
    }

    if (!yaEsta)
    {
      resultado->append(candidata);
    }
  }

  return resultado;
}
