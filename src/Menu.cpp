#include "Menu.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>
#include <string>
#include <vector>

void Menu::initFont() {
  if (!this->font.loadFromFile("/Users/sil/.config/nvim/GameProject/assets/"
                               "JetBrainsMonoNerdFont-Bold.ttf")) {
    std::cerr << "Failed to load font(initFont)!" << std::endl;
    exit(1);
  }
}

void Menu::initMenu() {
  std::vector<std::string> menuOptions = {"Start Game", "Continue", "Exit"};
  float bgWidth = 250.f; // 固定背景寬度
  float bgHeight = 50.f; // 固定背景高度
  float startY = 260.f;  // 第一個選項的 Y 位置

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

    // 選項文字背景設定
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(bgWidth, bgHeight));
    background.setFillColor(sf::Color(0, 0, 0, 0));

    // **確保所有背景大小相同**
    background.setOrigin(bgWidth / 2.f, bgHeight / 2.f);
    background.setPosition(this->window->getSize().x / 2.f,
                           startY + i * bgHeight);
    // 加入到陣列
    this->options.push_back(text);
    this->scaleFactors.push_back(1.0f);
    this->textBackground.push_back(background);
  }
}

void Menu::renderAnimation() {
  for (size_t i = 0; i < this->options.size(); i++) {
    float targetScale = (i == selectedIndex) ? 1.2f : 1.0f;
    scaleFactors[i] += (targetScale - scaleFactors[i]) * 0.1f;

    this->options[i].setScale(scaleFactors[i], scaleFactors[i]);
  }
}

Menu::Menu(sf::RenderWindow *win) {
  this->window = win;
  this->selectedIndex = 0;
  this->initFont();
  this->initMenu();
}

Menu::~Menu() {}

void Menu::moveUp() {
  if (this->selectedIndex > 0) {
    this->options[this->selectedIndex].setFillColor(sf::Color::Black);
    this->selectedIndex--;
    this->options[this->selectedIndex].setFillColor(sf::Color::Red);
  }
}

void Menu::moveDown() {
  if (this->selectedIndex < this->options.size() - 1) {
    this->options[this->selectedIndex].setFillColor(sf::Color::Black);
    this->selectedIndex++;
    this->options[this->selectedIndex].setFillColor(sf::Color::Red);
  }
}

int Menu::getSelectedIndex() { return this->selectedIndex; }

void Menu::update(sf::Vector2f mousePos) {
  // bool isMouseOver = false;

  for (size_t i = 0; i < this->options.size(); i++) {
    if (this->options[i].getGlobalBounds().contains(mousePos)) {
      this->selectedIndex = i;
      // isMouseOver = true;  -> to cancel J, K option!!
    }
  }

  for (size_t i = 0; i < this->options.size(); i++) {
    if (i == this->selectedIndex) {
      this->options[i].setScale(1.2f, 1.2f);
      this->options[i].setFillColor(sf::Color::Red);
    } else {
      this->options[i].setScale(1.0f, 1.0f);
      this->options[i].setFillColor(sf::Color::Black);
    }
  }
}

void Menu::render() {
  for (size_t i = 0; i < this->textBackground.size(); i++)
    this->window->draw(this->textBackground[i]);
  this->renderAnimation();

  for (size_t i = 0; i < options.size(); i++) {
    this->window->draw(options[i]);
  }
}
