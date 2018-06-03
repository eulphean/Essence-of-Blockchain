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
    ofxIntSlider partitionSize;
    ofxFloatSlider xPosition;
  
    // Flags
    bool showGui = true;
  
    // A partition of integers that will keep updating with the
    // new hash while other stay stagnant. Size of the partition
    // is decided by 'partitionSize' integer in GUI. This is to
    // extract the constantly updating, iterating, thinking quality
    // of the mining process. 
    vector<int> updatePartition;
    long int resetPartitionTime = 1; // Starting with 2 seconds. Updates
                                     // everytime the partition gets updated.
    long int lastTime; 
};
