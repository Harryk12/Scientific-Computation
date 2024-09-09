//Harry Singh Kang eid:hsk697  tacc:hkangt
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


int main() {
  int longestsequence=0;
  for(int i=1;i<=1000;i++){   // looping through all starting numbers
    int currentnum =i;
    int startingnum=currentnum;   //save for later
    int sequencecount=1;   //initialize length of current sequence
    while(currentnum>1){    //actual algorithm
      if(currentnum%2==0){
	currentnum=currentnum/2;
      } else{
	currentnum=3*currentnum+1;
      }
      sequencecount++;    //update the count of the sequence
    }
    if (sequencecount>longestsequence){ //conditional to update the new longest sequence with the current one if bigger
      longestsequence=sequencecount;
      cout<<"The new longest sequence of "<<longestsequence<<" started with "<<startingnum<<endl;
    }
  }
  return 0;
}
