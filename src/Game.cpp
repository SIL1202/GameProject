#include "Game.hpp"
#include "../include/json.hpp"
#include "PauseMenu.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include <cstdlib>
#include <iostream>
using json = nlohmann::json;
#include <sstream>

void Game::initFont() {
  if (!this->font.loadFromFile("/Users/sil/.config/nvim/GameProject/assets/"
                               "JetBrainsMonoNerdFont-Bold.ttf")) {
    std::cerr << "Failed to load font(initFont)!" << std::endl;
    exit(1);
  }
}

void Game::initjumpCountingText() {
  this->jumpCountingtext.setFont(this->font);
  this->jumpCountingtext.setCharacterSize(20);
  this->jumpCountingtext.setFillColor(sf::Color(255, 150, 50));
  this->jumpCountingtext.setPosition(10.f, 10.f);
  this->jumpCountingtext.setString("NONE");
}

void Game::inithighestScoreText() {
  this->highestScoreText.setFont(this->font);
  this->highestScoreText.setCharacterSize(20);
  this->highestScoreText.setFillColor(sf::Color(255, 150, 50));
  this->highestScoreText.setPosition(300.f, 10.f);
  this->highestScoreText.setString("NONE");
}

void Game::initcurrentScoreText() {
  this->currentScoreText.setFont(this->font);
  this->currentScoreText.setCharacterSize(20);
  this->currentScoreText.setFillColor(sf::Color(255, 150, 50));
  this->currentScoreText.setPosition(550.f, 10.f);
  this->currentScoreText.setString("NONE");
}

// initialize winow
void Game::initWindow() {
  this->window =
      new sf::RenderWindow(sf::VideoMode(800, 600), "Endless Runner");
  this->window->setFramerateLimit(120);
}
// initialize game over text
void Game::initgameOverText() {
  this->gameOverText.setFont(this->font);
  this->gameOverText.setCharacterSize(25);
  this->gameOverText.setFillColor(sf::Color::Red);
  this->gameOverText.setString("Game Over! Press Enter to Restart");

  sf::FloatRect textBounds = this->gameOverText.getLocalBounds();

  // **修正這一行**
  this->gameOverText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);

  this->gameOverText.setPosition(this->window->getSize().x / 2.0f,
                                 this->window->getSize().y / 2.0f);
}

// check collision of each obstacle
void Game::checkCollision() {
  auto dinoBound = this->dino.getBound();

  for (auto &obstacle : this->obstacles) {
    if (dinoBound.intersects(obstacle.getBounds())) {
      std::cout << "Collision Detected! Game Over!\n";
      this->isGameOver = true;
      return;
    }
  }
}

void Game::spawnObstacle() {
  float spawnInterval = 1.0f + static_cast<float>(std::rand()) /
                                   static_cast<float>(RAND_MAX) * 4.5f;

  if (this->obstacleSpawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
    this->obstacleSpawnClock.restart();

    sf::Vector2f dinoSize =
        sf::Vector2f(this->dino.getBound().width, this->dino.getBound().height);

    // **生成新障礙物**
    Obstacle newObstacle(dinoSize);
    this->obstacles.push_back(newObstacle);
  }
}

// reset Game
void Game::resetGame() {
  this->isGameOver = false;
  this->dino.reset(); // go Dino to reset dino's position.
  this->obstacles.clear();
  this->obstacleSpawnClock.restart();
  this->currentScore = 0;
  this->dinoLevel = 1;

  if (this->currentScore > this->highestScore)
    this->highestScore = this->currentScore;
}

void Game::handleMenuSelection(int choice) {
  switch (choice) {
  case 0:
    this->resetGame();
    this->state = GameState::PLAYING; // "Start Game"
    break;
  case 1:
    this->loadGame();
    this->state = GameState::PLAYING;
    break;
  case 2:
    this->window->close(); // "Exit"
    break;
  }
}

