#ifndef LISTASENLAZADAS_H_INCLUDED
#define LISTASENLAZADAS_H_INCLUDED

#include <raylib.h>
#include <raymath.h>

typedef struct Nodo {
  Vector2 valor = Vector2Zero();
  Nodo *siguiente = nullptr;
  Nodo(Vector2 valor) { this->valor = valor; }
} Nodo;

class ListaEnlazada {
  Nodo *primero = nullptr;
  Nodo *ultimo = nullptr;
  int tamanio = 0;

public:
  void pushFront(Nodo *nuevo) {
    if (primero == nullptr) {
      primero = nuevo;
      ultimo = nuevo;
    } else {
      nuevo->siguiente = primero;
      primero = nuevo;
    }
    tamanio++;
  }
  void pushBack(Nodo *nuevo){
    if(primero == nullptr){
      primero = nuevo;
      ultimo = nuevo;
    }else{
      ultimo->siguiente = nuevo;
      ultimo = nuevo;
    }
    tamanio++;
  }
  int get_tamanio(){
    return tamanio;
  }
  Nodo *peek() { return primero; }

  void popBack() {
    if (primero != nullptr) {
      if (primero->siguiente == nullptr) {
        delete primero;
        primero = nullptr;
        ultimo = nullptr;
      } else {
Nodo *actual = primero;
        while (actual->siguiente->siguiente != nullptr) {
          actual = actual->siguiente;
        }
        delete actual->siguiente;
        actual->siguiente = nullptr;
        ultimo = actual;
      }
      tamanio--;
    }
  }
};

#endif  //LISTASENLAZADAS_H_INCLUDED
