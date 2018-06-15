#include "BlockHash.h"

void BlockHash::setup() {
  // Collect all the fonts.
  fonts.push_back("betong.ttf");
  fonts.push_back("jmt.otf");
  fonts.push_back("perfect.otf");
  fonts.push_back("chengis.otf");
  fonts.push_back("schaeffer.ttf");
  fonts.push_back("keys.ttf");
  fonts.push_back("giovanni.ttf");
  
  fontSize.addListener(this, &BlockHash::updateFromGui);
  
  createCharacters();
  
  // Create the partition.
  updateCharacterPartition();
  
  // Store current time for mining partition update.
  lastPartitionTime = ofGetElapsedTimef();
}

void BlockHash::update(ofFbo &fbo) {
  if (miningState == Mining) {
    // Create new hash
    hash = sha256 (ofToString(ofRandom(1000, 2000)));
    
    // Are we inside the partition time bound? Check if I can update the "hash" update partition.
    if (ofGetElapsedTimef() - lastPartitionTime > resetPartitionTime) {
      updateCharacterPartition();
      lastPartitionTime = ofGetElapsedTimef();
      resetPartitionTime = ofRandom(1, 5);
    }
  }
  
  updateHashFbo(fbo);
}
// Time
//+-----------------------------------------------------+
//O-----------------------------------------------------o
//                        5129
//x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x
//                        732D
//:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:
//                        C7DF
//x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x
//                        D94C
//:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:
//                        F449
//x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x
//                        C0B5
//:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:
//                        61E4
//x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x
//                        BFD8
//:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:
//                        5808
//x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x
//                        AD69
//:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:
//                        4D59
//x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x
//                        D33F
//:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:
//                        4F16
//x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x
//                        D3F0
//:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:
//                        A35E
//x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x
//                        C1F2
//+-----------------------------------------------------+
//o-----------------------------------------------------o

void BlockHash::print(ESCPOS::DefaultSerialPrinter printer) {
  std::stringstream stream;
  
  // Line 0 - Time
  printer.setInvert(true);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_CENTER);
  std::time_t currentTime = std::time(NULL);
  string s = std::ctime(&currentTime);
  string currentLine = s.substr(0, s.size() - 1);
  
  stream << currentLine << endl;
  printer.println(currentLine);
  
  // Line 1
  stream << printBoundingSection(printer, '+') << endl;
  
  // Line 2
  stream << printBoundingSection(printer, 'o') << endl;
  
  // Line 3 - 34
  int start = 0; int end = 4; int idx = 0;
  for (int i = 0; i < 31; i++) {
    if (i % 2 == 0) {
      stream << printHash(printer, start, end) << endl;
      start += 4; end += 4;
    } else {
      if (idx % 2 == 0) {
        stream << printInbetween(printer, 'x') << endl;
      } else {
        stream << printInbetween(printer, ':') << endl;
      }
      idx++;
    }
  }
  
  // Line 35
  stream << printBoundingSection(printer, 'o') << endl;
  
  // Line 36
  stream << printBoundingSection(printer, '+') << endl;
  
  std::cout << stream.str() << endl;
  
  // Send a cut command.
  printer.println("Chill life ~ Chill beats.");
  printer.cut(ESCPOS::BaseCodes::CUT_FULL);
}

string BlockHash::printBoundingSection(ESCPOS::DefaultSerialPrinter printer, char c) {
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

string BlockHash::printHash(ESCPOS::DefaultSerialPrinter printer, int start, int end) {
  printer.setInvert(true);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_CENTER);
  
  string currentLine;
  for (int i = start; i < end; i++) {
    currentLine += hash[i];
  }
  
  printer.println(currentLine);
  return currentLine;
}

string BlockHash::printInbetween(ESCPOS::DefaultSerialPrinter printer, char c) {
  printer.setInvert(false);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_LEFT);
  
  string currentLine;
  for (int i = 0; i < 48; i++) {
    if (i % 2 == 0) {
      currentLine += c;
    } else {
      currentLine += '-';
    }
  }
  printer.println(currentLine);
  return currentLine;
}

void BlockHash::updateFromGui(int & val) {
  createCharacters();
}

void BlockHash::createCharacters() {
  characters.clear();
  
  // We have 64 characters.
  for (int i = 0; i < numCharacters; i++) {
    Character c;
    c.setup(fonts[currentFontIdx], fontSize);
    characters.push_back(c);
  }
}

void BlockHash::updateCharacterPartition() {
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
  
  // Push the entire character set. Need to show the new hash.
  if (miningState == Mined) {
    for (int i = 2; i < numCharacters; i++) {
      updatePartition.push_back(i);
    }
  }
}

void BlockHash::updateHashFbo(ofFbo &fbo) {
  fbo.begin();
    if (miningState == Mined) {
      ofBackground(ofColor::red);
    } else {
      ofBackground(ofColor::red);
    }
  
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
  fbo.end();
}

void BlockHash::cycleFont(bool forward) {
  if (forward) {
    // Wrapp current font idx.
    currentFontIdx = (currentFontIdx + 1) % fonts.size();
    createCharacters();
  } else {
    // Wrap current font idx.
    if ((currentFontIdx - 1) < 0) {
      currentFontIdx = fonts.size() - 1;
    } else {
      currentFontIdx--;
    }
    createCharacters();
  }
}
