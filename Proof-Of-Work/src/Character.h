#pragma once

#include "ofMain.h"

class Character {

	public:
    void setup(string font, float fontSize);
    void draw(string hash, int curX);
 
  private:
    ofTrueTypeFont trueFont; // Loaded font.
};
