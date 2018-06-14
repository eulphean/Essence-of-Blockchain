#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Character.h"
#include "ofxPostGlitch.h"
#include "ofxESCPOS.h"
#include "BlockHash.h"

using namespace ofx;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void keyPressed(int key);
    void keyReleased(int key);
  
    void initPrinter();
    void printBlockCreation();
    void exit();
  
  private:  
    // GUI
    ofxPanel gui;
    ofParameter<int> frameRate { "Frame Rate", 5, 1, 60 };
    ofParameter<int> resetMinedTime { "Reset Mined Time", 3, 1, 20 }; // Time we want to hold before we start mining again.
    ofParameterGroup appParameters { "Mining", frameRate, resetMinedTime };
  
    // Flags
    bool showGui = true;
    bool engagePrinter = false;
  
    // Text glitch. 
    ofxPostGlitch glitch;
  
    long int resetMiningTime = 5; // This is randomly between 5-10 seconds right now.
                              // In reality, it's around 15-20 seconds.
    long int lastMiningTime;
    long int lastMinedTime;
  
    // Thermal printer.
    ESCPOS::DefaultSerialPrinter printer;
  
    // Block
    BlockHash block;
  
    // App-level fbo
    ofFbo canvasFbo;
};
