#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "listasEnlazadas.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>

class Snake {
  Vector2 direction = Vector2{1, 0};
  float rotation = 0;
  float scale = 20;
  // Color color;
  ListaEnlazada snakeBody;
  Texture2D texture;

public:
  Snake(Vector2 positionHead, int scale, int sizeBody) {
    this->snakeBody.pushBack(new Nodo(positionHead));
    this->scale = scale;
    // this->color = color;
    setBodySize(sizeBody);

    // chargue image snake;
    texture = LoadTexture("./Assets/snake.png");
  }

  ~Snake() { UnloadTexture(texture); };

  void Reset(Vector2 position) {
    snakeBody.peek()->valor = position;
    direction = Vector2{1, 0};
    rotation = 0;
    int tamanio = snakeBody.get_tamanio();
    for (int i = 0; i < tamanio - 1; i++) {
      snakeBody.popBack();
    }
  }

  void setBodySize(int size) {
    for (int i = 0; i < size; i++) {
      incrementBody();
    }
  }
  Nodo *get_Head() { return snakeBody.peek(); }

  void updateDirection() {
    if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) &&
        Vector2Equals(direction, Vector2{0, 1}) == false) {
      direction = Vector2{0, -1};
      rotation = -90;
    } else if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) &&
               Vector2Equals(direction, Vector2{0, -1}) == false) {
      direction = Vector2{0, 1};
      rotation = 90;
    } else if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) &&
               Vector2Equals(direction, Vector2{-1, 0}) == false) {
      direction = Vector2{1, 0};
      rotation = 0;
    } else if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) &&
               Vector2Equals(direction, Vector2{1, 0}) == false) {
      direction = Vector2{-1, 0};
      rotation = 180;
    }
  }

  void incrementBody() {
    snakeBody.pushBack(new Nodo(Vector2Add(
        snakeBody.peek()->valor,
        Vector2{-direction.x * scale, -direction.y * scale})));
  }
  void motion() {
    updateDirection();
    snakeBody.pushFront(new Nodo(Vector2Add(
        snakeBody.peek()->valor,
        Vector2{direction.x * scale, direction.y * scale})));
    snakeBody.popBack();
  }

  int get_tamanio(){
    return snakeBody.get_tamanio();
  }

  void Draw() {
    float sprite = 1.f;
    Nodo *actual = snakeBody.peek();
    while (actual != nullptr) {
      // se dibuja con respecto al eje de rotacion
      DrawTexturePro(
          texture, Rectangle{0, sprite * 40, 40, 40},
          Rectangle{actual->valor.x + 20, actual->valor.y + 20, 40, 40},
          Vector2{20, 20}, rotation, WHITE);

      sprite = 0.f;
      actual = actual->siguiente;
    }
  }
};

#endif // SNAKE_H_INCLUDED
