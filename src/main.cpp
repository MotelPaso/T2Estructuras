#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "modules/List/LinkedList.h"
#include "modules/Cancion/Cancion.h"
#include "modules/ListaReproduccion/ListaReproduccion.h"
#include "modules/Heap/Heap.h"
#include "modules/Trie/Trie.h"
using namespace std;

// global lists
LinkedList<Cancion *> *listadoCanciones = new LinkedList<Cancion *>();
ListaReproduccion *listaReproduccion = new ListaReproduccion();
Trie *trieCanciones = new Trie();
void guardarEstado();


void reconstruirTrie(){
  delete trieCanciones;
  trieCanciones = new Trie();

  for (int i = 0; i < listadoCanciones->lentejas(); i++)
  {
    trieCanciones->insertarCancion(listadoCanciones->get(i));
  }
}

void limpiarPantalla()
{
#ifdef _WIN32
  system("cls"); // si es windows se usa este comando
#else
  system("clear"); // si es linux, este comando.
#endif
}

void mostrarOpciones()
{
  cout << "Opciones:" << endl;
  cout << "W - Reproducir/Pausar" << endl;
  cout << "Q - Pista Anterior" << endl;
  cout << "E - Pista Siguiente" << endl;
  cout << "S - Activar/Desactivar modo aleatorio" << endl;
  cout << "R - Repetición (Desactivado/Repetir una/Repetir todas)" << endl;
  cout << "A - Ver lista de reproducción actual" << endl;
  cout << "L - Listado de canciones" << endl;
  cout << "F - Buscar canciones" << endl;
  cout << "T - TOP 10 Artistas y Canciones" << endl;
  cout << "X - Salir" << endl;
  cout << "Ingrese Opción: ";
};
bool esSeparador(char c)
{
  return c == ',';
}
bool cargarMusica()
{
  fstream arch("../music_source.txt");

  if (!arch)
  {
    return false;
  }

  string linea;

  while (getline(arch, linea))
  {
    string datos[8];
    int i = 0;
    string actual = "";

    for (int j = 0; j < linea.size(); j++)
    {
      if (esSeparador(linea[j]) && i < 7)
      {
        datos[i] = actual;
        i++;
        actual = "";
      }
      else
      {
        actual += linea[j];
      }
    }

    datos[i] = actual;

    if (i < 7)
    {
      continue;
    }

    Cancion *c = new Cancion(
        stoi(datos[0]),
        datos[1],
        datos[2],
        datos[3],
        stoi(datos[4]),
        stoi(datos[5]),
        datos[6],
        stoi(datos[7]));

    listadoCanciones->append(c);
  }

  arch.close();
  return true;
};

bool cargarOpciones()
{
  fstream arch("../status.cfg");

  if (!arch)
  {
    return true;
  }

  int indiceActual;
  int reproduciendo;
  int aleatorio;
  string repeticion;

  arch >> indiceActual;
  arch >> reproduciendo;
  arch >> aleatorio;
  arch >> repeticion;

  if (arch.fail())
  {
    arch.close();
    return false;
  }

  arch.close();

  listaReproduccion->clear();

  for (int i = 0; i < listadoCanciones->lentejas(); i++)
  {
    listaReproduccion->append(listadoCanciones->get(i));
  }

  listaReproduccion->moverAIndice(indiceActual);
  listaReproduccion->setReproduciendo(reproduciendo == 1);
  listaReproduccion->setAleatorio(aleatorio == 1);
  listaReproduccion->repetir(repeticion);

  return true;
}

void mostrarCanciones()
{
  cout << endl;
  cout << "Canciones registradas:" << endl;

  if (listadoCanciones->isEmpty())
  {
    cout << "No hay canciones registradas." << endl;
    return;
  }

  cout << listadoCanciones->mostrar() << endl;
}

