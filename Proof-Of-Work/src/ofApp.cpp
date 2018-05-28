#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(ofColor::red);
  
  // Collect all the fonts.
  fonts.push_back("betong.ttf");
  fonts.push_back("jmt.otf");
  fonts.push_back("perfect.otf");
  fonts.push_back("chengis.otf");
  fonts.push_back("schaeffer.ttf");
  fonts.push_back("keys.ttf");
  fonts.push_back("giovanni.ttf");
  
  // Setup GUI.
  gui.setup();
  gui.add(fontSize.setup("Font Size", 15, 5, 100));
  gui.add(characterSpacing.setup("Character Spacing", 10, 5, 50));
  gui.add(frameRate.setup("Frame Rate", 5, 1, 60));
  gui.add(xPosition.setup("X Position", 50, 0, ofGetWidth()/2));
  fontSize.addListener(this, &ofApp::updateFonts);
  gui.loadFromFile("ProofOfWork.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
  ofSetFrameRate(frameRate);
  
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
  string toShow = hash;
  
  // Draw the characters.
  int idx = 0;
  int curX = 0;
  ofPushMatrix();
  ofPushStyle();
    ofSetColor(ofColor::black);
    ofTranslate(xPosition, ofGetHeight()/2);
    for (auto &c: ofToUpper(hash)) {
      myFonts[idx].drawString(ofToString(c), curX, 0);
      curX += characterSpacing; // Each character is 5px apart.
    }
  ofPopStyle();
  ofPopMatrix();
  
  
  if (showGui) {
    gui.draw();
  }
}

// Callback from GUI.
void ofApp::updateFonts(float &val) {
  populateFonts();
}

void ofApp::populateFonts() {
  // Populate the vector of font.
  myFonts.clear();
  
  for (int i = 0; i < 64; i++) {
    ofTrueTypeFont font;
    font.load(fonts[currentFontIdx], fontSize);
    myFonts.push_back(font);
  }
}

void ofApp::keyPressed(int key) {
  if (key == OF_KEY_RIGHT) {
    // Wrapp current font idx.
    currentFontIdx = (currentFontIdx + 1) % fonts.size();
    populateFonts();
  }
  
  if (key == OF_KEY_LEFT) {
    // Wrap current font idx.
    if ((currentFontIdx - 1) < 0) {
      currentFontIdx = fonts.size() - 1;
    } else {
      currentFontIdx--;
    }
    
    populateFonts();
  }
  
  if (key == 'h') {
    showGui = !showGui;
  }
}

void ofApp::exit() {
  gui.saveToFile("ProofOfWork.xml");
}

