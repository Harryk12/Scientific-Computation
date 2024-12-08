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
  //Incorporating vaccination- randomly vaccinating a number of the population
    
  Population population(10);
  double randvacc=.3;                       //percentage to be randomly vaccinated                   
  population.random_vaccination(randvacc);
  cout<<"Number of people vaccinated: "<<population.count_vaccinated()<<endl;
  vector<Person>& people=population.get_people();
  Person& nthperson=people[4];        //nth person get's infected intially
  Disease flu(3,.5);
  for (int iter=0;iter<20;++iter){
    if (iter==0){
      nthperson.initial_infect(flu);  //different function than infect() here with p=1.0 to ensure the sim get's started (first person certainly gets infected)
    } else{
      for (int p=0;p<people.size();p++){  
	if (people[p].status_string()=="susceptible"){      //if susceptible person comes in contact with a sick neighbor, they have chance to get infected 
	  if (p+1<people.size() && people[p+1].status_string()=="sick"){                      //person in front is sick     
	    people[p].infect(flu);
	  };
	  if (p>0 && people[p-1].status_string()=="sick"){                   //person behind is sick
	    people[p].infect(flu);
	  };
        };
      };
    };
    int countnuminfected=population.count_infected();
    if (iter>0){
      cout<<"On iteration "<<iter<<" there are "<<countnuminfected<<" infected."<<endl;   //outputs number of infected per day
    };
    population.one_more_day();        //takes population's status through one day
  };
  return 0;
};
