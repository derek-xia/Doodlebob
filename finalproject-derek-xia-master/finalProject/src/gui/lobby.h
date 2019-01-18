#pragma once
#include <vector>
#include "ofMain.h"
#include "room.h"
class Lobby {
private:
  std::string message_ = "Create a team or join an existing team.";
  std::string back_text_ = "Back";

  ofTrueTypeFont menu_font_;
  ofTrueTypeFont back_font_;
  ofRectangle rect_;
  ofRectangle back_;

  float box_x_;
  float box_y_;

  float back_x_ = 15;
  float back_y_ = 20;

  std::vector<Room> rooms;
public:
  void setup();
  void update();
  void draw();
  bool MouseClick(int x, int y);
};