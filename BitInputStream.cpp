#include <iostream>
#include <bitset>
#include "BitInputStream.hpp"
using namespace std;

int BitInputStream::readBit(){//Read a bit per time from the input file.
  if (bufi == 8){// If buffer is full reset index 'bufi' as 0 and get a symbol
    bufi = 0;     // from inputfile.
    buf = in.get();
    if (in.eof()) {
      return -1;
    }
  }
  return (buf >> bufi++) & 1;//Otherwise,return the bit of index 'bufi'.
}

int BitInputStream::readByte(){// Read a byte from input file.
  if (in.eof()) {
    return -1;
  }
  return in.get();
}

int BitInputStream::readInt(){//Read a 4-byte Int from the input file.
  if (in.eof()) {
    return -1;
  }
  int readN;
  in.read((char*)&readN,sizeof(readN));
  return readN;
}
