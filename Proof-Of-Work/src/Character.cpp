#include "Character.h"

void Character::setup(string font, float fontSize) {
  // Setup ofTrueTypeFont
  trueFont.load(font, fontSize);
  lastTime = ofGetElapsedTimef(); // Store the current time.
  fadeTime = ofRandom(1, 5);
}

void Character::draw(string c, int curX) {
  // Draw the characters.
  ofPushMatrix();
  ofPushStyle();
    ofEnableAlphaBlending();
    //int alpha = calculateAlpha();
    int alpha = 255; 
    ofSetColor(ofColor::black, alpha);
    trueFont.drawString(c, curX, 0);
    ofDisableAlphaBlending();
  ofPopStyle();
  ofPopMatrix();
}

int Character::calculateAlpha() {
  long int elapsedTime = ofGetElapsedTimef() - lastTime;
  int alpha;
  if (fadeState == In) {
    alpha = ofMap(elapsedTime, 0, fadeTime, 127, 255, true);
    if (alpha == 255) { // Fade-In complete.
      fadeState = Out; // Transition state.
      lastTime = ofGetElapsedTimef(); // Save last time.
    }
  } else {
    alpha = ofMap(elapsedTime, 0, fadeTime, 255, 0, true);
    if (alpha == 0) { // Fade-Out complete.
      fadeState = In; // Transition state.
      lastTime = ofGetElapsedTimef(); // Save last time.
    }
  }
  
  return alpha;
}

//long int elapsedTime = ofGetElapsedTimeMillis();
//  if (shouldFadeOut) {
//    alpha = ofMap(elapsedTime, 0, fadeOutTime, 255, 0, true);
//    if (alpha == 0) {
//      shouldFadeOut = false; // Now, fade in.
//      ofResetElapsedTimeCounter(); // Reset time
//    }
//  } else {
//    alpha = ofMap(elapsedTime, 0, fadeInTime, 0, 255, true);
//    if (alpha == 255) {
//      // Completely faded in.
//      shouldFadeOut = true; // Now, fade out
//      ofResetElapsedTimeCounter(); // Reset time for next phase.
//    }
//  }