void guardarMusicSource()
{
  fstream arch("../music_source.txt", ios::out);

  if (!arch)
  {
    cout << "Error al guardar archivo" << endl;
    return;
  }

  for (int i = 0; i < listadoCanciones->lentejas(); i++)
  {
    Cancion *c = listadoCanciones->get(i);

    arch << c->getId() << ","
         << c->getTitulo() << ","
         << c->getAutor() << ","
         << c->getAlbum() << ","
         << c->getYear() << ","
         << c->getDuracion() << ","
         << c->getFilePath() << ','
         << c->getCantReproducciones();

    if (i < listadoCanciones->lentejas() - 1)
    {
      arch << endl;
    }
  }

  arch.close();
}

void menuCanciones()
{
  string opcionL;

  do
  {
    mostrarCanciones();

    cout << "Opciones:" << endl;
    cout << "R<num> - Reproducir cancion seleccionada" << endl;
    cout << "A<num> - Agregar cancion al final de la lista" << endl;
    cout << "N - Agregar cancion al registro" << endl;
    cout << "D<num> - Eliminar cancion seleccionada" << endl;
    cout << "V - Volver al menu principal" << endl;
    cout << "Ingrese opcion: ";

    cin >> opcionL;

    if (opcionL == "V" || opcionL == "v")
    {
      return;
    }
    else if (opcionL[0] == 'A' || opcionL[0] == 'a')
    {
      if (opcionL.length() > 1)
      {

        int num;

        try
        {
          num = stoi(opcionL.substr(1));
        }
        catch (...)
        {
          cout << "Numero invalido." << endl;
          continue;
        }
        if (num >= 1 && num <= listadoCanciones->lentejas())
        {
          Cancion *c = listadoCanciones->get(num - 1);
          listaReproduccion->append(c);
          guardarEstado();

          cout << c->mostrar() << " agregada a la lista." << endl;
        }
        else
        {
          cout << "Numero invalido." << endl;
        }
      }
      else
      {
        cout << "Debes ingresar un numero. Ej: A3" << endl;
      }
    }
    else if (opcionL[0] == 'R' || opcionL[0] == 'r')
    {
      if (opcionL.length() > 1)
      {
        int num;

        try
        {
          num = stoi(opcionL.substr(1));
        }
        catch (...)
        {
          cout << "Numero invalido." << endl;
          continue;
        }
        if (num >= 1 && num <= listadoCanciones->lentejas())
        {
          Cancion *c = listadoCanciones->get(num - 1);
          listaReproduccion->clear();

          listaReproduccion->append(c);

          for (int i = 0; i < listadoCanciones->lentejas(); i++)
          {
            Cancion *otraCancion = listadoCanciones->get(i);

            if (otraCancion != c)
            {
              listaReproduccion->append(otraCancion);
            }
          }

          listaReproduccion->activarAleatorio();

          listaReproduccion->setReproduciendo(true);

          guardarEstado();

          cout << "Reproduciendo: " << c->mostrar() << endl;
        }
        else
        {

          cout << "Numero invalido." << endl;
        }
      }
      else
      {
        cout << "Debes ingresar un numero." << endl;
      }
    }
    else if (opcionL == "N" || opcionL == "n")
    {
      string titulo, autor, album, ruta;
      int year, duracion;

      cin.ignore(); // limpiar buffer

      cout << "Titulo: ";
      getline(cin, titulo);

      cout << "Autor: ";
      getline(cin, autor);

      cout << "Album: ";
      getline(cin, album);

      cout << "Anio: ";
      cin >> year;

      cout << "Duracion (segundos): ";
      cin >> duracion;

      cin.ignore(); // limpiar buffer otra vez

      cout << "Ruta archivo: ";
      getline(cin, ruta);

      int nuevoId = listadoCanciones->lentejas() + 1;

      Cancion *c = new Cancion(nuevoId, titulo, autor, album, year, duracion, ruta, 0);

      listadoCanciones->append(c);

      cout << "Cancion agregada correctamente." << endl;
      guardarMusicSource();
      guardarEstado();
      reconstruirTrie();
    }
    else if (opcionL[0] == 'D' || opcionL[0] == 'd')
    {

      if (opcionL.length() > 1)
      {
        int num;

        try
        {
          num = stoi(opcionL.substr(1));
        }
        catch (...)
        {
          cout << "Numero invalido." << endl;
          continue;
        }
        if (num >= 1 && num <= listadoCanciones->lentejas())
        {
          Cancion *c = listadoCanciones->get(num - 1);
          cout << "Eliminando: " << c->mostrar() << endl;

          listaReproduccion->eliminarCancion(c);
          listadoCanciones->removeAt(num - 1);

          cout << "Cancion eliminada correctamente." << endl;
          guardarMusicSource();
          guardarEstado();
          reconstruirTrie();
        }
        else
        {
          cout << "Numero invalido." << endl;
        }
      }
      else
      {
        cout << "Debes ingresar un numero. Ej: D3" << endl;
      }
    }

    else
    {
      cout << "Opcion no valida o aun no implementada." << endl;
    }

  } while (true);
}

