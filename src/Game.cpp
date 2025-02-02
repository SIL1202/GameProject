#include "Game.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include <cstdlib>
#include <iostream>
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

// initialize winow
void Game::initWindow() {
  this->window =
      new sf::RenderWindow(sf::VideoMode(800, 600), "Endless Runner");
  this->window->setFramerateLimit(120);
}

// initialize game over text
void Game::initgameOverText() {
  gameOverText.setFont(this->font);
  gameOverText.setCharacterSize(25);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setString("Game Over! Press Enter to Restart");

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
}

void Game::handleMenuSelection(int choice) {
  switch (choice) {
  case 0:
    state = GameState::PLAYING; // "Start Game"
    break;
  case 1:
    std::cout << "Load Save (未實作)\n"; // "Continue"
    this->state = GameState::PLAYING;
    break;
  case 2:
    this->window->close(); // "Exit"
    break;
  }
}

Game::Game() {
  dt = this->clock.restart().asSeconds();
  this->initFont();
  this->initjumpCountingText();
  this->initWindow();
  this->isGameOver = false;
  this->initgameOverText();

  // When game start, initial menu.
  this->state = GameState::MENU;
  this->menu = new Menu(this->window);
}

Game::~Game() {
  if (this->menu) {
    delete this->menu;
    this->menu = nullptr; // 避免指標變成野指標
  }
  if (this->window) {
    delete this->window;
    this->window = nullptr;
  }
}

void Game::updateText() {
  std::stringstream ss;
  ss << "jumps: " << this->dino.getJumpCount();
  this->jumpCountingtext.setString(ss.str());
}

void Game::renderText(sf::RenderTarget &target) {
  target.draw(this->jumpCountingtext);
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

void Game::renderMenu() {
  if (state == GameState::MENU)
    this->menu->render();
  // else if (state == GameState::PLAYING) {
  //  **之後這裡會畫 Dino、障礙物**
  //}
}

void Game::update() {
  // window pollEvent
  while (this->window->pollEvent(this->event)) {
    switch (this->event.type) {
    case sf::Event::Closed:
      this->window->close();
      break;
    case sf::Event::KeyPressed:
      if (this->event.key.code == sf::Keyboard::Escape)
        this->window->close();
      else if ((this->event.key.code == sf::Keyboard::Space ||
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

    if (this->state == GameState::MENU) {
      this->updateMenu();
      return;
    }
  }

  if (this->state == GameState::PLAYING) {
    // game is not over then update dino.
    if (!this->isGameOver) {
      // 遊戲進行中，正常更新 Dino
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
  this->window->clear(sf::Color::White); // 設定背景顏色

  if (this->state == GameState::MENU) {
    this->renderMenu();
  } else {
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
