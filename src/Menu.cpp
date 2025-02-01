#include "Menu.hpp"
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

  for (size_t i = 0; i < menuOptions.size(); i++) {
    sf::Text text;
    text.setFont(this->font);
    text.setString(menuOptions[i]);
    text.setCharacterSize(25);
    text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::Black);
    text.setPosition(350.f, 200.f + i * 50.f);
    this->options.push_back(text);
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

void Menu::render() {
  for (auto &option : options) {
    this->window->draw(option);
  }
}
