#include <iostream>
#include "HCNode.hpp"

bool HCNode::operator<(const HCNode& other){ 
  //Overload the operator'<' to compare the priority of two nodes
  if (this->count != other.count){
    //The node with low frequency or count has greater priority
    return this->count > other.count;
  }
  else
    return this->symbol < other.symbol;
  // If the count is same, then the priority follows alphabetic rule.
}



