#pragma once

#include "sha256.h"
#include "ofMain.h"
#include "ofxESCPOS.h"

using namespace ofx;

class Transaction {
  public:
    Transaction();
    void print(ESCPOS::DefaultSerialPrinter printer);
    string hash; // Hash of the transaction.
    std::time_t currentTime; // Time this transaction was created.
    
  private:
    // Hash generator
    SHA256 sha256; // SHA-256 utility to generate hashes.
};
