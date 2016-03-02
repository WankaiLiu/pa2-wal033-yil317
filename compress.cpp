#include"HCTree.hpp"
#include"HCNode.hpp"
#include"BitInputStream.hpp"
#include"BitOutputStream.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

int main(int argc, char ** argv){
  vector<int> counter(256,0);  // count for every symbol in file.
  ifstream inputFile;  // input file stream
  ofstream outputFile; // output file stream
  int uniqueSymbol = 0;      // total number of unique Symbol
  int totalSymbol = 0;  //total number of input Symbol
  int totalOutputSymbol = 0; // total number of output symbol
  BitInputStream inputBit(inputFile); // bit for each input char
  BitOutputStream outputBit(outputFile); // bit for each input char
  int readBit;     
  HCTree hufTree;         //the new huffmanTree
  string infile(argv[1]); //the name of input file
  string outfile(argv[2]);// the name of output file
  
  //If the input parameterers is wrong, return fault.
  if(argc < 3){
    cout << "Arguments Error" << endl;
    return 1;
  }
  //if the input file name is wrong, return fault.
  inputFile.open(infile);
  if (!inputFile.is_open()){
    cout << "Could not open file"<<endl;
    return 0;
  }
  else{
    cout<< "Reading from file... \"" << infile << "\"...done" << endl;
  }
  //Count the frequency for each symbol.
  while (inputFile.good() ) {
    readBit = inputBit.readByte();
    if (readBit != -1){
      counter[readBit]++;
      totalSymbol = inputFile.tellg();
    }  

  }
  //Count the total number of unique symbol.
  for (int i = 0; i<256; i++ ){
    if (counter[i] != 0){
      uniqueSymbol++;
    }
  }
  cout << "Found " << uniqueSymbol << " unique symbols in input file of size "
       << totalSymbol << " bytes" << endl;
  cout << "Building huffman code tree...";
  //Build the Huffman tree.
  hufTree.build(counter);
  cout << "done" << endl;
  inputFile.close();
  inputFile.open(infile,ios::binary);
  outputFile.open(outfile,ios::binary);
  cout << "Writing to file... \"" << outfile << "\"...";
  //Write the frequency of symbols on the head of file.
  for (int i = 0; i<256; i++ ){
    if (counter[i] != 0){
      outputBit.writeInt(i);
      outputBit.writeInt(counter[i]);
    }
  }
  outputBit.writeInt(99999);  // the boundary of head and encode file
  //Convert the original code into Hufman code.
  while ((readBit = (inputBit.readByte())) != -1) {
    hufTree.encode(readBit,outputBit);
  }
  cout << "done" << endl; 
  outputBit.flush();
  totalOutputSymbol = outputFile.tellp();
  inputFile.close();
  outputFile.close();
  cout << "Output Filehas size "  << totalOutputSymbol << " bytes" << endl;
  cout << "Compression ratio: " 
       << (double)totalOutputSymbol/(double)totalSymbol << endl;
}
