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
    string printAddress(ESCPOS::DefaultSerialPrinter printer, int start, int end);
    // Hash generator
    SHA256 sha256; // SHA-256 utility to generate hashes.
};
