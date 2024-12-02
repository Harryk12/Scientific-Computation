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


class Disease{
private:
  int num_days_stay_sick;
  double chance_of_transmission;
public:
  Disease(int numdayssick, double transferprobability)
    : num_days_stay_sick(numdayssick), chance_of_transmission(transferprobability) {};
  int get_days(){
    return num_days_stay_sick;
  };
  double get_transmission(){
    return chance_of_transmission;
  };
  void touch(){
    //
  };
};


class Person{
private:
  string status;
  int day;
  int daysleft;
public:
  Person()
    : day(0),status("susceptible"),daysleft(){};
  int get_days_sick_left(){
    if (status=="sick"){
      return daysleft+1;
    } else{
      return -1;
    };
  };
  string status_string(){   //returns person's state as string
    return status;
  };
  void one_more_day(){     //update person's status to next day
    day=day+1;
  };
  void infect(Disease s) {
    ////int startdate=day;
    //int startdatestored=startdate;
    ////int numdaysleft=s.get_days();
    double r = ((double) rand() / (RAND_MAX));
    //if (day<(startdate+s.get_days())){
    ////if (numdaysleft>0){
    if(r<s.get_transmission() && status=="susceptible"){
      daysleft=s.get_days();
    };
    if (r<s.get_transmission()){
      if (daysleft>0){
	//if not vaccinated
	status="sick";
     
        //startdate=startdate+1;
        ////numdaysleft=numdaysleft-1;
	daysleft=daysleft-1;
      }else{    //if (day==startdatestored+s.get_days()){    //%% status==sick
	status="recovered";
      };
    };
  };
  bool is_recovered(){
    if(status=="recovered"){
      return true;
    } else{
      return false;
    };
  };

  void touch(Person i,Disease s){
    if(i.status_string()=="sick"){
      infect(s);
      //status="sick";
    };
  };

  
  //void get_infected(){
  void get_vaccinated(){

  };
  void progress_by_one_day(){

  };
};



class Population{
private:
  vector<Person>people;
  int numberpeople;
public:
  Population (int npeople):numberpeople(npeople),people(npeople) {};
  
  void random_infection(Disease fever,double initial_infection){  //change double
    double num=numberpeople*initial_infection;
    int numpeopleinfected=static_cast<int>(num);
    srand(static_cast<unsigned>(time(0)));
    set<int>indices;    //set previously
    while (indices.size()<numpeopleinfected){
      
      int index=rand() % people.size();
      indices.insert(index);
    };
    for (int i:indices){
      Person& per=people[i];
      per.infect(fever);
    };
  };
  void random_vaccination(){
    
  };
  int count_infected(){
    int count=0;
    for (Person& p:people){
      if(p.status_string()=="sick"){
	count=count+1;
      };
    }
    return count;
  };
  int count_vaccinated(){
    return 0;
  };
  void one_more_day(){
    for (Person& p:people){
      p.one_more_day();
    };
  };
  vector<Person>get_people(){
    return people;
  };
};

int main(){
  //One person status test
  Person joe;
  Disease fever(3,.9);
  for ( int step = 1; step<=10; ++step ) {
    joe.one_more_day();
    if(step>3){
      joe.infect(fever);
    };
    cout << "On day " << step << ", Joe is "<< joe.status_string() <<"("<<joe.get_days_sick_left()<<")"<<endl;
    if (joe.is_recovered())
      break;
  };
  //population test
  Population population(15);
  double initial_infect=.7;
  //population.random_infection(fever,initial_infect);
  for (int iter=1; iter<=10; ++iter){
    population.one_more_day();
    if (iter>3){
      population.random_infection(fever,initial_infect);
    };
    int countnuminfected=population.count_infected();
    cout<<"In step "<<iter<< " #sick:  "<<countnuminfected<<" : ";
    for (Person& indiv:population.get_people()){     //const Person b4
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
    }
  };
  //sanity tests
  Population population2(10);
  vector<Person> people2=population2.get_people();
  Person firstperson=people2[0];
  Disease flu2(3,1.);
  firstperson.infect(flu2);
  int countnuminfected2=population2.count_infected();
  cout<<countnuminfected2<<endl;
  #if 0
  for (int iter2=1;iter2<=10;++iter2){
    population2.one_more_day();
    //firstperson.infect(flu2);
    int iterator=0;
    for (Person& invid2:people2){
      if(people2[iterator].status_string()=="sick"){
	people2[iterator].infect(flu2);
      } else{
	if(iterator+1<people2.size() && people2[iterator+1].status_string()=="sick"){
	  invid2.touch(people2[iterator+1],flu2);
	};
	if (iterator>0 && people2[iterator-1].status_string()=="sick"){
	  invid2.touch(people2[iterator-1],flu2);
	};
      };
      iterator++;
    };
    int countnuminfected2=population2.count_infected();
    cout<<"On iteration "<<iter2<<" there are "<<countnuminfected2<<" infected."<<endl;
  };
  #endif
      
  return 0;
};
