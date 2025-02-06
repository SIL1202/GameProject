#include "PauseMenu.hpp"
#include <iostream>
#include <string>
#include <vector>

void PauseMenu::initFont() {
  if (!this->font.loadFromFile("/Users/sil/.config/nvim/GameProject/assets/"
                               "JetBrainsMonoNerdFont-Bold.ttf")) {
    std::cerr << "Failed to load font(initFont)!" << std::endl;
    exit(1);
  }
}

void PauseMenu::initPauseMenu() {
  std::vector<std::string> menuOptions = {"Resume", "Restart Game",
                                          "Quit & Save"};
  for (size_t i = 0; i < menuOptions.size(); i++) {
    sf::Text text;
    text.setFont(this->font);
    text.setString(menuOptions[i]);

    // 選項文字置中設定
    sf::FloatRect textBound = text.getLocalBounds();
    text.setOrigin(+textBound.width / 2.f,
                   textBound.height / 2.f); // 重新定位文字原點
    text.setPosition(this->window->getSize().x / 2.f,
                     250.f + i * 50.f); // 設定位置
    // 加入到陣列
    this->options.push_back(text);
    this->scaleFactors.push_back(1.0f);
  }
}

void PauseMenu::renderAnimation() {
  for (size_t i = 0; i < this->options.size(); i++) {
    float targetScale = (i == selectedIndex) ? 1.2f : 1.0f;
    scaleFactors[i] += (targetScale - scaleFactors[i]) * 0.1f;

    this->options[i].setScale(scaleFactors[i], scaleFactors[i]);
  }
}

PauseMenu::PauseMenu(sf::RenderWindow *win) {
  this->window = win;
  this->selectedIndex = 1;
  this->initFont();
  this->initPauseMenu();
}

PauseMenu::~PauseMenu() {}

void PauseMenu::moveUp() {
  if (this->selectedIndex > 0) {
    this->selectedIndex--;
  }
}

void PauseMenu::moveDown() {
  if (this->selectedIndex < this->options.size() - 1) {
    this->selectedIndex++;
  }
}

int PauseMenu::getSelectedIndex() { return this->selectedIndex; }

void PauseMenu::update(sf::Vector2f mousePos) {
  for (size_t i = 0; i < this->options.size(); i++) {
    if (this->options[i].getGlobalBounds().contains(mousePos)) {
      this->selectedIndex = i;
    }
  }

  for (size_t i = 0; i < this->options.size(); i++) {
    bool isSelected = (i == this->selectedIndex);

    // **焦糖色文字（選中時） & 深灰色（未選中）**
    sf::Color textColor =
        isSelected ? sf::Color(180, 90, 40) : sf::Color(0, 0, 0);
    this->options[i].setFillColor(textColor);

    // **選中時的縮放效果**
    this->options[i].setScale(isSelected ? 1.2f : 1.0f,
                              isSelected ? 1.2f : 1.0f);
  }
}

void PauseMenu::render() {
  this->renderAnimation();

  for (size_t i = 0; i < options.size(); i++) {
    this->window->draw(options[i]);
  }
}
