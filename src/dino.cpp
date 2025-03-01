#include "dino.hpp"
// #include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>

void Dino::initTexture() {
  if (!this->texture.loadFromFile(
          "/Users/sil/Projects/GameProject/assets/dino.png")) {
    std::cerr << "Failed to load dino.png" << std::endl;
  }
}

void Dino::initSprite() {
  this->sprite.setTexture(this->texture);
  sf::FloatRect bounds = this->sprite.getLocalBounds();

  // 設定原點為底部中央
  this->sprite.setOrigin(bounds.width / 2, bounds.height);

  std::cout << "[initSprite] setOrigin(" << this->sprite.getOrigin().x << ", "
            << this->sprite.getOrigin().y << ")\n";

  // Dino 初始位置
  this->sprite.setPosition(200.f, 400.f);
  std::cout << "[initSprite] setPosition(" << this->sprite.getPosition().x
            << ", " << this->sprite.getPosition().y << ")\n";

  float scaleFactor = 0.1f;
  this->sprite.setScale(scaleFactor, scaleFactor);
  std::cout << "[initSprite] setScale(" << scaleFactor << ", " << scaleFactor
            << ")\n";
  sf::FloatRect bounds1 = this->sprite.getLocalBounds();
  std::cout << "[DEBUG] Dino Image Bounds: Width = " << bounds1.width
            << ", Height = " << bounds1.height << std::endl;
}

Dino::Dino() {
  this->initTexture();
  this->initSprite();
  this->isJumping = false;
  this->jumpCount = 0;
  this->velocity = sf::Vector2f(0.f, 0.f);
}

Dino::~Dino() {}

/* void Dino::upgradeAppearance(int level) {
  switch (level) {
  case 2:
    this->sprite.setColor(sf::Color(255, 215, 0)); // 金色
    break;
  case 3:
    this->sprite.setColor(sf::Color(255, 140, 0)); // 橘色
    break;
  case 4:
    this->sprite.setColor(sf::Color(220, 20, 60)); // 紅色
    break;
  case 5:
    this->sprite.setColor(sf::Color::White); // 最高等級 白色
    break;
  default:
    this->sprite.setColor(sf::Color::Black);
    break;
  }
} */

void Dino::jump() {
  if (this->sprite.getPosition().y >= 330.f) {
    this->isJumping = true;
    this->velocity.y = -300.f;
    this->jumpCount++;
    std::cout << "Jump Count: " << this->jumpCount << std::endl;
  }
}

void Dino::fall(float dt) {
  this->velocity.y += 900.f * dt;
  this->sprite.move(0.f, this->velocity.y * dt);
}

// reset dino's position
void Dino::reset() {
  this->jumpCount = 0;
  this->isJumping = false;
  this->velocity = sf::Vector2f(0.f, 0.f);
  this->sprite.setPosition(100.f, 400.f);
}

unsigned int Dino::getJumpCount() { return this->jumpCount; }

void Dino::update(float dt) {
  if (this->isJumping) {
    if (this->velocity.y < 0) {
      // 在上升時，減少重力影響
      this->velocity.y += 140.0f * dt;
    } else {
      // 在下降時，加強重力影響
      this->velocity.y += 160.0f * dt;
    }

    if (this->velocity.y >= -50.f && this->velocity.y <= 50.f) {
      this->velocity.y *= 0.95f; // 當速度接近 0 時，進一步減速
    }
    this->sprite.move(0.f, this->velocity.y * dt);

    std::cout << "[update] Moving Dino: Y = " << this->sprite.getPosition().y
              << ", Velocity = " << this->velocity.y << "\n";

    if (this->sprite.getPosition().y >= 400.f) {
      this->sprite.setPosition(this->sprite.getPosition().x, 400.f);
      this->isJumping = false;
      std::cout << "[update] Dino landed at 400.f\n";
    }
  }
}

void Dino::render(sf::RenderTarget &target) { target.draw(this->sprite); }

sf::FloatRect Dino::getBound() const { return this->sprite.getGlobalBounds(); }
