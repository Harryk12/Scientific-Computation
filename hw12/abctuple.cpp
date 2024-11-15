//Harry Singh Kang    hsk697    hkangt
#include <iostream>
using std::cout;
#include <cmath>
#include <string>
using std::string;

#include <optional>
using std::optional;

#include <tuple>
using std::pair, std::make_pair, std::tuple, std::make_tuple;
#include <variant>
using std::variant, std::monostate;

using quadratic = tuple<double,double,double>;

double discriminant
    ( quadratic q ) {
  auto [a,b,c] = q;
  return b*b-4*a*c;
}

// assuming there are two roots, return as pair
pair<double,double> abc_roots( quadratic q ){
  auto[a,b,c]=q;
  auto disc=discriminant(q);         //find discriminant 
  auto xmin=(-b-sqrt(disc))/(2.0*a);    //finding left and right side roots    
  auto xmax=(-b+sqrt(disc))/(2.0*a);
  pair <double,double> ans=make_pair(xmax,xmin);
  return ans;
};

// say either "one" or "two", or say nothing
optional<string> how_many_roots( quadratic q ){
  if(discriminant(q)>=0){         //if real roots exist
    if((discriminant(q)-0.0)<1e-6){    //accounting for bit error- so close enough to 0 is 1 root
      return "one";
    };
    return "two";   //otherwise 2
  }else {
    return {};     //if roots are imag
  };
};

//variant used here to accomodate switch testing in the code below- different output type depending on the case
variant<monostate,double,pair<double,double>> abc_cases(quadratic q){
  if (discriminant(q)<0){
    return monostate{};      //monostate if no real roots exist
  }
  auto[a,b,c]=q;
  if((discriminant(q)-0.0)<1e-6){          //double if one root exists
    return -b/(2.0*a);
  } else {
    auto tworoots=abc_roots(q);       //pair if two do
    return tworoots;
  };
};

int main() {
/*
   * Initialization syntax is not unique
   */
  { 
    // spell it out
    auto sunk = tuple<double,double,double>{1.,0.,-2};
  }
  {
    // brace syntax
    auto sunk = quadratic{1.,0.,-2};
  }
    
     /*
   * Here is the actual program
   */
  // parenthesis syntax
  // polynomial: x^2 - 2


  //testing the code with the sunk use case
  auto sunk = quadratic(1.,0.,-2);
  auto [a,b,c] = sunk;
  cout << "coefficients: " << a << "," << b << ',' << c << '\n';

  auto d = discriminant( sunk );
  cout << "discriminant: "
       << d << '\n';
  //seeing if how_many_roots works
  auto num_solutions = how_many_roots(sunk);
  if ( not num_solutions.has_value() )
    cout << "none\n";
  else
    cout << num_solutions.value() << '\n';
  //seeing if abc_roots works
  auto roots = abc_roots( sunk );
  auto [xplus,xminus] = roots;
  cout << xplus << "," << xminus << '\n';
  //seeing if variant structure works
  auto root_cases = abc_cases( sunk );
  switch (root_cases.index()) {
  case 0 : cout << "No roots\n"; break;
  case 1 : cout << "Single root: " << get<1>(root_cases); break;
  case 2 : {
    auto xs = get<2>(root_cases);
    auto [xp,xm] = xs;
    cout << "Roots: " << xp << "," << xm << '\n';
  } ; break;
  }

  return 0;
}
