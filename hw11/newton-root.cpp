//Harry Singh Kang   hsk697   hkangt
#include <iostream>
using std::cout;
using std::endl;
#include <complex>
#include <type_traits>
using std::complex;
using namespace std::complex_literals;

//templatized function and derivative
template<typename T> 
T f(T x, T val) {return x*x-static_cast<T>(val);};
template<typename T>
T deriv(T x, T val) {return static_cast<T>(2)*x;};

template <typename T>
struct is_complex : std::false_type {};  // Default to false

template <typename T>
struct is_complex<complex<T>> : std::true_type {};    //checking for complex input

//templatized newton-root function
template<typename T>
T newton_root(T val){
  T current_x;
  //pass in different initial guess values depending on complex or not
  if constexpr (is_complex<T>::value){
    current_x=static_cast<T>(100.+1.i);
  }else{
    current_x=static_cast<T>(100.);
  };
  //compute function value
  auto function_value = f(current_x,val);
  //loop until break
  for ( int iteration_count=0; ; ++iteration_count ) {
    // update current x
    current_x -= f(current_x,val) / deriv(current_x,val);
    // calcute new function value
    function_value = f(current_x,val);
    //printing values at current iteration
    cout << iteration_count << ":" << function_value << '\n';
    if ( std::abs(function_value)<1.e-5 ) {   //if close to root, print result and break
      cout << "Function is " << f(current_x,val) << " at " << current_x <<" in iteration " << iteration_count << '\n';
      return current_x;
    };
  };     
};
      
int main() {
  // calling the newton-root function for different values- complex, float, and double
  auto x_float=newton_root<float>(2.0f);
  cout<<"Xfloat is: "<< x_float <<endl;
  auto x_double=newton_root<double>(2.0);
  cout<<"Xdouble is: "<<x_double<<endl;
  auto x_complex=newton_root<complex<float>>(2.0f+2.fi);
  cout<<"Xcomplex is "<<x_complex<<endl;
  return 0;
}


