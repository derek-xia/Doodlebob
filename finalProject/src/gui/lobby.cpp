#include "lobby.h"

void Lobby::setup() {
  menu_font_.load("ARLRDBD.TTF", 24);
  rect_ = menu_font_.getStringBoundingBox(message_, 0, 0);

  back_font_.load("ARLRDBD.TTF", 16);
  back_ = back_font_.getStringBoundingBox(back_text_, 0, 0);
}
void Lobby::update() {
  box_x_ = (ofGetWindowWidth() - rect_.width) / 2;
  box_y_ = (ofGetWindowHeight() - rect_.height) / 6;
}
void Lobby::draw() {
  ofSetBackgroundColorHex(0x521168);
  ofSetHexColor(0xff8000);
  menu_font_.drawString(message_, box_x_, box_y_);
  back_font_.drawString(back_text_, back_x_, back_y_);
}
bool Lobby::MouseClick(int x, int y) {
  if (x >= 0 && x <= back_x_ + 2 * back_.getWidth() && y >= 0 && y <= back_y_ + 2 * back_.getHeight()) {
    return true;
  }
  return false;
}