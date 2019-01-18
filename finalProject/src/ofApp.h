#pragma once

#include <iostream>
#include "ofMain.h"
#include "gui/start_screen.h"
#include "gui/lobby.h"
#include "gui/gameplay.h"

enum GameState {
  START,
  LOBBY,
  IN_PROGRESS,
  FINISHED
};

class ofApp : public ofBaseApp{
  private:
    GameState current_state_ = START;
    ofTrueTypeFont menu_font_;

    void DrawLobby();
    void DrawGame();

    StartScreen start_;
    Lobby lobby_;
    Gameplay gameplay_;

    uint64_t time_;
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
