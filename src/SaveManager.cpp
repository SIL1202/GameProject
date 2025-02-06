#include "SaveManager.hpp"
#include <fstream>
#include <iostream>

SaveManager::SaveManager() { this->saveFilePath = "savegame.json"; }

void SaveManager::saveGame(int highestScore, int dinoLevel, int currentScore) {
  json saveData;
  saveData["highestScore"] = highestScore;
  saveData["dinoLevel"] = dinoLevel;
  saveData["currentScore"] = currentScore;

  std::ofstream file(this->saveFilePath);
  if (file.is_open()) {
    file << saveData.dump(4);
    file.close();
    std::cout << "Game Saved successfully!";
    std::cout << "\nHighest Score: " << highestScore
              << "\nDino Level: " << dinoLevel
              << "\nCurrent Score: " << currentScore << std::endl;

  } else {
    std::cerr << "Failed to save game!\n";
  }
}

bool SaveManager::loadGame(int &highestScore, int &dinoLevel,
                           int &currentScore) {
  std::ifstream file(this->saveFilePath);
  if (file.is_open()) {
    json saveData;
    file >> saveData;
    file.close();

    highestScore = saveData["highestScore"];
    dinoLevel = saveData["dinoLevel"];
    currentScore = saveData["currentScore"];
    return true;
  }
  std::cerr << "No save file found. Starting a new game.\n";
  return false;
}
