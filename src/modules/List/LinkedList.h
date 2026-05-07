#pragma once
#include "../Node.h"
#include <string>

template <typename T>
class LinkedList
{
private:
  Node<T> *head;
  int size = 0;

public:
  LinkedList<T>() : head(nullptr){};
  ~LinkedList();
  int lentejas();
  void append(T data);
  T get(int index);
  bool isEmpty();
  std::string mostrar();
  void removeAt(int index);
};

#include "LinkedList.cpp"