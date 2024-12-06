#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <variant>
#include <cmath>
#include <ctime>
#include <set>


using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::variant;
using std::srand;
using std::rand;
using std::time;
using std::set;

int variantcounter=1;
int transmissioncounter=0;

#include "infect_lib.cc"

int main(){
//One person status test
  Person joe;
  Disease fever(3,1.);
  for ( int step = 1; step<=10; ++step ) {
    if(step==3){
      joe.infect(fever);
    };
    cout << "On day " << step << ", Joe is "<< joe.status_string();
    if(joe.status_string()=="sick"){
      cout<<"("<<joe.get_days_sick_left()<<" sick days left to go)";
    };
    cout<<"\n";
    if (joe.is_recovered())
      break;
    joe.one_more_day();
  };
  return 0;
};
