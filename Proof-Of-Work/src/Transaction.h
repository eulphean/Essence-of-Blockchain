#pragma once

#include "sha256.h"
#include "ofMain.h"

class Transaction {
  public:
    Transaction();
    string hash; // Hash of the transaction.
    ofTime time; // Time this transaction was created.
    
  private:
    // Hash generator
    SHA256 sha256; // SHA-256 utility to generate hashes.
};
