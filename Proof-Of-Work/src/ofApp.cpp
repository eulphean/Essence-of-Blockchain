#include "ofApp.h"
#include "Types.h"

// Declaring the extern mining state that gets used throughout
// the appl by all the modules.
State miningState = Mining;

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(ofColor::black);
  
  // Load background image.
  bgImage.load("wall.jpg");
  
  // Setup GUI.
  gui.setup();
  gui.add(appParameters);
  gui.add(block.parameters);
  gui.loadFromFile("ProofOfWork.xml");
  
  // Fbo to draw the text in.
  canvasFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  
  glitch.setup(&canvasFbo);
  
  // Mining tracker.
  lastMiningTime = ofGetElapsedTimef();
  
  // Initialize the printer.
  initPrinter();
  
  // Setup block
  block.setup();
  
  // Calculate time for the first transaction to occur.
  nextTransactionTime = calcNextTransactionTime(); // In 2 - 5 seconds, first transaction happens.
  lastTransactionTime = ofGetElapsedTimeMillis();
  
  // Start the first section for the block.
  printer.cut(ESCPOS::BaseCodes::CUT_FULL);
  printBoundingSection('x');
}

//--------------------------------------------------------------
void ofApp::update(){
  ofSetFrameRate(frameRate);
  
  // Update block
  block.update(canvasFbo, bgImage);
  
  // Track mining state.
  if (miningState == Mining) {  
    
    // Mining done? Update state to mined.
    if (ofGetElapsedTimef() - lastMiningTime > resetMiningTime) {
      lastMinedTime = ofGetElapsedTimef(); // Start tracking mined time.
      block.updateCharacterPartition(); // All the characters should update now.
      
      // Clear previous transactions, get ready for the next block.
      confirmedTransactions.clear();
      
      // Block is successfully mined. Engage the printer.
      miningState = Mined;
      
      // Print block.
      block.print(printer);
      // End the block.
      printBoundingSection('x');
      printer.cut(ESCPOS::BaseCodes::CUT_FULL);
    }
    
    // Check if it's time for a transaction.
    if (ofGetElapsedTimeMillis() - lastTransactionTime > nextTransactionTime) {
      // Reset transaction times.
      lastTransactionTime = ofGetElapsedTimeMillis();
      nextTransactionTime = calcNextTransactionTime();
      
      // Create a transaction. 
      Transaction tx;
      confirmedTransactions.push_back(tx);
      
      // Print transaction.
      tx.print(printer);
    }
  }
  
  if (miningState == Mined) {
    // Mined visualization done? Update state to mining.
    if (ofGetElapsedTimef() - lastMinedTime > resetMinedTime) {
      resetMiningTime = ofRandom(15, 25); // Calculate a new random mining time.
      lastMiningTime = ofGetElapsedTimef(); // Start tracking mining time.
      miningState = Mining;
      
      // Reset transaction times.
      lastTransactionTime = ofGetElapsedTimef();
      nextTransactionTime = calcNextTransactionTime();
      
      // Start a new block.
      printBoundingSection('x');
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  if (miningState == Mining) {
    glitch.setFx(OFXPOSTGLITCH_CUTSLIDER, true);
    glitch.setFx(OFXPOSTGLITCH_NOISE, true);
    glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, false);
//    glitch.setFx(OFXPOSTGLITCH_SLITSCAN, true);
    //glitch.setFx(OFXPOSTGLITCH_INVERT, true);
    //textGlitch.setFx(OFXPOSTGLITCH_OUTLINE, true);
    glitch.setFx(OFXPOSTGLITCH_GLOW, false);
  }
  
  if (miningState == Mined) {
//    glitch.setFx(OFXPOSTGLITCH_SLITSCAN, false);
    glitch.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
    glitch.setFx(OFXPOSTGLITCH_NOISE, false);
    glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
    //glitch.setFx(OFXPOSTGLITCH_INVERT, false);
    //textGlitch.setFx(OFXPOSTGLITCH_OUTLINE, false);
    glitch.setFx(OFXPOSTGLITCH_GLOW, true);
  }
  
  /* Apply effects */
  glitch.generateFx();
  float alpha = ofMap(ofGetElapsedTimef() - lastMiningTime, 0, resetMiningTime, 10, 255, true);
  ofSetColor(255, 255, 255, alpha);
  canvasFbo.draw(0, 0);

  if (showGui) {
    gui.draw();
  }
}

int ofApp::calcNextTransactionTime() {
  return ofRandom(100, 1200); // Milliseconds
}

void ofApp::initPrinter() {
    // We can get all of the connected serial devices using the
    // ofxIO::SerialDeviceUtils::listDevices() static method.
    //
    auto devices = ofxIO::SerialDeviceUtils::listDevices();
  
    std::cout << devices[0].port();
  
    // Connect to the first available port.
    // Conform that this is the one you want.
    if (!printer.setup(38400))
    {
        ofLogError("ofApp::setup") << "Unable to connect to: " << printer.port();
        ofExit();
    }
    else
    {
        ofLogNotice("ofApp::setup") << "Connected to: " << printer.port();
    }
  
    // Set up hardware flow control if needed.
    printer.setDataTerminalReady();
    printer.setRequestToSend();
  
    // Initialize the printer.
    printer.initialize();
    printer.flush();
  
    // Invert the text.
    printer.setCharacterSize(ESCPOS::BaseCodes::MAGNIFICATION_1X,
                             ESCPOS::BaseCodes::MAGNIFICATION_1X);
    printer.setUpsideDown(true);
    printer.setAlign(ESCPOS::BaseCodes::ALIGN_LEFT);
}

void ofApp::printBoundingSection(char c) {
  printer.setInvert(false);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_LEFT);
  
  string currentLine = ofToString(c);
  for (int i = 0; i < 46; i++) {
    currentLine += '-';
  }
  currentLine += c;
  
  printer.println(currentLine);
  return currentLine;

}

