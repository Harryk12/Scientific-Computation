//Harry Singh Kang   hsk697    hkangt
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

//global variables used in later main programs
int variantcounter=1;
int transmissioncounter=0;

//library of classes/methods
#include "infect_lib.cc"

int main(){
  //Tracking the status of one person infected
  Person joe;
  Disease flu(3,1.);      
  for ( int step = 1; step<=10; ++step ) {
    if(step==3){                   //day of initial infection 
      joe.infect(flu);
    };
    cout << "On day " << step << ", Joe is "<< joe.status_string();
    if(joe.status_string()=="sick"){
      cout<<"("<<joe.get_days_sick_left()<<" sick days left to go)";   //tracks how many days of sick left
    };
    cout<<"\n";
    if (joe.is_recovered())
      break;
    joe.one_more_day();                         //taking person through one more day and updating status
  };

  
  //Person class sanity tests
  Person bob;
  bob.infect(flu);
  for (int iter=1;iter<=4;iter++){
    bob.one_more_day();
    if (iter==1){
      cout<<"After getting infected, bob's status is:"<<bob.status_string()<<endl;   //tests if infected with 100% transmission, register as sick the next day
    };
  };
  bob.infect(flu);           //given iter amount of days to recover, this tests if it's possible to get sick again after recovering
  cout<<"After getting infected again with a recovered status, bob's status is:"<<bob.status_string()<<endl;

  //seeing if around 50% of "persons" get affected if transmission rate is .5
  Disease flu2(3,.5);
  vector<Person>people(100);  
  int countinfected=0;
  for (auto& indiv : people){
    indiv.infect(flu2);
    indiv.one_more_day();
    if (indiv.status_string()=="sick"){
      countinfected++;                                  //counts those infected
    };
  };
  //output
  cout<<"With transmission rate of .5, the number of people who got infected using random numbers was "<<countinfected<<endl;
  return 0;
};
