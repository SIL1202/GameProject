#ifndef GAME_HPP
#define GAME_HPP
#include "Menu.hpp"
#include "Obstacle.hpp"
#include "PauseMenu.hpp"
#include "SaveManager.hpp"
#include "dino.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

enum class GameState { MENU, PLAYING, GAME_OVER, PAUSED };

class Game {
private:
  sf::RenderWindow *window;
  sf::Event event;
  sf::Clock clock; // 控制遊戲時間
  sf::Font font;
  sf::Text jumpCountingtext;
  sf::Text gameOverText;
  sf::Text currentScoreText;
  sf::Text highestScoreText;

  Dino dino;
  std::vector<Obstacle> obstacles;
  sf::Clock obstacleSpawnClock;
  bool isGameOver;
  float dt;

  GameState state;
  Menu *menu;
  PauseMenu *pauseMenu;
  SaveManager saveManager;
  int highestScore;
  int dinoLevel;
  int currentScore;
  bool shouldClose;

  void initFont();
  void initjumpCountingText();
  void inithighestScoreText();
  void initcurrentScoreText();
  void initWindow();
  void initgameOverText();
  void checkCollision();
  void spawnObstacle();
  void resetGame();
  void handleMenuSelection(int choice);
  void handlePauseMenuSelection(int choice);

public:
  Game();
  ~Game();

  void updateText();
  void renderText(sf::RenderTarget &target);

  void updateObstacle();
  void renderObstacle();

  void updateMenu();
  void renderMenu();

  void updatePauseMenu();
  void renderPauseMenu();

  void update();
  void render();

  void saveGame();
  void loadGame();
  void run();
};

#endif
