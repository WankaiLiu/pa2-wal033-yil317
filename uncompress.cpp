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
  BitInputStream inputBit(inputFile); // bit for each input char
  BitOutputStream outputByte(outputFile); // bit for each input char
  HCTree hufTree;
  int i; // Number of leaves
  char symbol;    // Huffman node with frequency;
  int totalSymbol = 0;  // total number of symbol
  int uniqueSymbol = 0;      // total number of unique Symbol
  int totalinputSymbol = 0; // total number of input symbol
  string infile(argv[1]);
  string outfile(argv[2]);

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
    cout << "Reading header from file \"" << infile << "\"...done" << endl;
  }
  //Count the frequency for each symbol from the head of file.
  while((i = inputBit.readInt()) != 99999){
    counter[i] = inputBit.readInt();
    totalSymbol += counter[i];
  }
  for (i = 0; i<256; i++ ){
    if (counter[i] != 0){
      uniqueSymbol++;
    }
  }
  cout << "Uncompressed file will have " 
       << uniqueSymbol << "unique symbols and size " 
       << totalSymbol<< "bytes." << endl;
  //Build the Huffman tree.
  hufTree.build(counter);
  cout << "Building Huffman code tree... done.";
  outputFile.open(outfile, ios::binary);
  //Decode the symbol from the compress file.
  for (i=0; i<totalSymbol; i++) {
    symbol = hufTree.decode(inputBit);
    outputByte.writeByte(symbol);
  }
  //Display the final result.
  cout << "Writing to file \"" << outfile << "... done.\"" << endl;
  totalinputSymbol = inputFile.tellg();
  inputFile.close();
  outputFile.close();
  cout << "Uncompression ratio: " 
       << (double)totalSymbol / (double)totalinputSymbol << endl;
}
