#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED
#include <raylib.h>
#include <raymath.h>
class Food {

  Vector2 position = Vector2Zero();
  int scale = 20;
  int points = 20;
  Texture2D texture;

public:
  Food(Vector2 position, int points, int scale, int textureUse = 1) {
    this->position = position;
    this->scale = scale;
    this->points = points;
    // seleccion de textura
    texture = (textureUse == 0 ? LoadTexture("./Assets/apple.png")
                               : LoadTexture("./Assets/pizza.png"));
  }
  ~Food() { UnloadTexture(texture); };

  Vector2 get_position() { return position; }
  
  void set_position(Vector2 position) { this->position = position; }
  
  int get_points() { return points; }
  
  void Draw() { DrawTextureV(texture, position, WHITE); }
};

#endif // FOOD_H_INCLUDED
