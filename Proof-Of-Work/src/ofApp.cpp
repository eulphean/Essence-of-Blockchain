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
  gui.add(xPosition.setup("X Position", 50, -ofGetWidth(), ofGetWidth()));
  fontSize.addListener(this, &ofApp::updateFromGui);
  gui.loadFromFile("ProofOfWork.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
  ofSetFrameRate(frameRate);
  if (!hasDrawn) {
    createNewHash();
    //hasDrawn = true;
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Draw every single character from the hash. 
  int idx = 0;
  int curX = 0;
  ofPushMatrix();
    ofTranslate(xPosition, ofGetHeight()/2);
    for (auto c: ofToUpper(hash)) {
      characters[idx].draw(ofToString(c), curX);
      curX += characterSpacing;
    }
  ofPopMatrix();
  
  if (showGui) {
    gui.draw();
  }

}

void ofApp::createCharacters() {
  characters.clear();
  
  // We have 64 characters.
  for (int i = 0; i < 64; i++) {
    Character c;
    c.setup(fonts[currentFontIdx], fontSize);
    characters.push_back(c);
  }
}

void ofApp::createNewHash() {
   // Keep pushing a new character to this vector to generate a new hash.
  hashString.push_back('a');
  
  // Empty the vector when the size becomes really big.
  if (hashString.size() > 50) {
    hashString.clear();
  }
  
  // Extract a SHA256 hash from the string.
  hash = sha256 (ofToString(hashString));
}


// Callback for any GUI updates.
void ofApp::updateFromGui(float &val) {
  createCharacters();
}

void ofApp::keyPressed(int key) {
  if (key == OF_KEY_RIGHT) {
    // Wrapp current font idx.
    currentFontIdx = (currentFontIdx + 1) % fonts.size();
    createCharacters();
  }
  
  if (key == OF_KEY_LEFT) {
    // Wrap current font idx.
    if ((currentFontIdx - 1) < 0) {
      currentFontIdx = fonts.size() - 1;
    } else {
      currentFontIdx--;
    }
    createCharacters();
  }
  
  if (key == 'h') {
    showGui = !showGui;
  }
}

void ofApp::exit() {
  gui.saveToFile("ProofOfWork.xml");
}

