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

//mutation
int variantcounter=1;    //variant counter
int transmissioncounter=0;     //infections counter

//libary for classes and methods
#include "infect_lib.cc"

int main(){
  
  //coding random interactions and mutations
  
  Population population(50000);  
  double randvac=0.1;       
  population.random_vaccination(randvac);                     //random vaccinations
  cout<<"Number of people vaccinated: "<<population.count_vaccinated()<<endl;
  vector<Person>& people=population.get_people();
  Person& nthperson=people[11];         //nth person to be intially infected
  Disease flu(10,.4);
  srand(time(0));
  for (int iter=0;iter<100;++iter){
    if (iter==0){
      nthperson.initial_infect(flu);       //different than infect() to ensure starting person is infected (p=1)
    }else{
      int indexiter=0;
      for (Person& indiv:people){
	while((indiv.get_touch_counter())<6){         //limiting daily touches to 6 
	  int rindex=rand()%50000;                 //randomly indexing the 6 people out of population
	  if (rindex!=indexiter){                              //can't infect self
	    indiv.touch(people[rindex],flu);   
	  };
	};
	indexiter=indexiter+1;
      };
    };
    population.one_more_day();                 //takes population status through another day
    int countnuminfected=population.count_infected();
    if (iter>=0){
      cout<<"On iteration "<<iter<<" there are "<<countnuminfected<<" infected."<<endl;          //outputs number infected
    };
    for (Person& indivs:people){
      indivs.reset_touch_counter();                 //resets touch counter per day per person
    };
  };
  cout<<variantcounter<<endl;                       //outputs mutatations for sanity check
  cout<<transmissioncounter<<endl;
  return 0;
};
