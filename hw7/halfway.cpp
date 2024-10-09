//Harry Singh Kang hsk697  hkangt
#include <iostream>
#include <string>
#include <sstream>
using std::endl;
using std::cout;
using std::string;
using std::stringstream;

class Point {
private:
   float p;
   float q;
public:
   // Constructor
  Point (float P,float Q){
     p=P;
     q=Q;
   }
  //Overload Operators

  Point operator*(float scaler) const{
    return Point(p*scaler,q*scaler);
  }
  Point operator+(const Point& B) const{
    return Point((this->p)+B.p,(this->q)+B.q);
  }
  //printing the class 
  string as_string(){
    stringstream ss;
    ss<<"("<<p<<", "<<q<<")";
    return ss.str();
  }
};

int main() {
  //creating objects and computing halway point
    Point a(1, 3);
    Point b(3,7);
    Point sum=a+b;
    Point scaled=sum*.5;
  
    cout<<scaled.as_string()<<endl;  //printing
    return 0;
}
