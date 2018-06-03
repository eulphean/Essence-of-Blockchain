#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(ofColor::black);
  
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
  gui.add(partitionSize.setup("Update Partition Size", 10, 0, 64));
  gui.add(resetMinedTime.setup("Reset Mined Time", 3, 1, 20));
  fontSize.addListener(this, &ofApp::updateFromGui);
  gui.loadFromFile("ProofOfWork.xml");
  
  // Create the partition.
  createNewPartition();
  
  // Store current time.
  lastPartitionTime = ofGetElapsedTimef();
  lastMiningTime = ofGetElapsedTimef();
  
  // Fbo to draw the text in.
  textFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  textGlitch.setup(&textFbo);
}

//--------------------------------------------------------------
void ofApp::update(){
  ofSetFrameRate(frameRate);
  
  if (miningState == Mining) {
    createNewHash();
  }
  
  // Track mining state.
  if (miningState == Mining) {
    // Are we mining? Regularly update the partition. 
    if (ofGetElapsedTimef() - lastPartitionTime > resetPartitionTime) {
      createNewPartition();
      lastPartitionTime = ofGetElapsedTimef();
      resetPartitionTime = ofRandom(1, 5);
    }
  
    if (ofGetElapsedTimef() - lastMiningTime > resetMiningTime) {
      lastMinedTime = ofGetElapsedTimef(); // Start tracking mined time.
      cout << "Successfully mined." << endl;
      miningState = Mined;
      createNewPartition();
    }
  }
  
  if (miningState == Mined) {
    if (ofGetElapsedTimef() - lastMinedTime > resetMinedTime) {
      resetMiningTime = ofRandom(5, 10); // Calculate a new random mining time.
      lastMiningTime = ofGetElapsedTimef(); // Start tracking mining time.
      cout << "Beginning mining." << endl;
      miningState = Mining;
    }
  }

  drawTextFbo();
}

//--------------------------------------------------------------
void ofApp::draw(){
  /* Apply effects */
  textGlitch.generateFx();

  /* draw effected view */
  ofSetColor(255);
  textFbo.draw(0, 0);

  if (showGui) {
    gui.draw();
  }
}

void ofApp::drawTextFbo() {
  textFbo.begin();
    ofBackground(ofColor::black);
    // Draw every single character from the hash.
    int idx = 2;
    int curX = 0;
    ofPushMatrix();
      ofTranslate(xPosition, ofGetHeight()/2);
  
      // Draw the first 2 characters.
      characters[0].draw(ofToString('0'), curX, false);
      curX += characterSpacing;
      characters[1].draw(ofToString('x'), curX, false);
      curX += characterSpacing;

      for (auto c: ofToUpper(hash)) {
        // Check if this idx is in the updating partition.
        bool shouldUpdate = ofContains(updatePartition, idx);
        characters[idx].draw(ofToString(c), curX, shouldUpdate);
        curX += characterSpacing;
        idx++;
      }
    ofPopMatrix();
  textFbo.end();
}

void ofApp::createNewPartition() {
  updatePartition.clear();
  
  // Push a selective partition.
  if (miningState == Mining) {
    // Out of 64 numbers, choose 'partitionSize' random numbers.
    // Numbers start from index 2.
    while (updatePartition.size() < partitionSize) {
      int randomIdx = ofRandom(2, numCharacters);
      // Keep generating a random idx till we find one that's not
      // in the vector.
      while (ofContains(updatePartition, randomIdx)) {
        randomIdx = ofRandom(2, numCharacters);
      }
      updatePartition.push_back(randomIdx);
    }
  }
  
  // Push the entire character set.
  if (miningState == Mined) {
    for (int i = 2; i < numCharacters; i++) {
      updatePartition.push_back(i);
    }
  }
}

void ofApp::createCharacters() {
  characters.clear();
  
  // We have 64 characters.
  for (int i = 0; i < numCharacters; i++) {
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
  
  if (key == '1') textGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE  , true);
  if (key == '2') textGlitch.setFx(OFXPOSTGLITCH_GLOW      , true);
  if (key == '3') textGlitch.setFx(OFXPOSTGLITCH_SHAKER      , true);
  if (key == '4') textGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER    , true);
  if (key == '5') textGlitch.setFx(OFXPOSTGLITCH_TWIST      , true);
  if (key == '6') textGlitch.setFx(OFXPOSTGLITCH_OUTLINE    , true);
  if (key == '7') textGlitch.setFx(OFXPOSTGLITCH_NOISE      , true);
  if (key == '8') textGlitch.setFx(OFXPOSTGLITCH_SLITSCAN    , true);
  if (key == '9') textGlitch.setFx(OFXPOSTGLITCH_SWELL      , true);
  if (key == '0') textGlitch.setFx(OFXPOSTGLITCH_INVERT      , true);
}

void ofApp::keyReleased(int key) {
  if (key == '1') textGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE  , false);
  if (key == '2') textGlitch.setFx(OFXPOSTGLITCH_GLOW      , false);
  if (key == '3') textGlitch.setFx(OFXPOSTGLITCH_SHAKER      , false);
  if (key == '4') textGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER    , false);
  if (key == '5') textGlitch.setFx(OFXPOSTGLITCH_TWIST      , false);
  if (key == '6') textGlitch.setFx(OFXPOSTGLITCH_OUTLINE    , false);
  if (key == '7') textGlitch.setFx(OFXPOSTGLITCH_NOISE      , false);
  if (key == '8') textGlitch.setFx(OFXPOSTGLITCH_SLITSCAN    , false);
  if (key == '9') textGlitch.setFx(OFXPOSTGLITCH_SWELL      , false);
  if (key == '0') textGlitch.setFx(OFXPOSTGLITCH_INVERT      , false);
}

void ofApp::exit() {
  gui.saveToFile("ProofOfWork.xml");
}

