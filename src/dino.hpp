#ifndef DINO_HPP
#define DINO_HPP

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include <SFML/Graphics.hpp>

class Dino {
private:
  sf::RectangleShape shape;
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Vector2f velocity;
  sf::Clock clock;
  bool isJumping;
  unsigned int jumpCount;

  void initTexture();
  void initSprite();

public:
  Dino();
  ~Dino();

  unsigned int getJumpCount();
  void upgradeAppearance(int dinoLevel);
  void update(float dt);
  void render(sf::RenderTarget &target);
  void jump();
  void reset();
  void fall(float dt);
  sf::FloatRect getBound() const;
};

#endif
