#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class PauseMenu {
private:
  sf::RenderWindow *window;
  sf::Font font;
  std::vector<sf::Text> options;
  size_t selectedIndex;
  std::vector<float> scaleFactors;

  void initFont();
  void initPauseMenu();
  void renderAnimation();

public:
  PauseMenu(sf::RenderWindow *win);
  ~PauseMenu();

  void moveUp();
  void moveDown();
  int getSelectedIndex();
  void update(sf::Vector2f mousePos);
  void render();
};

#endif // !PAUSEMENU_HPP
