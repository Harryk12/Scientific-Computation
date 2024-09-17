#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::abs;

double f(double x){
  return x*x-2;
}

double deriv(double x){
  return 2*x;
}


//int main(){
//yvalue=2;
//startyvalue=yvalue;
//xvalue=fx(starty);
//while (yvalue<10^-5){
//  xnew=xvalue-fx(xvalue)/derivx(xvalue);
//  yvalue=fx(xnew);
//}

  
int main(){


  double current_x=100000000.0;
  double function_value=f(current_x);
  for (int iteration_count=0; abs(function_value)>1.e-5;++iteration_count){
    //update x
    current_x -=f(current_x)/deriv(current_x);
    //calculate new function value
    function_value=f(current_x);
    //print
    if(abs(function_value)<1.e-5){ 
      cout<<"Function value of "<<f(current_x)<<" is reached at x="<<current_x<<" in "<<iteration_count<<" iterations"<<endl;
    }
  }
  return 0;
}








 
