//Harry Singh Kang   hsk697   hkangt
#include <iostream>
using std::cout;
#include <complex>
using std::complex;

//templatized functions
template<typename T> 
T f(T x) {return x*x-static_cast<T>(-2);};
template<typename T>
T deriv(T x) {return static_cast<T>(2)*x;};

int main() {
  // find the square root of negative two
  
  using namespace std::complex_literals;
  //starting at a complex value
  complex<double> current_x = 10000000.+1.i;
  auto function_value = f(current_x);
  //loop until break
  for ( int iteration_count=0; ; ++iteration_count ) {
    // update current x
    current_x -= f(current_x) / deriv(current_x);
    // calcute new function value
    function_value = f(current_x);
    //printing values at current iteration
    cout << iteration_count << ":" << function_value << '\n';
    if ( std::abs(function_value)<1.e-5 ) {   //if close to root, print result and break
      cout << "Function is " << f(current_x) << " at " << current_x <<
	" in iteration " << iteration_count << '\n';
      break;
    }
  }
  return 0;
}


