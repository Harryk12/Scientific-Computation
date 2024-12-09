//Harry Singh Kang   hsk697   hkangt
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

//global variables to be used later for mutations
int variantcounter=1;
int transmissioncounter=0;

//library of classes and methods
#include "infect_lib.cc"

int main(){
  
  //coding random interactions and iterating over vaccination and transmission rates to evaluate patterns
  
  for (double vac=0.1;vac<=.1;vac=vac+.1){      //iterating over vaccination rates                                -vary accordingly
    for (double transmit=0.9;transmit<=.9;transmit=transmit+.1){     //iterating over transmission rates            -vary accordingly
      Population population(50000);  //population size
      double randvac=vac;    
      population.random_vaccination(randvac);          
      cout<<"Number of people vaccinated: "<<population.count_vaccinated()<<endl;
      vector<Person>& people=population.get_people();
      Person& nthperson=people[11];        //arbirary starting value
      Disease flu(10,transmit);           //disease lasts 10 days
      srand(time(0));
      for (int iter=0;iter<220;++iter){
	if (iter==0){
	  nthperson.initial_infect(flu);           //day of initial infection (to ensure first person gets infected p=1. here)
	}else{
	  int indexiter=0;
	  for (Person& indiv:people){
	    while((indiv.get_touch_counter())<6){            //each person is limited to 6 contacts per day
	      
	      int rindex=rand()%50000;                             //contacts are randomly indexed
	      if (rindex!=indexiter){                          //can't infect themselves
		indiv.touch(people[rindex],flu);                    //interactions encoded in touch
	      };
	    };
	    indexiter=indexiter+1;
	  };
	};
	population.one_more_day();                          //population status taken through a day
	int countnuminfected=population.count_infected();
	if (iter>=0){
	  cout<<"On iteration "<<iter<<" there are "<<countnuminfected<<" infected."<<endl;      //outputs how many infected
	};
	for (Person& indivs:people){
	  indivs.reset_touch_counter();                    //touch counter reset each day
	};
      };
    };
  };
  return 0;
};
