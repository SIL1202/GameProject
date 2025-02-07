#include "SaveManager.hpp"
#include <fstream>
#include <iostream>
#include <unistd.h>

SaveManager::SaveManager() {
  this->saveFilePath = "../savegame.json"; // 存到專案主目錄
}

void SaveManager::saveGame(int highestScore, int dinoLevel, int currentScore) {
  json saveData;
  saveData["highestScore"] = highestScore;
  saveData["dinoLevel"] = dinoLevel;
  saveData["currentScore"] = currentScore;

  std::ofstream file(this->saveFilePath);
  if (file.is_open()) {
    file << saveData.dump(4);
    file.close();
    std::cout << "Game Saved successfully at: " << this->saveFilePath
              << std::endl;
  } else {
    std::cerr << "Failed to save game at: " << this->saveFilePath << std::endl;
  }
}

bool SaveManager::loadGame(int &highestScore, int &dinoLevel,
                           int &currentScore) {
  std::ifstream infile(this->saveFilePath);

  if (!infile) {
    std::cerr << "No save file found at: " << this->saveFilePath << std::endl;
    return false;
  }

  try {
    json saveData;
    infile >> saveData;
    infile.close();

    highestScore = saveData["highestScore"];
    dinoLevel = saveData["dinoLevel"];
    currentScore = saveData["currentScore"];

    std::cout << "Game Loaded Successfully!\n"
              << "Highest Score: " << highestScore
              << ", Dino Level: " << dinoLevel
              << ", Current Score: " << currentScore << std::endl;
    return true;

  } catch (json::parse_error &e) {
    std::cerr << "JSON Parsing error: " << e.what() << std::endl;
    return false;
  }
}
