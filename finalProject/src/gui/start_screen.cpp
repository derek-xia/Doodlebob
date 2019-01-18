#include "start_screen.h"

void StartScreen::setup() {
  menu_font_.load("ARLRDBD.TTF", 32);
  name_font_.load("ARLRDBD.TTF", 24);
  title_font_.load("kindergarten.TTF", 64);
  rect_ = menu_font_.getStringBoundingBox(message_, 0, 0);
  box_width_ = rect_.width + 20;
  box_height_ = rect_.height + 30;
}

void StartScreen::update() {
  box_x_ = (ofGetWindowWidth() - rect_.width) / 2 - 10;
  box_y_ = 2 * (ofGetWindowHeight() - rect_.height) / 3 - 20;
}

void StartScreen::draw() {
  ofSetBackgroundColorHex(0xffffff);
  
  ofSetHexColor(0x78AB46);
  ofDrawRectRounded(box_x_, box_y_, box_width_, box_height_, 10);

  ofSetHexColor(0x000000);
  title_font_.drawString(title_, box_x_ - 130, ofGetWindowHeight() / 3);

  
  if (name_.size() > 0) {
    ofSetHexColor(0x000000);
    name_font_.drawString(std::string(name_.begin(), name_.end()), box_x_ -60, ofGetWindowHeight() / 2);
  } else {
    ofSetHexColor(0xd3d3d3);
    name_font_.drawString("Enter your name", box_x_ - 60, ofGetWindowHeight() / 2);
  }

  ofSetHexColor(0xffffff);
  menu_font_.drawString(message_, box_x_ + 10, 2 * ofGetWindowHeight() / 3);
}

bool StartScreen::MouseClick(int x, int y) {
  if (x >= box_x_ - 5 && x <= box_x_ + box_width_ && y >= box_y_ && y <= box_y_ + box_height_) {
    return true;
  }
  return false;
}

std::string StartScreen::KeyPress(int key)
{
  if (key == OF_KEY_RETURN) {
    if (name_.size() > 0) {
      return std::string(name_.begin(), name_.end());
    }
  } else if (key == OF_KEY_BACKSPACE && name_.size() > 0) {
    name_.pop_back();
  } else {
    name_.push_back(key);
  }
  return "";
}