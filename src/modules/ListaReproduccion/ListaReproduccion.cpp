#include "ListaReproduccion.h"
#include "../Cancion/Cancion.h"
#include <cstdlib>
#include <ctime>

ListaReproduccion::~ListaReproduccion()
{
  while (head != nullptr)
  {
    DNodo *temp = head;
    head = head->next;
    delete temp;
  }
}
std::string ListaReproduccion::mostrarListaActual()
{
  if (this->actual == nullptr)
  {
    return "Vacía\n";
  }

  std::string datos = "";
  DNodo *temp = this->actual->next;
  int contador = 1;

  if (temp == nullptr)
  {
    return "Vacía\n";
  }

  while (temp != nullptr)
  {
    datos += std::to_string(contador) + ". ";
    datos += temp->cancion->mostrar() + "\n";
    temp = temp->next;
    contador++;
  }

  return datos;
}

void ListaReproduccion::saltarA(int posicion)
{
  if (posicion <= 0 || actual == nullptr || actual->next == nullptr)
  {
    return;
  }

  DNodo *objetivo = actual->next;
  int contador = 1;

  while (objetivo != nullptr && contador < posicion)
  {
    objetivo = objetivo->next;
    contador++;
  }

  if (objetivo == nullptr)
  {
    return;
  }

  DNodo *temp = actual->next;

  while (temp != objetivo)
  {
    DNodo *eliminar = temp;
    temp = temp->next;
    delete eliminar;
    size--;
  }

  actual->next = objetivo;
  objetivo->prev = actual;

  actual = objetivo;
}

void ListaReproduccion::append(Cancion *c)
{
  DNodo *n = new DNodo(c);
  this->size++;
  if (this->head == nullptr)
  {
    this->head = n;
    this->actual = n;
    this->end = n;
    return;
  }
  end->next = n;
  n->prev = end;
  end = n;
  return;
};

void ListaReproduccion::remove()
{
  if (this->size == 0)
  {
    return;
  }
  else if (this->size == 1)
  {
    delete end;
    end = nullptr;
    head = end;
    actual = end;
    this->size--;
    return;
  }
  DNodo *temp = end->prev;
  temp->next = nullptr;
  delete end;
  end = temp;
  this->size--;
  return;
};

bool ListaReproduccion::estaReproduciendo()
{
  if (this->actual != nullptr)
  {
    this->actual->cancion->agregarReproduccion(); // sumar uno a la wea
  }
  return this->reproduciendo;
}
bool ListaReproduccion::esAleatorio()
{
  return this->aleatorio;
}
string ListaReproduccion::getTipoRepeticion()
{
  return this->tipoRepeticion;
}
int ListaReproduccion::getIndiceActual()
{
  int index = 0;
  DNodo *temp = head;

  while (temp != nullptr && temp != actual)
  {
    temp = temp->next;
    index++;
  }

  return index;
}

void ListaReproduccion::activarAleatorio()
{
  if (this->size <= 2 || this->actual == nullptr || this->actual->next == nullptr)
  {
    this->aleatorio = !this->aleatorio;
    return;
  }

  if (!this->aleatorio)
  {
    this->aleatorio = true;

    srand(time(nullptr));

    for (DNodo *i = this->actual->next; i != nullptr; i = i->next)
    {
      DNodo *randomNodo = this->actual->next;
      int pasos = rand() % (this->size - 1);

      for (int j = 0; j < pasos && randomNodo->next != nullptr; j++)
      {
        randomNodo = randomNodo->next;
      }

      Cancion *temp = i->cancion;
      i->cancion = randomNodo->cancion;
      randomNodo->cancion = temp;
    }
  }
  else
  {
    this->aleatorio = false;
  }
}
std::string ListaReproduccion::repetir(std::string r)
{
  if (r == "R0" || r == "R1" || r == "RA")
  {
    this->tipoRepeticion = r;
    return this->tipoRepeticion;
  }
  else
  {
    return "Tipo invalido...";
  }
};

std::string ListaReproduccion::getEstadoActual()
{
  if (this->size == 0)
  {
    return "Reproducción Detenida";
  }
  string datos = "";
  if (reproduciendo)
  {
    datos += "Reproduciendo ";
  }
  else
  {
    datos += "En pausa ";
  }
  if (aleatorio || tipoRepeticion != "R0")
  {
    datos += "(";

    if (aleatorio)
      datos += "S";

    if (tipoRepeticion != "R0")
    {
      if (aleatorio)
        datos += "-";

      datos += tipoRepeticion;
    }

    datos += "): ";
  }
  else
  {
    datos += ": ";
  }
  datos += " " + this->actual->cancion->mostrarEstado();
  return datos;
}
void ListaReproduccion::setReproduciendo(bool estado)
{
  this->reproduciendo = estado;
}
void ListaReproduccion::setAleatorio(bool estado)
{
  this->aleatorio = estado;
}
void ListaReproduccion::moverAIndice(int indice)
{
  if (indice < 0 || head == nullptr)
  {
    return;
  }

  DNodo *temp = head;
  int contador = 0;

  while (temp != nullptr && contador < indice)
  {
    temp = temp->next;
    contador++;
  }
  if (temp != nullptr)
  {
    actual = temp;
  }
}

void ListaReproduccion::togglePlayStop()
{
  this->reproduciendo = !this->reproduciendo;
}
void ListaReproduccion::avanzar()
{
  if (actual == nullptr)
  {
    return;
  }
  if (tipoRepeticion == "R1")
  {
    return;
  }
  if (actual->next != nullptr)
  {
    actual = actual->next;
    return;
  }
  if (tipoRepeticion == "RA")
  {
    actual = head;

    if (aleatorio)
    {
      activarAleatorio();
    }

    return;
  }
}
void ListaReproduccion::retroceder()
{
  if (actual == nullptr)
  {
    return;
  }
  if (tipoRepeticion == "R1")
  {
    return;
  }
  if (actual->prev != nullptr)
  {
    actual = actual->prev;
    return;
  }
  if (tipoRepeticion == "RA")
  {
    actual = end;
    return;
  }
}
void ListaReproduccion::clear()
{
  while (head != nullptr)
  {
    DNodo *temp = head;
    head = head->next;
    delete temp;
  }

  head = nullptr;
  actual = nullptr;
  end = nullptr;
  size = 0;
}
int ListaReproduccion::lentejas()
{
  return this->size;
}

void ListaReproduccion::eliminarCancion(Cancion *c)
{
  DNodo *temp = head;

  while (temp != nullptr)
  {
    DNodo *siguiente = temp->next;

    if (temp->cancion == c)
    {
      if (temp == head)
      {
        head = temp->next;
      }

      if (temp == end)
      {
        end = temp->prev;
      }

      if (temp == actual)
      {
        actual = temp->next;

        if (actual == nullptr)
        {
          actual = temp->prev;
        }
      }

      if (temp->prev != nullptr)
      {
        temp->prev->next = temp->next;
      }

      if (temp->next != nullptr)
      {
        temp->next->prev = temp->prev;
      }

      delete temp;
      size--;
    }

    temp = siguiente;
  }

  if (size == 0)
  {
    head = nullptr;
    actual = nullptr;
    end = nullptr;
    reproduciendo = false;
  }
}