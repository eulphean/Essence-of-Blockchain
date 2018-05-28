#pragma once

#include "ofMain.h"
#include "sha256.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void keyPressed(int key);
    void populateFonts();
    void updateFonts(float &newVal); 
    void exit();
  
  private:
    bool showGui = true;
  
    SHA256 sha256; // SHA-256 utility to generate hashes. 
  
    std::vector<char> hashString;
    string hash;
  
    std::vector<ofTrueTypeFont> myFonts;
    std::vector<string> fonts;
    int currentFontIdx = 0;
  
    float xPos;
  
    // GUI
    ofxPanel gui;
    ofxFloatSlider fontSize;
    ofxFloatSlider characterSpacing;
    ofxIntSlider frameRate;
    ofxFloatSlider xPosition;
};
