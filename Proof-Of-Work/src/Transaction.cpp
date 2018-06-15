#include "Transaction.h"

Transaction::Transaction() {
  // Create a transaction hash.
  hash = sha256 (ofToString(ofRandom(0, 1000)));
  
  // Get the current time.
  time = ofGetCurrentTime();
}
