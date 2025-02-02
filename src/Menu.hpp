#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
private:
  sf::RenderWindow *window;
  sf::Font font;
  std::vector<sf::Text> options;
  size_t selectedIndex;
  std::vector<float> scaleFactors;

  void initFont();
  void initMenu();
  void renderAnimation();

public:
  Menu(sf::RenderWindow *win);
  ~Menu();

  void moveUp();
  void moveDown();
  int getSelectedIndex();
  void update(sf::Vector2f mousePos);
  void render();
};

#endif // !MENU_HPP
