#include "ofApp.h"

void ofApp::DrawLobby(){
}

void ofApp::DrawGame(){
}

//--------------------------------------------------------------
void ofApp::setup(){
  if (current_state_ == START) {
    start_.setup();
  } else if (current_state_ == LOBBY) {
    lobby_.setup();
  } else if (current_state_ == IN_PROGRESS) {
    std::cout << "setup gameplay" << std::endl;
    gameplay_.setup();
    gameplay_.update();
    time_ = ofGetElapsedTimeMillis();
  }
}

//--------------------------------------------------------------
void ofApp::update(){
  if (current_state_ == START) {
    start_.update();
  } else if (current_state_ == LOBBY) {
    lobby_.update();
  } else if (current_state_ == IN_PROGRESS) {
    uint64_t new_time = ofGetElapsedTimeMillis();
    if (new_time - time_ >= 50) {
      gameplay_.update();
      time_ = new_time;
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  if (current_state_ == START) {
    start_.draw();
  } else if (current_state_ == LOBBY) {
    lobby_.draw();
  } else if (current_state_ == IN_PROGRESS) {
    gameplay_.draw();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (current_state_ == LOBBY && key == OF_KEY_BACKSPACE) {
    current_state_ = START;
    setup();
  }
  else if (current_state_ == IN_PROGRESS && (
      (key >= 'a' && key <= 'z') ||
      (key >= 'A' && key <= 'Z') ||
      (key >= '0' && key <= '9') ||
      (key == OF_KEY_RETURN) ||
      (key == OF_KEY_BACKSPACE) ||
      (key == ' ')
    )) {
    gameplay_.KeyPress(key);
  }
  else if (current_state_ == START && (
    (key >= 'a' && key <= 'z') ||
    (key >= 'A' && key <= 'Z') ||
    (key >= '0' && key <= '9') ||
    (key == OF_KEY_RETURN) ||
    (key == OF_KEY_BACKSPACE)
    )) {
    std::string name = start_.KeyPress(key);
    if (name.length() > 0) {
      current_state_ = IN_PROGRESS;
      gameplay_.SetName(name);
      setup();
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  if (current_state_ == IN_PROGRESS) {
    gameplay_.MouseMoved(x,y);
  }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  if (current_state_ == IN_PROGRESS) {
    gameplay_.MouseDraw(10,x,y);
  }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  if (current_state_ == START) {
    if (start_.MouseClick(x, y)) {
      current_state_ = IN_PROGRESS;
      setup();
    }
  }
  if (current_state_ == LOBBY) {
    if (lobby_.MouseClick(x, y)) {
      current_state_ = START;
      setup();
    }
  }
  if (current_state_ == IN_PROGRESS) {
    std::cout << "Drawing" << std::endl;
    gameplay_.MouseClick(x, y);
  }
  update();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
