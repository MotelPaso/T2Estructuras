#pragma once
#include <string>
using namespace std;

class Cancion
{
private:
  int id;
  string titulo;
  string autor;
  string album;
  int year;
  int duracion;
  string filePath;
  bool sonando = false;
  // cantReproducciones
  int cantReproducciones = 0;

public:
  Cancion(int id, string titulo, string autor, string album, int year, int duracion, string filePath, int cantReproducciones)
  {
    this->id = id;
    this->titulo = titulo;
    this->autor = autor;
    this->album = album;
    this->year = year;
    this->duracion = duracion;
    this->filePath = filePath;
    this->cantReproducciones = cantReproducciones;
  };
  int getId() const { return id; }
  string getTitulo() const { return titulo; }
  string getAutor() const { return autor; }
  string getAlbum() const { return album; }
  int getYear() const { return year; }
  int getDuracion() const { return duracion; }
  string getFilePath() const { return filePath; }
  int getCantReproducciones() const { return cantReproducciones; }

  void agregarReproduccion()
  {
    this->cantReproducciones += 1;
  }

  ~Cancion() {};
  string mostrar() const
  {
    return titulo + " - " + autor;
  }
  string mostrarEstado()
  {
    return titulo + "\nArtista: " + autor + "\nAlbum: " + album + "\n";
  }
};