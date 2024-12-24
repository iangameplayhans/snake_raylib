#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED
#include <raylib.h>

class Score {
  int points;
  int fontSize;
  Vector2 position;
  Color color;

public:
  Score(Vector2 position, int points, int fontSize, Color color) {
    this->position = position;
    this->points = points;
    this->color = color;
    this->fontSize = fontSize;
  }

  ~Score() {}
  void set_position(Vector2 position){
    this->position = position;
  }
  int get_points() { return points; }
  void set_points(int points) { this->points = points; }
  void AddPoints(int points) { this->points += points; }
  void Draw() {
    DrawText(TextFormat("SCORE:%08i", points), position.x, position.y, fontSize,
             color);
  }
};
#endif // SCORE_H_INCLUDED
