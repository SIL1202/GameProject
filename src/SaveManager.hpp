#ifndef SAVEMANAGER_HPP
#define SAVEMANAGER_HPP

#include "../include/json.hpp"
#include <string>

using json = nlohmann::json;

class SaveManager {
private:
  std::string saveFilePath; // 存檔路徑

public:
  SaveManager();

  void saveGame(int highestScore, int dinoLevel, int currentScore);
  bool loadGame(int &highestScore, int &dinoLevel, int &currentScore);
};

#endif
