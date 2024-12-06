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
  int variantcount=1;
  int transmissioncount=0;
  Disease(int numdayssick, double transferprobability)
    : num_days_stay_sick(numdayssick), chance_of_transmission(transferprobability) {
    transmissioncount++;
    if (transmissioncount>=5){
      variantcount++;
      transmissioncount=0;
    };
  };
  int get_days(){
    return num_days_stay_sick;
  };
  double get_transmission(){
    return chance_of_transmission;
  };
  //void touch(){
    //
  //};
};


class Person{
private:
  string status;
  int day;
  int daysleft;
  int touchcounter;
public:
  Person()
    : day(1),status("susceptible"),daysleft(-1),touchcounter(0){}; //srand(time(0));
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
    if (daysleft==0){
      status="recovered";
    };
    if (daysleft>0){
      status="sick";
      daysleft=daysleft-1;
    };
  };
  void infect(Disease s) {
    ////int startdate=day;
    //int startdatestored=startdate;
    ////int numdaysleft=s.get_days();
    /////srand(time(0));
    double r = ((double) rand() / (RAND_MAX));
    //if (day<(startdate+s.get_days())){
    ////if (numdaysleft>0){
    if(r<s.get_transmission() && status=="susceptible"){
      daysleft=s.get_days();
    };
    //if (r<s.get_transmission()){
    //if (daysleft>0){
	//////if not vaccinated
	//status="sick";
     
        ////////startdate=startdate+1;
        /////numdaysleft=numdaysleft-1;
	//daysleft=daysleft-1;   updating now
    //}else{    //if (day==startdatestored+s.get_days()){    //%% status==sick
    //	status="recovered";
    //};
    //};
  };
  bool is_recovered(){
    if(status=="recovered"){
      return true;
    } else{
      return false;
    };
  };
  void update_counter(){
    touchcounter=touchcounter+1;
  };
  int get_touch_counter(){
    return touchcounter;
  };
  void reset_touch_counter(){
    touchcounter=0;
  };

  void touch(Person i){    //Disease s
    if (touchcounter<6){
      touchcounter=touchcounter+1;
      if (i.get_touch_counter()<6){
	i.update_counter();
      };
      if(status=="susceptible" && i.status_string()=="sick"){
	Disease s(5,.81);
	infect(s);
	//status="sick";
      };
      if(i.status_string()=="susceptible" && status=="sick"){
	Disease s(5,.81);    //got to update this
	i.infect(s);
      };
    };
  };

  void vaccinate(){
    status="vaccinated";
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
  void random_vaccination(double initial_vaccination){
    double num=numberpeople*initial_vaccination;
    int numpeoplevaccinated=static_cast<int>(num);
    srand(static_cast<unsigned>(time(0)));
    set<int>indices;
    while (indices.size()<numpeoplevaccinated){
      int index=rand() % people.size();
      indices.insert(index);
    };
    for (int i:indices){
      Person& per=people[i];
      per.vaccinate();
    };
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
    int count=0;
    for (Person& p:people){
      if(p.status_string()=="vaccinated"){
	count=count+1;
      };
    };
    return count;
  };
  void one_more_day(){
    for (Person& p:people){
      p.one_more_day();
    };
  };
  vector<Person>& get_people(){
    return people;
  };
};

