#include "Obstacle.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

Obstacle::Obstacle(const sf::Vector2f &dinoSize) {
  auto width = 40.f + static_cast<float>(rand() % 75);
  auto height = 40.f + static_cast<float>(rand() % 75);

  this->shape.setSize(sf::Vector2f(width, height));
  this->shape.setPosition(800.f, 400.f + dinoSize.y - height);

  this->shape.setFillColor(sf::Color(102, 102, 102));
  this->velocity = sf::Vector2f(-3.5f, 0.f);
}

Obstacle::~Obstacle() {}

void Obstacle::update() { this->shape.move(this->velocity); }

void Obstacle::render(sf::RenderWindow &window) { window.draw(this->shape); }

sf::FloatRect Obstacle::getBounds() const {
  return this->shape.getGlobalBounds();
}
