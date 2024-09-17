// Harry Singh Kang    eid:hsk697      Tacc: hkangt
#include <iostream>
#include <functional>
using std::function;

using std::cin;
using std::cout;
using std::endl;
using std::abs;


double newton_root (function <double(double)> f, function <double(double)>fprime){
  double current_x=100000000.0;   //initial guess
  double fcurrent=f(current_x);   //corresponding function value
  for (int iteration_count=0; abs(fcurrent)>1e-5;++iteration_count){
    current_x -=f(current_x)/fprime(current_x);    //update new x value using newton method
    fcurrent=f(current_x);   //calculate new function value
    if(abs(fcurrent)<1e-5){    //stops when function value approaches a tiny value
      break;
    }
  }
  return current_x;    //this will return the root
}
double newton_root (function <double(double)>f){
  double current_x=100000000.0;   //initial guess
  double fcurrent=f(current_x);   //corresponding function value
  for (int iteration_count=0; abs(fcurrent)>1.e-5;++iteration_count){
    double fprimecurrent=(f(current_x+1e-6)-f(current_x))/(1e-6);   //calculating derivative using limit definition now instead of deriv function
    current_x-=f(current_x)/fprimecurrent;    //update new x value using newton method
    fcurrent=f(current_x);   //calculate new function value
    if(abs(fcurrent)<1e-5){    //stops when function value approaches tiny value
      break;
    }
  }
  return current_x;   //spits out the root
}

int main(){
  for (int n=2;n<=8;++n){
    auto f =[n](double x){return x*x-n;};    //functions for the first method of newton root
    auto fprime=[](double x){return 2*x;};
    cout<<"Sqrt(" << n << ") = " << newton_root(f,fprime) << " using a derivative function." << endl;   //calls first version of newton root (ex 4)
    cout<<"Sqrt(" << n << ") = " << newton_root(f) << " using the derivative/limit definition." << endl;  //calls second version of newton root (ex 5)
  }
  return 0;
}








 
