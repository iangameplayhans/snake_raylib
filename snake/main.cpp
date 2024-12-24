#include "headers/Food.h"
#include "headers/Score.h"
#include "headers/Snake.h"
#include "headers/listasEnlazadas.h"
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <string>

using namespace std;

// escala de resolucion de pantalla
int SCALE = 40;
// cantidad de celdas por filas y columnas
int CELL_COUNT = 20;
// dificultad
int Dificult = 0;
// string que maneja la escena actual;
string currentScene = "menu";

// Colores personalizados

Color blue = Color{56, 89, 179, 255};
Color green = Color{90, 181, 82, 255};
Color red = Color{107, 38, 67, 255};
Color gray = Color{94, 91, 140, 255};
// Dibujado del menu
void DrawMenu() {
  ClearBackground(green);
  DrawText("SNAKE", 100, 150, 90, blue);
  DrawText("Press Enter", 150, 250, 60, red);
}

// Dibujado de pantalla de muerte
void DrawGameOver(Score *score) {
  ClearBackground(green);
  DrawText("GAME OVER", 150, 150, 60, blue);
  score->Draw();
  DrawText("Press Enter", 150, 260, 50, red);
}

// detect collision with snake body;
bool colission(Nodo *Snake, Vector2 ObjectPosition) {
  Nodo *actual = Snake;
  if (actual != nullptr) {
    if (Vector2Equals(actual->valor, ObjectPosition)) {
      return true;
    } else {
      return colission(actual->siguiente, ObjectPosition);
    }
  }
  return false;
}

// reset the snake game
void resetGame(Snake *snake, Score *score) {
  Dificult = 0;
  snake->Reset(Vector2{7 * (float)SCALE, 8 * (float)SCALE});
  snake->setBodySize(5);
  score->set_position(Vector2{0, 0});
  score->set_points(0);
}

Vector2 randCell() {
  float x = GetRandomValue(0, ((CELL_COUNT)-1));
  float y = GetRandomValue(0, ((CELL_COUNT)-1));
  return Vector2{x * SCALE, y * SCALE};
}

void changeDificult(int score) {
  if (score >= 2500) {
    Dificult = 5;
  } else if (score >= 2000) {
    Dificult = 4;
  } else if (score >= 1500) {
    Dificult = 3;
  } else if (score >= 1000) {
    Dificult = 2;
  } else if (score >= 500) {
    Dificult = 1;
  } else {
    Dificult = 0;
  }
}

int main(void) {

  const int screenWidth = SCALE * CELL_COUNT;
  const int screenHeight = SCALE * CELL_COUNT;

  InitWindow(screenWidth, screenHeight, "SNAKE");

  int t = 0;

  Texture2D textureBackground = LoadTexture("./Assets/Background.png");

  Snake snake(Vector2{7 * (float)SCALE, 8 * (float)SCALE}, (float)SCALE, 5);
  Food manzana(Vector2{(float)SCALE * 10, (float)SCALE * 1}, 50, SCALE, 0);
  Food pizza(Vector2{(float)SCALE * 11, (float)SCALE * 11}, 100, SCALE, 1);
  Score score(Vector2{0, 0}, 0, SCALE, red);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    if (strcmp(currentScene.c_str(), "menu") == 0) {

      // MENU
      if (IsKeyPressed(KEY_ENTER)) {
        resetGame(&snake, &score);
        // reset score
        currentScene = "game";
      }
      // DRAWING

      BeginDrawing();
      DrawMenu();
      EndDrawing();

    } else if (strcmp(currentScene.c_str(), "game") == 0) {
      // JUEGO

      if (t % (10 - Dificult ) == 0) {
        snake.motion();
        // colision con las frutas

        if (colission(snake.get_Head(), manzana.get_position())) {
          snake.incrementBody();
          score.AddPoints(manzana.get_points());

          changeDificult(score.get_points());
          // posicion de la fruta sin que toque el cuerpo
          do {
            manzana.set_position(randCell());
            // se verifica tambien que el tamanio del cuerpo no ocupe todo el
            // tablero para evitar no salir del bucle
          } while (colission(snake.get_Head(), manzana.get_position()) ==
                       true &&
                   snake.get_tamanio() < CELL_COUNT * CELL_COUNT - 1);
        }

        if (colission(snake.get_Head(), pizza.get_position())) {
          snake.incrementBody();
          snake.incrementBody();

          score.AddPoints(pizza.get_points());

          changeDificult(score.get_points());

          // posicion de la fruta sin que toque el cuerpo
          do {
            pizza.set_position(randCell());
            // se verifica tambien que el tamanio del cuerpo no ocupe todo el
            // tablero para evitar no salir del bucle
          } while (colission(snake.get_Head(), pizza.get_position()) == true &&
                   snake.get_tamanio() < CELL_COUNT * CELL_COUNT - 1);
        }

        // delimitar extremos de pantalla y colision con el cuerpo
        if (snake.get_Head()->valor.x < 0 ||
            snake.get_Head()->valor.x >= screenWidth ||
            snake.get_Head()->valor.y < 0 ||
            snake.get_Head()->valor.y >= screenHeight ||
            colission(snake.get_Head()->siguiente, snake.get_Head()->valor) ==
                true) {
          currentScene = "gameOver";
        }

        t = 0;
      }
      t++;
      // DRAWING

      BeginDrawing();

      ClearBackground(GRAY);

      // Fondo
      DrawTexture(textureBackground, 0, 0, WHITE);

      snake.Draw();

      manzana.Draw();
      pizza.Draw();

      score.Draw();
      // Texto de dificultad
      DrawText(TextFormat("Dificult: %2i", Dificult), 400, 0, 40, red);
      EndDrawing();

    } else {

      // GAME OVER

      score.set_position(Vector2{150, 200});

      if (IsKeyPressed(KEY_ENTER) == true) {
        currentScene = "menu";
      }
      // DRAWING

      BeginDrawing();
      DrawGameOver(&score);

      EndDrawing();
    }
  }

  CloseWindow();

  return 0;
}
