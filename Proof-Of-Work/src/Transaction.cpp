#include "Transaction.h"

Transaction::Transaction() {
  // Create a transaction hash.
  hash = sha256 (ofToString(ofRandom(0, 1000)));
  
  // Get the current time.
  currentTime = std::time(NULL);
}

string Transaction::printAddress(ESCPOS::DefaultSerialPrinter printer, int start, int end) {
  printer.setInvert(false);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_CENTER);
  
  string currentLine;
  for (int i = start; i < end; i++) {
    currentLine += hash[i];
  }
  
  printer.println(currentLine);
  return currentLine;
}
// Time
// 5129732DC7DFD94CF449C0B561E4BFD8
// 5808AD694D59D33F4F16D3F0A35EC1F2
void Transaction::print(ESCPOS::DefaultSerialPrinter printer) {
  std::stringstream stream;
  
  // Print time.
  printer.setInvert(true);
  printer.setAlign(ESCPOS::BaseCodes::ALIGN_CENTER);
  string s = std::ctime(&currentTime);
  string currentLine = s.substr(0, s.size() - 1);
  stream << currentLine << endl;
  printer.println(currentLine);
  
  currentLine.clear();
  
  // Print complete hash. 
  currentLine = printAddress(printer, 0, 32);
  stream << currentLine << endl;
  currentLine = printAddress(printer, 32, 64);
  stream << currentLine << endl;
  
  std::cout << stream.str() << endl;
}
