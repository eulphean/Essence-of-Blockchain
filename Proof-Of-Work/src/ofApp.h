#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Character.h"
#include "ofxPostGlitch.h"
#include "ofxESCPOS.h"
#include "BlockHash.h"
#include "Transaction.h"

using namespace ofx;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void keyPressed(int key);
    void keyReleased(int key);
  
    int calcNextTransactionTime();
    void initPrinter();
    void exit();
  
  private:
    void printBoundingSection(char c);
  
    // GUI
    ofxPanel gui;
    ofParameter<int> frameRate { "Frame Rate", 5, 1, 60 };
    ofParameter<int> resetMinedTime { "Reset Mined Time", 3, 1, 20 }; // Time we want to hold before we start mining again.
    ofParameterGroup appParameters { "Mining", frameRate, resetMinedTime };
  
    ofImage bgImage;
  
    // Flags
    bool showGui = true;
  
    // Text glitch. 
    ofxPostGlitch glitch;
  
    unsigned long int resetMiningTime = 10; // This is randomly between 5-10 seconds right now.
                              // In reality, it's around 15-20 seconds.
    unsigned long int lastMiningTime;
    unsigned long int lastMinedTime;
  
    // Thermal printer.
    ESCPOS::DefaultSerialPrinter printer;
  
    // Block
    BlockHash block;
  
    // Transaction (Track time in milliseconds because we need higher precision)
    vector<Transaction> confirmedTransactions;
    unsigned long nextTransactionTime; // (ms) Randomly decide this after every confirmed transaction
    unsigned long lastTransactionTime;
  
    // App-level fbo
    ofFbo canvasFbo;
};
