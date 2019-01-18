#include "gameplay.h"

using std::string;
using std::vector;

void Gameplay::setup()
{
  // Loads fonts and images
  menu_font_.load("ARLRDBD.TTF", 16);
  medium_font_.load("ARLRDBD.TTF", 18);
  title_font_.load("ARLRDBD.TTF", 24);
  pencil_.load("images/bw-pencil.png");
  timer_.load("images/alarm-clock.png");
  timer_.resize(100, 100);

  // Sets up drawing panel
  black_.setHex(0x000000);
  panel_.set(100, 100, 500, 500);
  ofSetBackgroundColorHex(0xd3560e);

  // Sets colors
  colors_ = vector<ofColor>(10);
  colors_[0].setHex(0xffffff);
  colors_[1].setHex(0x000000);
  colors_[2].setHex(0xa52a2a);
  colors_[3].setHex(0xff0000);
  colors_[4].setHex(0xffa500);
  colors_[5].setHex(0xffff00);
  colors_[6].setHex(0x9acd32);
  colors_[7].setHex(0x008000);
  colors_[8].setHex(0x0000ff);
  colors_[9].setHex(0x800080);
  color_picker_loc_.set(100, 650);

  // Connects client to server
  if (client_.Connect(name_) == 1) {
    std::cerr << "Couldn't connect." << endl;
  } else {
    client_.SetNumPlayers();
  }
}

void Gameplay::update()
{
  // Gets game info
  client_.UpdateGameInfo(); // Updates game info in the client
  client_.SetNumPlayers();
  client_.UpdatePlayers();
  scores_ = client_.GetScores();
  names_ = client_.GetNames();

  // Gets drawing info
  if (client_.getId() == client_.GetCurrPlayer()) {
    client_.SetLines(lines_);
    client_.SetColors(line_colors_);
  }
  else {
    lines_ = client_.GetLines();
    line_colors_ = client_.GetColors();
  }

  // Updates when players take turns
  if (curr_player_ != client_.GetCurrPlayer() || round_ != client_.GetRound()) {
    std::cout << "Changed player" << std::endl;

    curr_player_ = client_.GetCurrPlayer();
    round_ = client_.GetRound();

    lines_.clear();
    line_colors_.clear();
    client_.SetLines(lines_);
    guessed_word_.clear();
    guessed_ = false;
    word_ = client_.GetWord();

    if (client_.getId() == client_.GetCurrPlayer()) {
      ofHideCursor();
    } else {
      ofShowCursor();
    }
  }
  
}

void Gameplay::SetName(string name)
{
  name_ = name;
}

void Gameplay::updateNumPlayers()
{
  client_.SetNumPlayers();
}

void Gameplay::draw()
{
  // Draws player scores and current player's turn
  ostringstream scores;
  ofSetHexColor(0xffffff);
  if (client_.GetRound() == 0) {
    medium_font_.drawString("Waiting for players" , 700, 50);
  } else {
    medium_font_.drawString("Round " + std::to_string(client_.GetRound()), 700, 50);
  }
  
  scores << "Scores: \n\n";
  for (int i = 0; i < scores_.size(); i++) {
    scores << names_[i];
    if (client_.getId() == i) {
      scores << " (You)";
    }
    scores << " : " << scores_[i] << "\n\n";
  }
  scores << "Player currently drawing: \n" << names_[client_.GetCurrPlayer()];
  menu_font_.drawString(scores.str(), 700, 115); // Font is ~15 pixels high
  ofSetHexColor(0x000000);
  medium_font_.drawString(std::to_string(client_.GetTime()), 100, 50);

  // Draws drawing panel and player's drawing
  ofSetHexColor(0xffffff);
  ofDrawRectangle(panel_);
  ofSetColor(black_);
  for (int i = 0; i < lines_.size(); i++) {
    ofSetColor(colors_[line_colors_[i]]);
    lines_[i].draw();
  }

  // Writes player's guess
  if (guessed_) {
    ofSetHexColor(0x66CD00);
  } else {
    ofSetColor(black_);
  }
  title_font_.drawString(string(guessed_word_.begin(), guessed_word_.end()), 100, 650);

  // Draws word and color selector or underscores based on whether the player is currently drawing
  ofSetHexColor(0xffffff);
  if (client_.getId() == client_.GetCurrPlayer()) {
    // Draws color selector
    for (int i = 0; i < colors_.size(); i++) {
      ofRectangle box;
      box.setPosition(color_picker_loc_.x + i * 50, color_picker_loc_.y);
      box.setSize(50, 50);
      ofSetColor(colors_[i]);
      ofDrawRectangle(box);
    }

    ofSetHexColor(0xffffff);
    pencil_.draw(mouse_loc_.x, mouse_loc_.y - pencil_.getHeight());
    title_font_.drawString(word_, 300, 50);

  } else if (guessed_) {
    ofSetHexColor(0x66CD00);
    title_font_.drawString(word_, 300, 50);
  } else {
    ostringstream spaced_hint;
    string hint = client_.GetHint();
    for (int i = 0; i < hint.length(); i++) {
      spaced_hint << hint[i] << " ";
    }
    title_font_.drawString(spaced_hint.str(), 300, 50);
  }

  ofSetHexColor(0xffffff);
  timer_.draw(65, -15);
}