void cleanUp()
{
  delete listaReproduccion;
  delete listadoCanciones;
  delete trieCanciones;
};

void menuListaReproduccion()
{
  string opcionA;

  do
  {
    cout << endl;
    cout << listaReproduccion->getEstadoActual() << endl;
    cout << "Lista de reproduccion actual:" << endl;
    cout << listaReproduccion->mostrarListaActual() << endl;

    cout << "Opciones:" << endl;
    cout << "S<num> - Saltar a la cancion seleccionada" << endl;
    cout << "V - Volver al menu principal" << endl;
    cout << "Ingrese opcion: ";

    cin >> opcionA;

    if (opcionA == "V" || opcionA == "v")
    {
      return;
    }
    else if (opcionA[0] == 'S' || opcionA[0] == 's')
    {
      if (opcionA.length() > 1)
      {

        int num;

        try
        {
          num = stoi(opcionA.substr(1));
        }
        catch (...)
        {
          cout << "Numero invalido." << endl;
          continue;
        }

        listaReproduccion->saltarA(num);
        guardarEstado();
        return;
      }
      else
      {
        cout << "Debes ingresar un numero. Ej: S2" << endl;
      }
    }
    else
    {
      cout << "Opcion invalida." << endl;
    }

  } while (true);
}

void cambiarRepeticion()
{
  static int estado = 0;

  if (estado == 0)
  {
    listaReproduccion->repetir("R1");
    cout << "Repetir una activado" << endl;
  }
  else if (estado == 1)
  {
    listaReproduccion->repetir("RA");
    cout << "Repetir todas activado" << endl;
  }
  else
  {
    listaReproduccion->repetir("R0");
    cout << "Repeticion desactivada" << endl;
  }

  estado = (estado + 1) % 3;
}

void guardarEstado()
{
  fstream arch("../status.cfg", ios::out);

  if (!arch)
  {
    cout << "Error guardando estado" << endl;
    return;
  }

  arch << listaReproduccion->getIndiceActual() << endl;
  arch << listaReproduccion->estaReproduciendo() << endl;
  arch << listaReproduccion->esAleatorio() << endl;
  arch << listaReproduccion->getTipoRepeticion() << endl;

  arch.close();
}

