#include <iostream>
#include <bitset>
#include "BitOutputStream.hpp"
using namespace std;

void BitOutputStream::writeBit(int bit){//Write a bit per time into the output file
  buf = (buf | ((bit & 1) << bufi));//Put the input bit into a buffer. 
  bufi++;
  if (bufi == 8){//If the buffer is full then fluch out.
    flush();
  }
  return;
}

void BitOutputStream::writeByte(int b){//Writ a byte per time.
  out.put(b);
}

void BitOutputStream::writeInt(int i){//Write a 4-byte Int into the output file.
  out.write((char*)&i,sizeof(i));
}

void BitOutputStream::flush(){//flush function which is called when the buffer is full.
  out.put(buf);
  buf = 0;
  bufi = 0;
}
