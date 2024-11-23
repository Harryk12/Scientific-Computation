#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using std::string;
using std::cout;
using std::endl;
using std::vector;


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
  int dayofinfection;
public:
  Person()
    : day(0),status("susceptible"),dayofinfection(){};
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
      dayofinfection=day;
    };
    if (r<s.get_transmission()){
      if (day<s.get_days()+dayofinfection){
	//if not vaccinated
	status="sick";
     
        //startdate=startdate+1;
        ////numdaysleft=numdaysleft-1;
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
  //void get_infected(){
  void get_vaccinated(){

  };
  void progress_by_one_day(){

  };
};



class Population{
private:
  vector<Person>people;
public:
  //Population
  
  //  void random_infection(Disease fever,double initial_infection){  //change double
    
  //};
  void random_vaccination(){

  };
  int count_infected(){
    
    return 0;
  };
  int count_vaccinated(){
    return 0;
  };
  void one_more_day(){
    //heart of code



  };
};

int main(){
  Person joe;
  Disease fever(3,.9);
  for ( int step = 1; step<=10; ++step ) {
    joe.one_more_day();
    if(step>3){
      joe.infect(fever);
    };
    cout << "On day " << step << ", Joe is "<< joe.status_string() <<endl;
    if (joe.is_recovered())
      break;
  };
  return 0;
};