void menuResultadosBusqueda(LinkedList<Cancion *> *resultados, string textoBuscado)
{
  string opcionF;

  do
  {
    cout << endl;
    cout << "Búsqueda de canciones" << endl;
    cout << "Canciones que contienen \"" << textoBuscado << "\":" << endl;

    if (resultados->isEmpty())
    {
      cout << "No se encontraron coincidencias." << endl;
    }
    else
    {
      cout << resultados->mostrar();
    }

    cout << "Opciones:" << endl;
    cout << "R<num> - Reproducir canción seleccionada" << endl;
    cout << "A<num> - Agregar canción seleccionada al final de la lista de reproducción actual" << endl;
    cout << "F - Repetir búsqueda con un texto diferente" << endl;
    cout << "V - Volver al menú principal" << endl;
    cout << "Ingrese Opción: ";

    cin >> opcionF;

    if (opcionF == "V" || opcionF == "v")
    {
      delete resultados;
      return;
    }
    else if (opcionF == "F" || opcionF == "f")
    {
      delete resultados;

      string nuevoTexto;
      cout << "Buscar canciones que contengan: ";
      cin.ignore();
      getline(cin, nuevoTexto);

      if (nuevoTexto.empty())
      {
        return;
      }

      LinkedList<Cancion *> *nuevosResultados = trieCanciones->buscar(nuevoTexto);
      menuResultadosBusqueda(nuevosResultados, nuevoTexto);
      return;
    }
    else if (opcionF[0] == 'A' || opcionF[0] == 'a')
    {
      if (opcionF.length() > 1)
      {
        int num;

        try
        {
          num = stoi(opcionF.substr(1));
        }
        catch (...)
        {
          cout << "Numero invalido." << endl;
          continue;
        }

        if (num >= 1 && num <= resultados->lentejas())
        {
          Cancion *c = resultados->get(num - 1);
          listaReproduccion->append(c);
          guardarEstado();

          cout << c->mostrar() << " agregada a la lista." << endl;
        }
        else
        {
          cout << "Numero invalido." << endl;
        }
      }
      else
      {
        cout << "Debes ingresar un numero. Ej: A1" << endl;
      }
    }
    else if (opcionF[0] == 'R' || opcionF[0] == 'r')
    {
      if (opcionF.length() > 1)
      {
        int num;

        try
        {
          num = stoi(opcionF.substr(1));
        }
        catch (...)
        {
          cout << "Numero invalido." << endl;
          continue;
        }

        if (num >= 1 && num <= resultados->lentejas())
        {
          Cancion *c = resultados->get(num - 1);
          listaReproduccion->clear();

          listaReproduccion->append(c);

          for (int i = 0; i < listadoCanciones->lentejas(); i++)
          {
            Cancion *otraCancion = listadoCanciones->get(i);

            if (otraCancion != c)
            {
              listaReproduccion->append(otraCancion);
            }
          }

          listaReproduccion->activarAleatorio();
          listaReproduccion->setReproduciendo(true);

          guardarEstado();

          cout << "Reproduciendo: " << c->mostrar() << endl;
        }
        else
        {
          cout << "Numero invalido." << endl;
        }
      }
      else
      {
        cout << "Debes ingresar un numero." << endl;
      }
    }
    else
    {
      cout << "Opcion no valida." << endl;
    }

  } while (true);
}

void menuBuscar()
{
  string textoBuscado;

  cout << endl;
  cout << "Búsqueda de canciones" << endl;
  cout << "Buscar canciones que contengan: ";
  cin.ignore();
  getline(cin, textoBuscado);

  if (textoBuscado.empty())
  {
    return;
  }

  LinkedList<Cancion *> *resultados = trieCanciones->buscar(textoBuscado);
  menuResultadosBusqueda(resultados, textoBuscado);
}