void Game::handlePauseMenuSelection(int choice) {
  switch (choice) {
  case 0:
    std::cout << "選擇了 Resume\n";
    this->state = GameState::PLAYING;
    break;
  case 1:
    std::cout << "選擇了 Continue\n";
    this->loadGame();
    this->state = GameState::PLAYING;
    break;
  case 2:
    std::cout << "存檔並退出...\n"; // 這行應該要輸出
    this->saveGame();
    this->window->close();
    break;
  default:
    std::cout << "未知選項: " << choice << "\n";
    break;
  }
}

void Game::saveGame() {
  if (this->currentScore > this->highestScore) {
    this->highestScore = this->currentScore; // 確保存檔時是最高分
  }
  this->saveManager.saveGame(highestScore, dinoLevel, currentScore);
}

void Game::loadGame() {
  if (this->saveManager.loadGame(highestScore, dinoLevel, currentScore)) {
    std::cout << "Game loaded! Highest Score: " << highestScore
              << ", Dino Level: " << dinoLevel
              << "Current Score: " << currentScore << std::endl;
  }
}

Game::Game() {
  dt = this->clock.restart().asSeconds();
  this->loadGame();
  this->initFont();
  this->initjumpCountingText();
  this->initWindow();
  this->isGameOver = false;
  this->initgameOverText();
  this->highestScore = 0;
  this->inithighestScoreText();
  this->dinoLevel = 1;
  this->currentScore = 0;
  this->initcurrentScoreText();
  // When game start, initial menu.
  this->state = GameState::MENU;
  this->menu = new Menu(this->window);
  this->pauseMenu = new PauseMenu(this->window);
}

Game::~Game() {
  if (this->menu) {
    delete this->menu;
    this->menu = nullptr; // 避免指標變成野指標
  }
  if (this->pauseMenu) {
    delete this->pauseMenu;
    this->pauseMenu = nullptr; // 避免指標變成野指標
  }
  if (this->window) {
    delete this->window;
    this->window = nullptr;
  }
}

void Game::updateText() {
  std::stringstream ss;
  ss << "Jumps: " << this->dino.getJumpCount();
  this->jumpCountingtext.setString(ss.str());
  ss.str("");
  ss.clear();

  ss << "Score: " << this->currentScore;
  this->currentScoreText.setString(ss.str());
  ss.str("");
  ss.clear();

  ss << "Highest: " << this->highestScore;
  this->highestScoreText.setString(ss.str());
}

void Game::renderText(sf::RenderTarget &target) {
  target.draw(this->jumpCountingtext);
  target.draw(this->currentScoreText);
  target.draw(this->highestScoreText);

  if (this->isGameOver)
    target.draw(this->gameOverText);
}

void Game::updateObstacle() {
  this->spawnObstacle();

  // Check if obstacles cross the bound
  for (auto it = obstacles.begin(); it != obstacles.end();) {
    it->update();

    if (it->getBounds().left + it->getBounds().width < 0) {
      it = this->obstacles.erase(it);
    } else {
      it++;
    }
  }
}

void Game::renderObstacle() {
  for (auto &obstacle : this->obstacles) {
    obstacle.render(*this->window);
  }
}

void Game::updateMenu() {
  if (this->state == GameState::MENU) {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*this->window);
    sf::Vector2f mousePo = this->window->mapPixelToCoords(pixelPos);
    this->menu->update(mousePo); // 統一處理滑鼠 & 鍵盤選擇

    if (this->event.type == sf::Event::KeyPressed) {
      if (this->event.key.code == sf::Keyboard::K) // K向上
        this->menu->moveUp();
      else if (this->event.key.code == sf::Keyboard::J) // J向下
        this->menu->moveDown();
      else if (this->event.key.code == sf::Keyboard::Enter) {
        int choice = this->menu->getSelectedIndex();
        this->handleMenuSelection(choice);
      }
    } else if (this->event.type == sf::Event::MouseButtonPressed) {
      if (this->event.mouseButton.button == sf::Mouse::Left) {
        int choice = this->menu->getSelectedIndex();
        this->handleMenuSelection(choice);
      }
    }
  }
}

