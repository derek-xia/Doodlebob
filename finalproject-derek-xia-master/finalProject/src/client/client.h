#pragma once
#include <Ice/Ice.h>
#include "Game.h"
#include "ofMain.h"

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

class Client {
private:
  const std::string kProxy_ = "GameServer:default -h 10.194.165.171 -p 10000";
  int num_players_;
  int id_;
  Game::GameInfo state_;
  Game::Players players_;
  
public:
  int Connect(std::string name);
  void Increment();
  void SetNumPlayers();
  int getId();

  void SetLines(std::vector<ofPolyline> lines);
  std::vector<ofPolyline> GetLines();
  void SetColors(std::vector<int> colors);
  std::vector<int> GetColors();

  void UpdateGameInfo();
  int GetCurrPlayer();
  bool IsInProgress();
  bool HasChangedTurn();
  std::string GetWord();
  std::string GetHint();
  int GetTime();
  int GetRound();
  bool CheckWord(string word);

  void UpdatePlayers();
  std::vector<int> GetScores();
  std::vector<std::string> GetNames();
  std::vector<std::string> GetLastGuesses();
  std::vector<bool> GetGuessed();

};