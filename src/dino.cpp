#include "dino.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>
/*
void Dino::initTexture() {
  if (!this->texture.loadFromFile("assets/dino.png")) {
    std::cerr << "Failed to load dino.png" << std::endl;
  }
}

void Dino::initSprite() {
  this->sprite.setTexture(this->texture);
  this->sprite.setScale(0.5f, 0.5f);
  this->sprite.setPosition(100.f, 400.f);
}
*/
Dino::Dino() {
  // this->initTexture();
  // this->initSprite();
  this->shape.setPosition(100.f, 400.f);
  this->shape.setFillColor(sf::Color::Black);
  this->shape.setSize(sf::Vector2f(50.f, 50.f));
  this->isJumping = false;
  this->jumpCount = 0;
  this->velocity = sf::Vector2f(0.f, 0.f);
}

Dino::~Dino() {}

void Dino::jump() {
  if (this->shape.getPosition().y >= 330.f) {
    this->isJumping = true;
    this->velocity.y = -700.f;
    this->jumpCount++;
    std::cout << "Jump Count: " << this->jumpCount << std::endl;
  }
}

void Dino::fall(float dt) {
  this->velocity.y += 900.f * dt;
  this->shape.move(0.f, this->velocity.y * dt);
}

// reset dino's position
void Dino::reset() {
  this->jumpCount = 0;
  this->isJumping = false;
  this->velocity = sf::Vector2f(0.f, 0.f);
  this->shape.setPosition(100.f, 400.f);
}

unsigned int Dino::getJumpCount() { return this->jumpCount; }

void Dino::update(float dt) {
  if (this->isJumping) {
    this->velocity.y += 900.0f * dt; // 模擬重力
    this->shape.move(0.f, this->velocity.y * dt);

    if (this->shape.getPosition().y >= 400.f) {
      this->shape.setPosition(this->shape.getPosition().x, 400.f);
      this->isJumping = false;
    }
  }
}

void Dino::render(sf::RenderTarget &target) { target.draw(this->shape); }

sf::FloatRect Dino::getBound() const { return this->shape.getGlobalBounds(); }
