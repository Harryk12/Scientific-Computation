#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main(){
  int n;
  cout<<"Please enter an integer"<<endl;
  cin>> n;
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