void menuCancionesDeArtista(Heap<Cancion *> *heap, int posicionArtista)
{
  string opcion;

  do
  {
    LinkedList<Cancion *> *cancionesArtista = heap->getCancionesDeArtista(posicionArtista);

    cout << endl;
    cout << "Ranking TOP 10 Artistas más escuchados:" << endl;

    if (cancionesArtista == nullptr || cancionesArtista->isEmpty())
    {
      cout << "No hay canciones registradas para este artista." << endl;
    }
    else
    {
      cout << cancionesArtista->mostrar();
    }

    cout << "Opciones:" << endl;
    cout << "R<num> - Reproducir canción seleccionada" << endl;
    cout << "A<num> - Agregar canción seleccionada al final de la lista de reproducción actual" << endl;
    cout << "V – Volver al listado de TOP 10 artistas" << endl;
    cout << "X – Volver al menú principal" << endl;
    cout << "Ingrese Opción: ";

    cin >> opcion;

    if (opcion == "X" || opcion == "x")
    {
      return;
    }
    else if (opcion == "V" || opcion == "v")
    {
      break; // vuelve al listado de artistas (continua el ciclo de afuera)
    }
    else if (cancionesArtista != nullptr && (opcion[0] == 'A' || opcion[0] == 'a'))
    {
      if (opcion.length() > 1)
      {
        int num;

        try
        {
          num = stoi(opcion.substr(1));
        }
        catch (...)
        {
          cout << "Numero invalido." << endl;
          continue;
        }

        if (num >= 1 && num <= cancionesArtista->lentejas())
        {
          Cancion *c = cancionesArtista->get(num - 1);
          listaReproduccion->append(c);
          guardarEstado();

          cout << c->mostrar() << " agregada a la lista." << endl;
        }
        else
        {
          cout << "Numero invalido." << endl;
        }
      }
      else
      {
        cout << "Debes ingresar un numero. Ej: A1" << endl;
      }
    }
    else if (cancionesArtista != nullptr && (opcion[0] == 'R' || opcion[0] == 'r'))
    {
      if (opcion.length() > 1)
      {
        int num;

        try
        {
          num = stoi(opcion.substr(1));
        }
        catch (...)
        {
          cout << "Numero invalido." << endl;
          continue;
        }

        if (num >= 1 && num <= cancionesArtista->lentejas())
        {
          Cancion *c = cancionesArtista->get(num - 1);
          listaReproduccion->clear();
          listaReproduccion->append(c);

          for (int i = 0; i < listadoCanciones->lentejas(); i++)
          {
            Cancion *otraCancion = listadoCanciones->get(i);

            if (otraCancion != c)
            {
              listaReproduccion->append(otraCancion);
            }
          }

          listaReproduccion->activarAleatorio();
          listaReproduccion->setReproduciendo(true);
          guardarEstado();

          cout << "Reproduciendo: " << c->mostrar() << endl;
        }
        else
        {
          cout << "Numero invalido." << endl;
        }
      }
      else
      {
        cout << "Debes ingresar un numero." << endl;
      }
    }
    else
    {
      cout << "Opcion no valida." << endl;
    }

  } while (true);
}