// Draws a thicker line like a paintbrush
// Taken from GitHub drawing example:
// https://github.com/ofZach/drawing-examples/blob/master/thickness/src/testApp.cpp
void Gameplay::Paint(ofPolyline line) {
  ofMesh meshy;
  meshy.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

  float widthSmooth = 10;
  float angleSmooth;

  for (int i = 0; i < line.getVertices().size(); i++) {

    int me_m_one = i - 1;
    int me_p_one = i + 1;
    if (me_m_one < 0) me_m_one = 0;
    if (me_p_one == line.getVertices().size()) me_p_one = line.getVertices().size() - 1;

    ofPoint diff = line.getVertices()[me_p_one] - line.getVertices()[me_m_one];
    float angle = atan2(diff.y, diff.x);

    if (i == 0) angleSmooth = angle;
    else {
      angleSmooth = ofLerpDegrees(angleSmooth, angle, 1.0);
    }


    float dist = diff.length();

    float w = ofMap(dist, 0, 20, 40, 2, true);

    widthSmooth = 0.9f * widthSmooth + 0.1f * w;

    ofPoint offset;
    offset.x = cos(angleSmooth + PI / 2) * widthSmooth;
    offset.y = sin(angleSmooth + PI / 2) * widthSmooth;

    meshy.addVertex(line.getVertices()[i] + offset);
    meshy.addVertex(line.getVertices()[i] - offset);
  }

  ofSetColor(0, 0, 0);
  meshy.draw();
  /*ofSetColor(100, 100, 100);
  meshy.drawWireframe();*/
}

void Gameplay::Fill(int x, int y) {

}

void Gameplay::KeyPress(int key)
{
  if (client_.getId() == client_.GetCurrPlayer() || guessed_) {
    return;
  }
  std::cout << "Key: " << key << std::endl;
  if (key == OF_KEY_RETURN) {
    string word(guessed_word_.begin(), guessed_word_.end());
    std::cout << "Word: " << word << std::endl;
    guessed_ = client_.CheckWord(word);
    guessed_word_.clear();
  } else if(key == OF_KEY_BACKSPACE && guessed_word_.size() > 0) {
    guessed_word_.pop_back();
  } else {
    guessed_word_.push_back(key);
  }
}

void Gameplay::MouseDraw(int size, int x, int y)
{
  // Doesn't allow player to draw if it's not their turn
  if (client_.getId() != client_.GetCurrPlayer()) {
    return;
  }
  if (x < panel_.getRight() && x > panel_.getLeft() && y < panel_.getBottom() && y > panel_.getTop()) {
    lines_[lines_.size() - 1].addVertex(ofPoint(x, y));
  }
   else {
    std::cout << "Out of bounds" << std::endl;
  }

  // Updates mouse position when mouse is pressed down
  mouse_loc_.x = x;
  mouse_loc_.y = y;
}

void Gameplay::MouseClick(int x, int y)
{
  // Creates a new polyline if the mouse is clicked
  if (client_.getId() != client_.GetCurrPlayer()) {
    return;
  }
  if (y >= color_picker_loc_.y && y <= color_picker_loc_.y + 50) {
    int color = (x - color_picker_loc_.x) / 50;
    if (color >= 0 && color < colors_.size()) {
      curr_color_ = color;
    }
  }
  else if (x >= panel_.getLeft() && x <= panel_.getRight() && y >= panel_.getTop() && y <= panel_.getBottom()) {
    ofPolyline line;
    lines_.push_back(line);
    line_colors_.push_back(curr_color_);
  }
}

void Gameplay::MouseMoved(int x, int y) {
  // Updates mouse position when it is not pressed down
  mouse_loc_.x = x;
  mouse_loc_.y = y;
}