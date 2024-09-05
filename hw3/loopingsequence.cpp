#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int read_number(){
  int n;
  cin>>n;
  return n;
}

int main() {
  int currentnum=read_number();
  int startingnum=currentnum;
  int longestsequence=0;
  for(int i=1;i<=1000;i++){
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
      cout<<"Starting number for this new longest sequence of "<<longestsequence<<" is "<<startingnum<<endl;
    }
  }
  return 0;
}
