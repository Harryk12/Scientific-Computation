//Harry Singh Kang   hsk697     hkangt
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

//gloabl variables to be used later for mutations
int variantcounter=1;
int transmissioncounter=0;

//libary of classes and methods
#include "infect_lib.cc"

int main(){
  //All tests involve contact where only direct neighbors of a sick person can get sick
  //sanity tests
  
  //p=1 and testing how many sick the next day
  cout<<"Testing how many sick the next day"<<endl;
  Population population(10);
  vector<Person>& people=population.get_people();
  Person& firstperson=people[0];              //testing how many sick the next day if nth person is sick(should be 2 if 0th or last get sick, three otherwise)
  Disease flu(3,1.);
  for (int iter=0;iter<20;++iter){
    if (iter==0){                         //day of initial infection
      firstperson.infect(flu);
    } else{
      for (int p=0;p<people.size();p++){                                        //iterating over people
	if (people[p].status_string()=="susceptible"){                //A susceptible person in contact with a sick neighbor has chance of getting infected
	  if (p+1<people.size() && people[p+1].status_string()=="sick"){               //person in front is sick 
	    people[p].infect(flu);                          
	  }; 
	  if (p>0 && people[p-1].status_string()=="sick"){                              //person behind is sick       
	    people[p].infect(flu);
	  };
	};
      };
    };
    int countnuminfected=population.count_infected();
    if (iter>0){
      cout<<"On iteration "<<iter<<" there are "<<countnuminfected<<" infected."<<endl;                //output number infected
    };
    population.one_more_day();                             //taking population and their status through one more day
  };

  //Testing to see how many days it takes to run out of the population
  cout<<"Testing number of days run"<<endl;
  Population population2(10);
  vector<Person>& people2=population2.get_people();
  Person& firstperson2=people2[0];
  Disease flu2(3,1.);
  for (int iter2=0;iter2<20;++iter2){
    if (iter2==0){
      firstperson2.infect(flu2);            //day of initial infection
    } else{
      for (int p=0;p<people2.size();p++){                                     //iterating over people
	if (people2[p].status_string()=="susceptible"){              //A susceptible person in contact with a sick neighbor has chance of getting infected
	  if (p+1<people2.size() && people2[p+1].status_string()=="sick"){            //person in front is sick
	    people2[p].infect(flu2);
	  };
	  if (p>0 && people2[p-1].status_string()=="sick"){                          //person behind is sick
	    people2[p].infect(flu2);
	  };
	};
      };
    };
    int countnuminfected2=population2.count_infected();
    if (iter2>0){
      cout<<"On iteration "<<iter2<<" there are "<<countnuminfected2<<" infected."<<endl;                //output number infected
    };
    population2.one_more_day();              //taking population and status through one more day
  };

  //Testing the affect of p=.5 rate of transmission
  cout<<"Testing when p=.5"<<endl;
  Population population3(10);
  vector<Person>& people3=population3.get_people();
  Person& firstperson3=people3[0];
  Disease flu3(3,.5);       //.5 rate of transmission
  for (int iter3=0;iter3<20;++iter3){
    if (iter3==0){                     //day of initial infection
      firstperson3.initial_infect(flu3);
    } else{
      for (int p=0;p<people3.size();p++){
	if (people3[p].status_string()=="susceptible"){                //A susceptible person in contact with a sick neighbor has chance of getting infected
	  if (p+1<people3.size() && people3[p+1].status_string()=="sick"){           //person in front is sick
	    people3[p].infect(flu3);
	  };
	  if (p>0 && people3[p-1].status_string()=="sick"){                             //person behind is sick
	    people3[p].infect(flu3);
	  };
	};
      };
    };
    int countnuminfected3=population3.count_infected();
    if (iter3>0){
      cout<<"On iteration "<<iter3<<" there are "<<countnuminfected3<<" infected."<<endl;     //output number infected
    };
    population3.one_more_day();        //taking population and status through one more day
  };
  return 0;
};
