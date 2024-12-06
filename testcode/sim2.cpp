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
  //population test
  Population population(15);
  Disease flu(3,.9);
  double initial_infect=.7;
  for (int iter=1; iter<=10; ++iter){
    if (iter==3){    
      population.random_infection(flu,initial_infect);
    };
    int countnuminfected=population.count_infected();
    cout<<"In step "<<iter<< " #sick:  "<<countnuminfected<<" : ";
    for (Person& indiv:population.get_people()){    
      if (indiv.status_string()=="sick"){
	cout<<"+ ";
      } else{
	cout<<"? ";
      };
    };
    cout<<endl;
    if (iter>3 &&countnuminfected==0){
      cout<<"Disease ran its course by step "<< iter<<endl;
      break;
    };
    population.one_more_day();
  };

  return 0;
};
