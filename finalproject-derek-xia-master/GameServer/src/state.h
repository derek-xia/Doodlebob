#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Game.h"

using std::string;
using std::vector;

class State {
private:
  vector<int> scores_;
  int time_;

  Game::LineVector lines_;

  string word_;
public:
  State();
  State(int players);
  
  int AddPlayer();
  void IncrementScore(int id);
  std::vector<int> GetScores();
  int GetTime();

  void SetLines(Game::LineVector lines);
  Game::LineVector GetLines();
  void Clear();

  int Size();
};