int main(){
  //One person status test
  Person joe;
  Disease fever(3,.9);
  for ( int step = 1; step<=10; ++step ) {
    //joe.one_more_day();
    if(step==3){
      joe.infect(fever);
    };
    cout << "On day " << step << ", Joe is "<< joe.status_string() <<"("<<joe.get_days_sick_left()<<")"<<endl;
    if (joe.is_recovered())
      break;
    joe.one_more_day();
  };
  //population test
  Population population(15);
  double initial_infect=.7;
  //population.random_infection(fever,initial_infect);
  for (int iter=1; iter<=10; ++iter){
    //population.one_more_day();
    if (iter==3){    //>
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
    };
    population.one_more_day();
  };
  //sanity tests
  Population population2(10);
  vector<Person>& people2=population2.get_people();
  //vector<Person> people2=population2.get_people();
  Person& firstperson=people2[0];
  //firstperson=people2[0];
  Disease flu2(3,.9);
  //////firstperson.infect(flu2);
  //population2.one_more_day();
  //int countnuminfected2=population2.count_infected();
  //cout<<countnuminfected2<<endl;
  //#if 0
  for (int iter2=0;iter2<15;++iter2){
    //population2.one_more_day();
    //////firstperson.infect(flu2);
    if (iter2==0){
      firstperson.infect(flu2);
    } else{
      for (int p=0;p<people2.size();p++){
	if (people2[p].status_string()=="susceptible"){
	  if (p+1<people2.size() && people2[p+1].status_string()=="sick"){       //
	    people2[p].infect(flu2);
	  };
	  if (p>0 && people2[p-1].status_string()=="sick"){       //
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

  //vaccinated test
  Population population3(10);
  double randvacc=.3;
  population3.random_vaccination(randvacc);
  cout<<"Number of people vaccinated: "<<population3.count_vaccinated()<<endl;
  vector<Person>& people3=population3.get_people();
  Person& nperson=people3[0];
  Disease flu3(3,.9);
  //int countnuminfected3=population3.count_infected();
  //cout<<countnuminfected3<<endl;
  for (int iter3=0;iter3<15;++iter3){
    //population2.one_more_day();
    //////firstperson.infect(flu2);
    if (iter3==0){
      nperson.infect(flu3);
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



  //random interations
  Population population4(10000);
  double randvac=.1;
  population4.random_vaccination(randvac);
  cout<<"Number of people vaccinated: "<<population4.count_vaccinated()<<endl;
  vector<Person>& people4=population4.get_people();
  Person& nthperson=people4[11];
  Disease flu4(5,.85);

  //////////////////nthperson.infect(flu4);
  //population4.one_more_day();
  //int countnuminfected4=population4.count_infected();
  //cout<<countnuminfected4<<endl;
  srand(time(0));
  for (int iter4=0;iter4<40;++iter4){
    if (iter4==0){
      nthperson.infect(flu4);
    }else{
      int indexiter=0;
      //int rindex;
      //srand(time(0));
      for (Person& indiv:people4){
	while((indiv.get_touch_counter())<6){ 
	  //srand(time(0));
	  int rindex=rand()%10000;
	  if (rindex!=indexiter){
	    indiv.touch(people4[rindex]);    //flu4
	  };
	};
	indexiter=indexiter+1;
      };
    };
    population4.one_more_day();
    int countnuminfected4=population4.count_infected();
    if (iter4>=0){
      cout<<"On iteration "<<iter4<<" there are "<<countnuminfected4<<" infected."<<endl;
    };
    for (Person& indivs:people4){
      indivs.reset_touch_counter();
    };



    
    //population4.one_more_day();
  };
	
    //////population2.one_more_day();
    //////firstperson.infect(flu2);
    //while(population4.peopletouchedceiling()<100)
      

    

#if 0
    if (iter4==0){
      nthperson.infect(flu4);
    } else{
      for (int p=0;p<people4.size();p++){
	//if (people3[p].status_string()=="susceptible"){
	if (p+1<people4.size()){     //&& people3[p+1].status_string()=="sick"
	  people4[p].touch(people4[p+1],flu4);
        };
        if (p>0){        //&& people3[p-1].status_string()=="sick"
          people4[p].touch(people4[p-1],flu4);
        };
        //};
      };
    };
    int countnuminfected4=population4.count_infected();
    if (iter4>0){
      cout<<"On iteration "<<iter4<<" there are "<<countnuminfected3<<" infected."<<endl;
    };
    population4.one_more_day();
    
  };
#endif
      
  return 0;
};
