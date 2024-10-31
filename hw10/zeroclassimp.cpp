//Harry S Kang    hsk697   hkangt
#include "zeroclasslib.hpp"
#include <iostream>
#include <vector>
#include <cmath>
//odd testing function
bool polynomial::is_odd() const{
  if(coefficients.size()%2==0){
    return 0;
  }else{
    return 1;
  };
};
//evaluation at a certain point 
double polynomial::evaluate_at(double x) const{
  double multiplier=1;
  double sum=0;
  for (int i=0;i<coefficients.size();i++){  //for loop to multiply by degrees of x
    double val=multiplier*coefficients[i];
    sum=sum+val;
    multiplier=multiplier*x;
  };
  return sum;
};
//find initial bounds for bisection
void find_initial_bounds( const polynomial& p, double& left, double& right){
  if (left> right){
    double stored=left;
    left=right;     //ensuring left is left of right
    right=stored;   
  };
  //trying to lead one of the bounds to the other side of the zero: cases
  if ((p(left)*p(right))>=0){
    if(p(left)>0){
      if (p(left)>p(right)){
	while(p(right)>0){
	  right=right+1;
	};
      } else {
	while(p(left)>0){
	  left=left-1;
	};
      };
    } else {
      if (p(left)>p(right)){
	while(p(left)<0){
	  left=left-1;
	};
      }else{
	while(p(right)<0){
	  right=right+1;
	};
      };
    };
  };
};
void move_bounds_closer( const polynomial& p,double& left,double& right){
  double midpoint=.5*(left+right);   //use midpoints and reassigning bounds for bisection
  if (p(midpoint)*p(right)>0){
    right=midpoint;
  }else{
    left=midpoint;
  };
};
//call function to find the zero
double find_zero( const polynomial& p,double precision){
  double leftval=8;   //initial random guesses
  double rightval=12;
  find_initial_bounds(p,leftval,rightval);
  while(std::abs(rightval-leftval)>precision){  //get it under tolerance
    move_bounds_closer( p,leftval,rightval);
  };
  return leftval;
};
  