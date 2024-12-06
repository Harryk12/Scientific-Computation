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
  Population population(10);
  double randvacc=.3;
  population.random_vaccination(randvacc);
  cout<<"Number of people vaccinated: "<<population.count_vaccinated()<<endl;
  vector<Person>& people=population.get_people();
  Person& nthperson=people[0];
  Disease flu(3,.9);
  //int countnuminfected3=population3.count_infected();
  //cout<<countnuminfected3<<endl;
  for (int iter=0;iter<15;++iter){
    //population2.one_more_day();
    //////firstperson.infect(flu2);
    if (iter==0){
      nthperson.initial_infect(flu);
    } else{
      for (int p=0;p<people.size();p++){
	if (people[p].status_string()=="susceptible"){
	  if (p+1<people.size() && people[p+1].status_string()=="sick"){     
	    people[p].infect(flu);
	  };
	  if (p>0 && people[p-1].status_string()=="sick"){        
	    people[p].infect(flu);
	  };
        };
      };
    };
    int countnuminfected=population.count_infected();
    if (iter>0){
      cout<<"On iteration "<<iter<<" there are "<<countnuminfected<<" infected."<<endl;
    };
    population.one_more_day();
  };
  return 0;
};
