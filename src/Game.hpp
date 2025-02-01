#ifndef GAME_HPP
#define GAME_HPP
#include "Menu.hpp"
#include "Obstacle.hpp"
#include "dino.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

enum class GameState { MENU, PLAYING, GAME_OVER };

class Game {
private:
  sf::RenderWindow *window;
  sf::Event event;
  sf::Clock clock; // 控制遊戲時間
  sf::Font font;
  sf::Text jumpCountingtext;
  sf::Text gameOverText;

  Dino dino;
  std::vector<Obstacle> obstacles;
  sf::Clock obstacleSpawnClock;
  bool isGameOver;
  float dt;

  GameState state;
  Menu *menu;

  void initFont();
  void initjumpCountingText();
  void initWindow();
  void initgameOverText();
  void checkCollision();
  void spawnObstacle();
  void resetGame();

public:
  Game();
  ~Game();

  void updateText();
  void renderText(sf::RenderTarget &target);
  void updateObstacle();
  void renderObstacle();
  void updateMenu();
  void renderMenu();
  void update();
  void render();
  void run();
};

#endif