void ofApp::keyPressed(int key) {
  if (key == OF_KEY_RIGHT) {
    block.cycleFont(true);
  }
  
  if (key == OF_KEY_LEFT) {
    block.cycleFont(false);
  }
  
  if (key == 'h') {
    showGui = !showGui;
  }
  
  if (key == '1') glitch.setFx(OFXPOSTGLITCH_CONVERGENCE  , true);
  if (key == '2') glitch.setFx(OFXPOSTGLITCH_GLOW      , true);
  if (key == '3') glitch.setFx(OFXPOSTGLITCH_SHAKER      , true);
  if (key == '4') glitch.setFx(OFXPOSTGLITCH_CUTSLIDER    , true);
  if (key == '5') glitch.setFx(OFXPOSTGLITCH_TWIST      , true);
  if (key == '6') glitch.setFx(OFXPOSTGLITCH_OUTLINE    , true);
  if (key == '7') glitch.setFx(OFXPOSTGLITCH_NOISE      , true);
  if (key == '8') glitch.setFx(OFXPOSTGLITCH_SLITSCAN    , true);
  if (key == '9') glitch.setFx(OFXPOSTGLITCH_SWELL      , true);
  if (key == '0') glitch.setFx(OFXPOSTGLITCH_INVERT      , true);
}

void ofApp::keyReleased(int key) {
  if (key == '1') glitch.setFx(OFXPOSTGLITCH_CONVERGENCE  , false);
  if (key == '2') glitch.setFx(OFXPOSTGLITCH_GLOW      , false);
  if (key == '3') glitch.setFx(OFXPOSTGLITCH_SHAKER      , false);
  if (key == '4') glitch.setFx(OFXPOSTGLITCH_CUTSLIDER    , false);
  if (key == '5') glitch.setFx(OFXPOSTGLITCH_TWIST      , false);
  if (key == '6') glitch.setFx(OFXPOSTGLITCH_OUTLINE    , false);
  if (key == '7') glitch.setFx(OFXPOSTGLITCH_NOISE      , false);
  if (key == '8') glitch.setFx(OFXPOSTGLITCH_SLITSCAN    , false);
  if (key == '9') glitch.setFx(OFXPOSTGLITCH_SWELL      , false);
  if (key == '0') glitch.setFx(OFXPOSTGLITCH_INVERT      , false);
}

void ofApp::exit() {
  gui.saveToFile("ProofOfWork.xml");
}