void Game::updatePauseMenu() {
  if (this->state == GameState::PAUSED) {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*this->window);
    sf::Vector2f mousePo = this->window->mapPixelToCoords(pixelPos);
    this->pauseMenu->update(mousePo); // 統一處理滑鼠 & 鍵盤選擇

    if (this->event.type == sf::Event::KeyPressed) {
      if (this->event.key.code == sf::Keyboard::K) // K向上
        this->pauseMenu->moveUp();
      else if (this->event.key.code == sf::Keyboard::J) // J向下
        this->pauseMenu->moveDown();
      else if (this->event.key.code == sf::Keyboard::Enter) {
        int choice = this->pauseMenu->getSelectedIndex();
        std::cout << "按下 Enter 鍵" << std::endl;
        this->handlePauseMenuSelection(choice);
        std::cout << "Pause Menu 選擇: " << choice << "\n"; // Debug
      }
    } else if (this->event.type == sf::Event::MouseButtonPressed) {
      if (this->event.mouseButton.button == sf::Mouse::Left) {
        int choice = this->pauseMenu->getSelectedIndex();
        this->handlePauseMenuSelection(choice);
      }
    }
  }
}

void Game::renderMenu() {
  if (state == GameState::MENU)
    this->menu->render();
  // else if (state == GameState::PLAYING) {
  //  **之後這裡會畫 Dino、障礙物**
  //}
}

void Game::renderPauseMenu() {
  if (this->state == GameState::PAUSED) {
    this->pauseMenu->render();
    std::cout << "正在渲染 Pause Menu" << std::endl;
  }
}

void Game::update() {
  // window pollEvent
  while (this->window->pollEvent(this->event)) {
    switch (this->event.type) {
    case sf::Event::Closed:
      this->saveGame();
      this->window->close();
      break;
    case sf::Event::KeyPressed:
      if (this->event.key.code == sf::Keyboard::Escape) {
        if (this->state == GameState::PLAYING) {
          this->state = GameState::PAUSED; // 進入暫停選單
        } else if (this->state == GameState::PAUSED) {
          this->state = GameState::PLAYING; // 返回遊戲
        }
      } else if ((this->event.key.code == sf::Keyboard::Space ||
                  this->event.key.code == sf::Keyboard::Up) &&
                 !isGameOver)
        this->dino.jump();
      else if ((this->event.key.code == sf::Keyboard::Enter ||
                this->event.key.code == sf::Keyboard::Space) &&
               isGameOver) {
        this->resetGame();
        this->state = GameState::PLAYING;
      }
      break;
    default:
      break;
    }

    // **當前在 `MENU` 狀態，處理選單**
    if (this->state == GameState::MENU) {
      this->updateMenu();
      return;
    }

    // **當前在 `PAUSED` 狀態，處理暫停選單**
    if (this->state == GameState::PAUSED) {
      std::cout << "進入 updatePauseMenu()" << std::endl;
      this->updatePauseMenu();
      return;
    }
  }

  if (this->state == GameState::PLAYING) {
    // game is not over then update dino.
    if (!this->isGameOver) {
      // 遊戲進行中，正常更新 Dino
      this->currentScore += 1;

      //**更新最高分**
      if (this->currentScore > this->highestScore)
        this->highestScore = this->currentScore;

      this->dino.update(dt);
      this->updateText();
      this->checkCollision();

      this->updateObstacle();
    } else {
      // Dino 持續往下掉落
      this->dino.fall(dt);

      // 如果 Dino 掉出畫面底部，則執行 resetGame()
      if (this->dino.getBound().top > this->window->getSize().y) {
        this->isGameOver = true;
      }
    }
  }
}

void Game::render() {
  this->window->clear(sf::Color(245, 230, 215, 255)); // 設定背景顏色

  if (this->state == GameState::MENU) {
    this->renderMenu();
  } else if (this->state == GameState::PAUSED)
    this->renderPauseMenu();
  else {
    this->dino.render(*this->window);
    this->renderText(*this->window);
    this->renderObstacle();

    if (this->isGameOver) {
      this->window->draw(this->gameOverText);
    }
  }

  this->window->display();
}

void Game::run() {
  while (this->window->isOpen()) {
    this->update();
    this->render();
  }
}
