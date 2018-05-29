#pragma once

#include "ofMain.h"

enum Fade {
  In,
  Out
};

class Character {

	public:
    void setup(string font, float fontSize);
    void draw(string hash, int curX);
    int calculateAlpha();
 
  private:
    ofTrueTypeFont trueFont; // Loaded font.
    Fade fadeState = In; // Start by fading in. 
    long int lastTime;
    int fadeTime;
    string prevChar; 
};
