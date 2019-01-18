#pragma once
#include <vector>
#include <string>

class Room {
private:
  int connection;
  std::vector<std::string> players;
public:
  std::vector<std::string> get_player_names();
};