#ifndef DINO_HPP
#define DINO_HPP

#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

class Dino {
private:
  sf::RectangleShape shape;
  sf::Texture textures[3];
  sf::Sprite sprite;
  sf::Vector2f velocity;
  sf::Clock clock;
  sf::SoundBuffer jumpBuffer;  // 存音效檔案
  sf::Sound jumpSound;         // 播放音效  
  bool isJumping;
  unsigned int jumpCount;

  void initSound();
  void initTexture();
  void initSprite();

    // 動畫變數
    int frameIndex;
    float frameDuration;
    float frameTime;
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
