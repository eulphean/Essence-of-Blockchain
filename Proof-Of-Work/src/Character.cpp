#include "Character.h"

void Character::setup(string font, float fontSize) {
  // Setup ofTrueTypeFont
  trueFont.load(font, fontSize);
}

void Character::draw(string c, int curX) {
  // Draw the characters.
  ofPushMatrix();
  ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(ofColor::black);
    trueFont.drawString(c, curX, 0);
    ofDisableAlphaBlending();
  ofPopStyle();
  ofPopMatrix();
}