void menuTop()
{
  if (listadoCanciones->isEmpty())
  {
    cout << "No hay canciones registradas." << endl;
    return;
  }

  Heap<Cancion *> *heap = new Heap<Cancion *>(listadoCanciones);
  string opcion;

  cout << "Ranking TOP" << endl;
  cout << "C - Top 10 canciones más escuchadas" << endl;
  cout << "A - Top 10 artistas más escuchados" << endl;
  cout << "X - Salir" << endl;
  cout << "Ingrese Opción: ";
  cin >> opcion;

  while (opcion != "X" && opcion != "x")
  {
    if (opcion == "C" || opcion == "c")
    {
      cout << heap->mostrarTop('C') << endl;
      cout << "Opciones:" << endl;
      cout << "R<num> - Reproducir canción seleccionada" << endl;
      cout << "A<num> - Agregar canción seleccionada al final de la lista de reproducción actual" << endl;
      cout << "A – Top 10 artistas más escuchados" << endl;
      cout << "V – Volver al menú principal" << endl;
      cout << "Ingrese Opción: ";

      cin >> opcion;

      if (opcion == "V" || opcion == "v")
      {
        break;
      }
      else if (opcion[0] == 'R' || opcion[0] == 'r')
      {
        if (opcion.length() > 1)
        {
          int num;

          try
          {
            num = stoi(opcion.substr(1));
          }
          catch (...)
          {
            cout << "Numero invalido." << endl;
            opcion = "C";
            continue;
          }

          Cancion *c = heap->getCancionEnPosicion(num);

          if (c != nullptr)
          {
            listaReproduccion->clear();
            listaReproduccion->append(c);

            for (int i = 0; i < listadoCanciones->lentejas(); i++)
            {
              Cancion *otraCancion = listadoCanciones->get(i);

              if (otraCancion != c)
              {
                listaReproduccion->append(otraCancion);
              }
            }

            listaReproduccion->activarAleatorio();
            listaReproduccion->setReproduciendo(true);
            guardarEstado();

            cout << "Reproduciendo: " << c->mostrar() << endl;
          }
          else
          {
            cout << "Numero invalido." << endl;
          }
        }
        opcion = "C";
        continue;
      }
      else if (opcion[0] == 'A' && opcion.length() > 1)
      {
        int num;

        try
        {
          num = stoi(opcion.substr(1));
        }
        catch (...)
        {
          cout << "Numero invalido." << endl;
          opcion = "C";
          continue;
        }

        Cancion *c = heap->getCancionEnPosicion(num);

        if (c != nullptr)
        {
          listaReproduccion->append(c);
          guardarEstado();
          cout << c->mostrar() << " agregada a la lista." << endl;
        }
        else
        {
          cout << "Numero invalido." << endl;
        }

        opcion = "C";
        continue;
      }
      else if (opcion == "A")
      {
        opcion = "A"; // cae al bloque de abajo en la siguiente iteracion
        continue;
      }
      else
      {
        opcion = "C";
        continue;
      }
    }

    if (opcion == "A" || opcion == "a")
    {
      cout << heap->mostrarTop('A') << endl;
      cout << "Opciones:" << endl;
      cout << "S<num> - Mostrar canciones del artista" << endl;
      cout << "C - Top 10 canciones más escuchadas" << endl;
      cout << "V - Volver al menú principal" << endl;
      cout << "Ingrese Opción: ";

      cin >> opcion;

      if (opcion == "V" || opcion == "v")
      {
        break;
      }
      else if (opcion[0] == 'S' || opcion[0] == 's')
      {
        if (opcion.length() > 1)
        {
          int num;

          try
          {
            num = stoi(opcion.substr(1));
          }
          catch (...)
          {
            cout << "Numero invalido." << endl;
            opcion = "A";
            continue;
          }

          menuCancionesDeArtista(heap, num);
        }

        opcion = "A";
        continue;
      }
      else if (opcion == "C" || opcion == "c")
      {
        continue;
      }
      else
      {
        opcion = "A";
        continue;
      }
    }
  }

  delete heap;
}

int main()
{
  bool musicaCargada = cargarMusica();
  bool optionsCargadas = cargarOpciones();
  reconstruirTrie();
  if (!(musicaCargada && optionsCargadas))
  {
    if (!musicaCargada)
    {
      cout << "Ha habido un problema cargando la musica...";
    }
    if (!optionsCargadas)
    {
      cout << "Ha habido un problema cargando la configuracion...";
    }
    return 0;
  }
  char opcion;
  do
  {
    limpiarPantalla();
    cout << listaReproduccion->getEstadoActual() << endl;
    mostrarOpciones();
    cin >> opcion;
    switch (opcion)
    {
    case 'W':
      listaReproduccion->togglePlayStop();
      guardarEstado();
      break;
    case 'Q':
      listaReproduccion->retroceder();
      guardarEstado();
      break;
    case 'E':
      listaReproduccion->avanzar();
      guardarEstado();
      break;
    case 'S':
      listaReproduccion->activarAleatorio();
      guardarEstado();
      cout << "Modo aleatorio cambiado" << endl;
      break;
    case 'R':
      cambiarRepeticion();
      guardarEstado();
      break;
    case 'A':
      menuListaReproduccion();
      break;
    case 'L':
      menuCanciones();
      break;
    case 'F':
      menuBuscar();
      break;
    case 'T':
      menuTop();
      break;
    case 'X':
      guardarEstado();
      cout << "Adios!" << endl;
      break;
    default:
      cout << "Opcion invalida..." << endl;
      break;
    }
  } while (opcion != 'X');

  cleanUp();
  return 0;
}