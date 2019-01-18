#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "client.h"
#include "ofMain.h"

using std::vector;
using std::string;

enum Brushes {
  PENCIL,
  PAINT
};

class Gameplay {
private:
  ofTrueTypeFont menu_font_;
  ofTrueTypeFont title_font_;
  ofTrueTypeFont medium_font_;
  ofRectangle panel_;
  ofColor black_;
  vector<ofColor> colors_;
  ofVec2f color_picker_loc_;

  Client client_;
  string name_;

  string word_;
  int curr_player_;
  int round_;
  vector<int> scores_;
  vector<string> names_;
  vector<ofPolyline> lines_;
  vector<int> line_colors_;
  /* Ints that represent each color:
    0: white, 1: black, 2: brown, 3: red, 4: orange,
    5: yellow, 6: yellow-green, 7: green, 8: blue, 9: purple
  */
  int curr_color_ = 1;
  
  ofVec2f mouse_loc_;
  ofImage pencil_;
  ofImage timer_;

  vector<char> guessed_word_;
  bool guessed_;


public:
  void setup();
  void update();
  void draw();

  void SetName(string name);
  void updateNumPlayers();

  void Paint(ofPolyline line);
  void Fill(int x, int y);
  void KeyPress(int key);
  void MouseDraw(int size, int x, int y);
  void MouseClick(int x, int y);
  void MouseMoved(int x, int y);
};