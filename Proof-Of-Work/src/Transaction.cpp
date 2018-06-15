#include "Transaction.h"

Transaction::Transaction() {
  // Create a transaction hash.
  hash = sha256 (ofToString(ofRandom(0, 1000)));
  
  // Get the current time.
  currentTime = std::time(NULL);
}

//+-----------------------------------------------------+ L1
//o-----------------------------------------------------o L2
//                  5129732DC7DFD94C (16) L3
//!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-! L4
//                  F449C0B561E4BFD8 L5
//-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i-i- L6
//                  5808AD694D59D33F L7
//!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-! L8
//                  4F16D3F0A35EC1F2 L9
//+-----------------------------------------------------+ L10
//o-----------------------------------------------------o L11
void Transaction::print(ESCPOS::DefaultSerialPrinter printer) {
  // Transaction pattern.
 
  string currentLine;
  std::stringstream stream;
  
  // Line 0 - Time
  printer.setInvert(true);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_CENTER);
  string s = std::ctime(&currentTime);
  currentLine = s.substr(0, s.size() - 1);
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  // Line 1
  printer.setInvert(false);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_LEFT);
  currentLine = "+";
  for (int i = 0; i < 46; i++) {
    currentLine += '-';
  }
  currentLine += '+';
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  
  // Line 2
  currentLine = "o";
  for (int i = 0; i < 46; i++) {
    currentLine += '-';
  }
  currentLine += 'o';
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  // Line 3
  printer.setInvert(true);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_CENTER);
  
  for (int i = 0; i < 16; i++) {
    currentLine += hash[i];
  }
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  // Line 4
  printer.setInvert(false);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_LEFT);
  
  for (int i = 0; i < 48; i++) {
    if (i % 2 == 0) {
      currentLine += '!';
    } else {
      currentLine += '-';
    }
  }
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  // Line 5
  printer.setInvert(true);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_CENTER);
  
  for (int i = 16; i < 32; i++) {
    currentLine += hash[i];
  }
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  // Line 6
  printer.setInvert(false);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_LEFT);
  
  for (int i = 0; i < 48; i++) {
    if (i % 2 == 0) {
      currentLine += 'i';
    } else {
      currentLine += '-';
    }
  }
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  // Line 7
  printer.setInvert(true);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_CENTER);
  
  for (int i = 32; i < 48; i++) {
    currentLine += hash[i];
  }
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  // Line 8
  printer.setInvert(false);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_LEFT);
  
  for (int i = 0; i < 48; i++) {
    if (i % 2 == 0) {
      currentLine += '!';
    } else {
      currentLine += '-';
    }
  }
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  // Line 9
  printer.setInvert(true);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_CENTER);
  
  for (int i = 48; i < 64; i++) {
    currentLine += hash[i];
  }
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  // Line 10
  printer.setInvert(false);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_LEFT);
  
  currentLine = "o";
  for (int i = 0; i < 46; i++) {
    currentLine += '-';
  }
  currentLine += 'o';
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  // Line 11
  currentLine = "+";
  for (int i = 0; i < 46; i++) {
    currentLine += '-';
  }
  currentLine += '+';
  
  stream << currentLine << endl;
  printer.println(currentLine);
  currentLine.clear();
  
  std::cout << stream.str() << endl;
}
