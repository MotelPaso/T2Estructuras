#pragma once
template <typename T>
class Node
{
private:
  T data;
  Node<T> *next;

public:
  Node(T data) : data(data), next(nullptr) {}

  T getData()
  {
    return data;
  }
  Node<T> *getNext()
  {
    return next;
  }
  void setData(T data)
  {
    this->data = data;
  }
  void setNext(Node<T> *next)
  {
    this->next = next;
  }
  bool hasNext()
  {
    return this->next != nullptr;
  }
};