#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

class Obstacle {
private:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Vector2f velocity;
  sf::RectangleShape shape;

  void initTexture();
  void initSprite();

public:
  Obstacle(const sf::Vector2f &dinoSize);
  ~Obstacle();

  void update();
  void render(sf::RenderWindow &window);

  sf::FloatRect getBounds() const;
};

#endif // !OBSTACLE_HPP
