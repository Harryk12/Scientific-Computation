//Harry Singh Kang eid:hsk697  tacc:hkangt
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


int main() {
  int longestsequence=0;
  for(int i=1;i<=1000;i++){
    int currentnum =i;
    int startingnum=currentnum;
    int sequencecount=1;
    while(currentnum>1){
      if(currentnum%2==0){
	currentnum=currentnum/2;
      } else{
	currentnum=3*currentnum+1;
      }
      sequencecount++;
    }
    if (sequencecount>longestsequence){
      longestsequence=sequencecount;
      cout<<"The new longest sequence of "<<longestsequence<<" started with "<<startingnum<<endl;
    }
  }
  return 0;
}
