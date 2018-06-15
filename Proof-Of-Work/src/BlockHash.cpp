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
    // New hash.
    createNewHash();
    
    // Are we inside the partition time bound? Check if I can update the "hash" update partition.
    if (ofGetElapsedTimef() - lastPartitionTime > resetPartitionTime) {
      updateCharacterPartition();
      lastPartitionTime = ofGetElapsedTimef();
      resetPartitionTime = ofRandom(1, 5);
    }
  }
  
  updateHashFbo(fbo);
}

void BlockHash::print(ESCPOS::DefaultSerialPrinter printer) {
  // Pre-hash.
  printer.setDefaultLineSpacing();
  printer.setInvert(true);
  string preString;
  for (int i = 0; i < 48; i++) {
    preString+='#';
  }
  printer.println(ofToString(preString));

  preString.clear();
  for (int i = 0; i < 48; i++) {
    preString+='|';
  }
  printer.println(ofToString(preString));

  preString.clear();
  for (int i = 0; i < 48; i++) {
    preString+='%';
  }
  printer.println(ofToString(preString));

  // Actual hash.
  printer.setInvert(false);
  printer.setLineSpacing(0);
  printer.println("0x" + ofToUpper(hash));

  // Post-hash.
  printer.setInvert(true);
  printer.setDefaultLineSpacing();

  string postString;
  for (int i = 0; i < 48; i++) {
    postString+='-';
  }
  printer.println(postString);

  postString.clear();
  for (int i = 0; i < 48; i++) {
    postString+=':';
  }
  printer.println(postString);

  postString.clear();
  for (int i = 0; i < 48; i++) {
    postString+='.';
  }
  printer.println(postString);

  printer.println("\n");
  
  // Send a cut command.
  printer.cut(ESCPOS::BaseCodes::CUT_FULL);
  printer.println("Live life like a king!");
  std::cout << "Full cut" << endl;
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

void BlockHash::createNewHash() {
   // Keep pushing a new character to this vector to generate a new hash.
  hashString.push_back('a');
  
  // Empty the vector when the size becomes really big.
  if (hashString.size() > 50) {
    hashString.clear();
  }
  
  // Extract a SHA256 hash from the string.
  hash = sha256 (ofToString(hashString));
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
    ofBackground(ofColor::red);
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
