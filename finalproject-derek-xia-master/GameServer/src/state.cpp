#include "state.h"
#include <fstream>
#include <ctime>
#include <cstdlib>

using std::vector;
using std::string;

State::State()
{
  scores_ = vector<int>();
}

State::State(int players)
{
  scores_ = vector<int>(players);
}

int State::AddPlayer() {
  scores_.push_back(0);
  return scores_.size()-1;
}

void State::IncrementScore(int id)
{
  scores_[id] += 1;
}

std::vector<int> State::GetScores()
{
  return scores_;
}

int State::GetTime()
{
  return time_;
}

void State::SetLines(Game::LineVector lines)
{
  lines_ = lines;
}

Game::LineVector State::GetLines()
{
  return lines_;
}

void State::Clear()
{
  lines_.clear();
}

int State::Size()
{
  return scores_.size();
}
