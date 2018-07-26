#pragma once

#include "ofParameter.h"
#include "ofParameterGroup.h"
#include "ofMain.h"
#include "Character.h"
#include "Types.h"
#include "sha256.h"
#include "ofxESCPOS.h"

using namespace ofx;

class BlockHash {
  public:
    void setup();
    void update(ofFbo &fbo, ofImage &img);
    void print(ESCPOS::DefaultSerialPrinter printer); // Prints the Blockchain.
  
    // GUI parameters.
    ofParameter<float> characterSpacing { "Character Spacing", 10.0, 5.0, 50.0 };
    ofParameter<int> partitionSize { "Update partition size", 10, 0, 64 };
    ofParameter<float> xPosition { "X Position", 50, -ofGetWidth(), ofGetWidth() };
    ofParameter<int> fontSize { "Font Size", 15, 5, 100 };
  
    // GUI group.
    ofParameterGroup parameters { "Block Hash", characterSpacing, partitionSize, xPosition, fontSize };
  
    void updateCharacterPartition();
    void cycleFont(bool forward);
  
  private:
    // Printing functions.
    string printBoundingSection(ESCPOS::DefaultSerialPrinter printer, char c);
    string printAddress(ESCPOS::DefaultSerialPrinter printer, int start, int end);
  
    void updateFromGui(int & val);
    void createCharacters();
    void updateHashFbo(ofFbo &fbo, ofImage &img);
    
    // Fonts
    std::vector<string> fonts;
    int currentFontIdx = 3;
  
    // Font characters.
    std::vector<Character> characters;
    const int numCharacters = 66; // OX + 64 character hash.
  
    // Hashing.
    SHA256 sha256; // SHA-256 utility to generate hashes.
    string hash;
  
    // A partition of integers that will keep updating with the
    // new hash while other stay stagnant. Size of the partition
    // is decided by 'partitionSize' integer in GUI. This is to
    // extract the constantly updating, iterating, thinking quality
    // of the mining process.
    vector<int> updatePartition;
    long int resetPartitionTime = 1; // Starting with 2 seconds. Updates
                                     // everytime the partition gets updated.
    long int lastPartitionTime;
};
