//Harry S Kang, hsk697, hkangt
#include <iostream>
#include <stdio.h>
using std::cout;
using std::endl;
using std::cin;

  
int main(int argc, char *argv[]){
  //=read_number()
  int n;
    n=atoi(argv[1]);
    //fizzbuzz logic
    //using remainder logic to see multiple of 3 and 5 (Fizzbuzz), just 3 (Fizz), and just 5 (Buzz).
  if ((n%3==0)&&(n%5==0)){
      cout<<"Fizzbuzz!\n";
  }
  else if((n%3==0)&&(n%5!=0)){
      cout<<"Fizz!\n";
  }
  else if((n%3!=0)&&(n%5==0)){
    cout<<"Buzz!\n";
  }
  else{
    return 0;
  }
  return 0;
}

//C-x C-s : save this file
//C-x C-c : quit the editor, but oten better to 
// C-z : suspend the editor
// on the unix level: fg brings it back
