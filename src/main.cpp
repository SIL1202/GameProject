#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
  // ✅ 創建 800x600 的視窗
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML 2.6.2 Test");

  // ✅ 遊戲迴圈
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) { // ✅ `pollEvent()` 現在應該這樣用
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          window.close();
        }
      }
    }

    // ✅ 清除畫面
    window.clear(sf::Color::Blue);

    // ✅ 顯示畫面
    window.display();
  }

  std::cout << "SFML 2.6.2 is working!" << std::endl;
  return 0;
}
