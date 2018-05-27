#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  ofSetFrameRate(15);
  
  
  // Collect all the fonts.
  fonts.push_back("betong.ttf");
  fonts.push_back("antaro.ttf");
  fonts.push_back("bellada.ttf");
  fonts.push_back("chengis.otf");
  fonts.push_back("consequences.ttf");
  fonts.push_back("kingdom.ttf");
  fonts.push_back("schaeffer.ttf");
  fonts.push_back("xminus.ttf");
  fonts.push_back("yonder.ttf");
  fonts.push_back("keys.ttf");
  fonts.push_back("fresty.ttf");
  fonts.push_back("giovanni.ttf");
  fonts.push_back("viksi.ttf");
  
  // Load the first font.
  myFont.load(fonts[currentFontIdx], fontSize);
  
  xPos = ofGetWidth()/2;
}

//--------------------------------------------------------------
void ofApp::update(){
  // Keep pushing a new character to this vector to generate a new hash.
  hashString.push_back('a');
  
  // Empty the vector when the size becomes really big.
  if (hashString.size() > 50) {
    hashString.clear();
  }
  
  // Extract a SHA256 hash from the string.
  hash = sha256 (ofToString(hashString));
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(ofColor::white);
  string toShow = "0x" + hash;
  
  // Calculate the x position to print the string at.
  ofPushMatrix();
  ofTranslate(xPos, ofGetHeight()/2);
  myFont.drawString(toShow, 0, 0);
  ofPopMatrix();
  float stringSize = myFont.stringWidth(toShow);
  xPos = ofGetWidth()/2 - stringSize/2;

}

void ofApp::keyPressed(int key) {
  if (key == OF_KEY_UP) {
    fontSize++;
  }
  
  if (key == OF_KEY_DOWN) {
    fontSize--;
  }
  
  if (key == OF_KEY_RIGHT) {
    // Wrapp current font idx.
    currentFontIdx = (currentFontIdx + 1) % fonts.size();
  }
  
  if (key == OF_KEY_LEFT) {
    // Wrap current font idx.
    if ((currentFontIdx - 1) < 0) {
      currentFontIdx = fonts.size() - 1;
    } else {
      currentFontIdx--;
    }
  }
  
  std::cout << fonts[currentFontIdx] << endl;

  // Reload font.
  myFont.load(fonts[currentFontIdx], fontSize);
}

// Change the size of the text
// Load a font desired for this. 
