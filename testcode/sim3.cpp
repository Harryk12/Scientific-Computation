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
  //sanity tests
  //p=1 and testing how many sick the next day
  cout<<"Testing how many sick the next day"<<endl;
  Population population(10);
  vector<Person>& people=population.get_people();
  Person& firstperson=people[0];
  Disease flu(3,1.);
  for (int iter=0;iter<15;++iter){
    if (iter==0){
      firstperson.infect(flu);
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
  
  cout<<"Testing number of days run"<<endl;
  Population population2(10);
  vector<Person>& people2=population2.get_people();
  Person& firstperson2=people2[0];
  Disease flu2(3,1.);
  for (int iter2=0;iter2<15;++iter2){
    if (iter2==0){
      firstperson2.infect(flu2);
    } else{
      for (int p=0;p<people2.size();p++){
	if (people2[p].status_string()=="susceptible"){
	  if (p+1<people2.size() && people2[p+1].status_string()=="sick"){ 
	    people2[p].infect(flu2);
	  };
	  if (p>0 && people2[p-1].status_string()=="sick"){       
	    people2[p].infect(flu2);
	  };
	};
      };
    };
    int countnuminfected2=population2.count_infected();
    if (iter2>0){
      cout<<"On iteration "<<iter2<<" there are "<<countnuminfected2<<" infected."<<endl;
    };
    population2.one_more_day();
  };

  cout<<"Testing when p=.5"<<endl;
  Population population3(10);
  vector<Person>& people3=population3.get_people();
  Person& firstperson3=people3[0];
  Disease flu3(3,.5);
  for (int iter3=0;iter3<20;++iter3){
    if (iter3==0){
      firstperson3.initial_infect(flu3);
    } else{
      for (int p=0;p<people3.size();p++){
	if (people3[p].status_string()=="susceptible"){
	  if (p+1<people3.size() && people3[p+1].status_string()=="sick"){ 
	    people3[p].infect(flu3);
	  };
	  if (p>0 && people3[p-1].status_string()=="sick"){       
	    people3[p].infect(flu3);
	  };
	};
      };
    };
    int countnuminfected3=population3.count_infected();
    if (iter3>0){
      cout<<"On iteration "<<iter3<<" there are "<<countnuminfected3<<" infected."<<endl;
    };
    population3.one_more_day();
  };
  return 0;
};
