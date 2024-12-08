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
  //vaccination sanity test
  Population community(20);
  double vacc=1.;                             //testing when 100% vaccination
  community.random_vaccination(vacc);
  cout<<"With a vaccinated rate of 100%, the number of vaccinated in a population of 20 is: "<<community.count_vaccinated()<<endl;

  
  //Epidemic simulation of a population with no contact shown with + for sick and ? for susceptible
  Population population(15);
  Disease flu(3,.9);
  double initial_infect=.4;                  //a certain number of the population gets infected  (should stay constant with no contact)
  for (int iter=1; iter<=10; ++iter){
    if (iter==3){                               //day of initial sickness
      population.random_infection(flu,initial_infect);
    };
    int countnuminfected=population.count_infected();
    cout<<"In step "<<iter<< " #sick:  "<<countnuminfected<<" : ";
    for (Person& indiv:population.get_people()){    
      if (indiv.status_string()=="sick"){
	cout<<"+ ";     //output sick
      }else if(indiv.status_string()=="susceptible"){
	cout<<"? ";     //output susceptible 
      }else{
	cout<<"- ";     //output recovered
      };	  
    };
    cout<<endl;
    if (iter>3 &&countnuminfected==0){     //outputting end of sickness
      cout<<"Disease ran its course by step "<< iter<<endl;
      break;
    };
    population.one_more_day();  //taking population through another day
  };

  return 0;
};
