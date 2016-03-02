#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include"HCTree.hpp"

HCTree::~HCTree(){  //destuctor for HCTree
  this->deletenode(root);
}

void HCTree::deletenode(HCNode* cur){    
  //Recursively use detenode function to delet the nodes in HCT.
  if (cur == 0){
    return;
  }
  deletenode(cur->c0);
  deletenode(cur->c1);
  delete cur;
}
	  
void HCTree::build(const vector<int>& freqs){  // Buil the Huffman Tree
  priority_queue<HCNode*,vector<HCNode*>, HCNodePtrComp> pQueue;
  for (int i = 0; i<256; i++ ){
    if (freqs[i] != 0){
      leaves[i] = new HCNode(freqs[i], i);  
      //Push the node of which the count is not zero into heap
      pQueue.push(leaves[i]);
    }
  }
  if(pQueue.size() == 0){
    return;
  }
  else{
    while (pQueue.size() != 1){
      // While the size fo heap or there is another tree in the forest,loop continues.
      HCNode *temp1, *temp2;
      temp1 = pQueue.top();
      //Get two elements with smallest count and  pop out these two.
      pQueue.pop();
      temp2 = pQueue.top();
      pQueue.pop();
      HCNode* newNode = new HCNode(temp1->count + temp2 -> count, temp1->symbol);
      //Combine two node with smallest frequency into one tree
      newNode->c0 = temp2;
      newNode->c1 = temp1;
      temp1->p = newNode;
      temp2->p = newNode;
      pQueue.push(newNode);
      //Push the new tree or new node into huffman tree.
    }
    root = pQueue.top();
    pQueue.pop();
  }
}

void HCTree::encode(byte symbol, BitOutputStream& out) const{
  //Encode function which calls subfuntion encode_2.
  HCNode *temp = leaves[symbol];
  if (!temp->p){ // If the tree only have one kind of symbol.
    out.writeBit(0);
    return;
  }
  encode_2(temp, out);//Call subfunction encode_2 to encode.
}
void HCTree::encode_2(HCNode* ptr, BitOutputStream& out) const{
  if(ptr -> p)                
    //If the current node has a parent then
    encode_2(ptr -> p, out);
  //recursivelly call subfunction encode_2.
  else
    return;
  if(ptr == ptr -> p -> c0){ 
    // If the child c0 of parent of current node is equal to current node
    out.writeBit(0);         
    // then write a bit '0' into the output file.
  }
  else{
    out.writeBit(1);        
    // Otherwise,write a bit of '1' into output file.
  }
}

int HCTree::decode(BitInputStream& in) const{// decode function
  HCNode *temp;
  temp = this->root;
  if ( temp->c0 == 0){ 
    // If root equals to leaf then return its symbol
    return temp->symbol;
  }
  do{                          
    //From the root to leaves,read one bit per time
    if (in.readBit() == 0){  
      //If the bit read is '0'. then move pointer from current node to the 'child0'.
      temp = temp->c0;         
      if (!temp->c0){        //If current node has no child 
	return temp->symbol;  //then return the symbol of leave

      }
    }
    else{                     
      //If the bit read is '1'. then move pointer from current node to the 'child1'.
      temp = temp->c1;
      if (!temp->c0){
	return temp->symbol;
      }
    }
  }while (1);
}

