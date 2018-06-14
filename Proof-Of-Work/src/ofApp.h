#pragma once

#include "ofMain.h"
#include "sha256.h"
#include "ofxGui.h"
#include "Character.h"
#include "ofxPostGlitch.h"
#include "ofxESCPOS.h"

using namespace ofx;

enum State {
  Mining,
  Mined
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void keyPressed(int key);
    void keyReleased(int key);
  
    void initPrinter();
    void printBlockCreation();
    void drawTextFbo();
    void createNewPartition();
    void createNewHash();
    void createCharacters();
    void updateFromGui(float &val);
    void exit();
  
  private:
    // Hashing.
    SHA256 sha256; // SHA-256 utility to generate hashes.
    std::vector<char> hashString;
    string hash;
  
    // Characters.
    std::vector<Character> characters;
    std::vector<string> fonts;
    int currentFontIdx = 3;
    const int numCharacters = 66; // OX + 64 character hash.
  
    // GUI
    ofxPanel gui;
    ofxFloatSlider fontSize;
    ofxFloatSlider characterSpacing;
    ofxIntSlider frameRate;
    ofxIntSlider resetMinedTime; // Time we want to hold before we start mining again. 
    ofxIntSlider partitionSize;
    ofxFloatSlider xPosition;
  
    // Flags
    bool showGui = true;
    bool engagePrinter = false;
  
    // A partition of integers that will keep updating with the
    // new hash while other stay stagnant. Size of the partition
    // is decided by 'partitionSize' integer in GUI. This is to
    // extract the constantly updating, iterating, thinking quality
    // of the mining process. 
    vector<int> updatePartition;
    long int resetPartitionTime = 1; // Starting with 2 seconds. Updates
                                     // everytime the partition gets updated.
    long int lastPartitionTime;
  
    // Text glitch. 
    ofxPostGlitch textGlitch;
    ofFbo textFbo;
  
    State miningState = Mining; // We begin with a mining state.
    long int resetMiningTime = 5; // This is randomly between 5-10 seconds right now.
                              // In reality, it's around 15-20 seconds.
    long int lastMiningTime;
    long int lastMinedTime;
  
    // Thermal printer.
    ESCPOS::DefaultSerialPrinter printer;
};
