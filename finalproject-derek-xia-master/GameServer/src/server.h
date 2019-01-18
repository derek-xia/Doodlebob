#pragma once
#include <Ice/Ice.h>
#include <string>
#include "Game.h"
#include <vector>
#include <fstream>

using namespace std;
using namespace Game;

string PickWord();
string PickHint(string hint, string word);

struct State {
  vector<int> scores_;
  time_t start_time_;
  int player_turn_;
  int round_;
  LineVector lines_;
  ColorVector colors_;
  string word_;
  string hint_;
  vector<bool> guessed_;
  bool hint_given_;
  Players players_;
};

class GameStateI : public GameState
{
private:
  const time_t kTurnLength_ = 25;
  State game_;
  int GetTimeRemaining();
  void ChangeTurn(GameInfo &info);
  
public:
  virtual void printString(string s, const Ice::Current&) override;
  virtual int AddPlayer(string name, const Ice::Current&) override;
  virtual void IncrementScore(int id, const Ice::Current&) override;
  virtual int GetScore(int id, const Ice::Current&) override;
  virtual int GetNumPlayers(const Ice::Current &) override;

  virtual LineVector GetLines(const Ice::Current&) override;
  virtual void DrawLines(LineVector lines, const Ice::Current&) override;
  virtual ColorVector GetColors(const Ice::Current&) override;
  virtual void DrawColors(ColorVector colors, const Ice::Current&) override;

  virtual GameInfo GetGameInfo(const Ice::Current&) override;
  virtual bool CheckWord(string word, int id, const Ice::Current&) override;

  virtual Players GetPlayers(const ::Ice::Current& current) override;
};