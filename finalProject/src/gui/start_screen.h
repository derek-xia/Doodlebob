#pragma once
#include <iostream>
#include <string>
#include "ofMain.h"
class StartScreen {
private:
  std::string message_ = "Play";
  std::string title_ = "Doodlebob";
  std::vector<char> name_;
  ofTrueTypeFont menu_font_;
  ofTrueTypeFont name_font_;
  ofTrueTypeFont title_font_;
  ofRectangle rect_;

  float box_x_;
  float box_y_;
  float box_width_;
  float box_height_;
public:
  void setup();
  void update();
  void draw();
  bool MouseClick(int x, int y);
  std::string KeyPress(int key);
};