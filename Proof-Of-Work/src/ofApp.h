#pragma once

#include "ofMain.h"
#include "sha256.h"
#include "ofxGui.h"
#include "Character.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void keyPressed(int key);
  
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
    int currentFontIdx = 0;
  
    // GUI
    ofxPanel gui;
    ofxFloatSlider fontSize;
    ofxFloatSlider characterSpacing;
    ofxIntSlider frameRate;
    ofxFloatSlider xPosition;
  
    // Flags
    bool showGui = true;
  
    bool hasDrawn = false;
};


//    // Test font.
//    ofTrueTypeFont testFont;
//    int alpha = 0; // Max value is 255.
//    long int fadeInTime = 1000;
//    long int fadeOutTime = 1000;
//    bool shouldFadeOut = false;
