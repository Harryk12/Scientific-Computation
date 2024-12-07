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
  
  //coding random interactions and mutations
  
  Population population(50000);  
  double randvac=0.1;    
  population.random_vaccination(randvac);
  cout<<"Number of people vaccinated: "<<population.count_vaccinated()<<endl;
  vector<Person>& people=population.get_people();
  Person& nthperson=people[11];
  Disease flu(10,.4);
  srand(time(0));
  for (int iter=0;iter<100;++iter){
    if (iter==0){
      nthperson.initial_infect(flu);
    }else{
      int indexiter=0;
      for (Person& indiv:people){
	while((indiv.get_touch_counter())<6){ 
	  //srand(time(0));
	  int rindex=rand()%50000;
	  if (rindex!=indexiter){
	    indiv.touch(people[rindex],flu);   //,flu    
	  };
	};
	indexiter=indexiter+1;
      };
    };
    population.one_more_day();
    int countnuminfected=population.count_infected();
    if (iter>=0){
      cout<<"On iteration "<<iter<<" there are "<<countnuminfected<<" infected."<<endl;
    };
    for (Person& indivs:people){
      indivs.reset_touch_counter();
    };
  };
  cout<<variantcounter<<endl;
  cout<<transmissioncounter<<endl;
  return 0;
};
