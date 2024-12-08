


class Disease{
private:
  int num_days_stay_sick;
  double chance_of_transmission;
public:
  Disease(int numdayssick, double transferprobability)
    : num_days_stay_sick(numdayssick), chance_of_transmission(transferprobability) {};     //important information is how many days the disease lasts and transfer probability
  int get_days(){
    return num_days_stay_sick;             //get functions
  };
  double get_transmission(){
    return chance_of_transmission;
  };
};


class Person{
private:
  string status;           //status of person
  int day;                  //current day
  int daysleft;              //days left being sick
  int touchcounter;          //interactions per day
  int statuscount;           //stored integer to track variant of disease
public:
  Person()
    : day(1),status("susceptible"),daysleft(-1),touchcounter(0),statuscount(0){srand(time(0));};     //initializers
  int get_days_sick_left(){
    if (status=="sick"){
      return daysleft+1;    //for cout in first sim
    } else{
      return -1;
    };
  };
  string status_string(){   //returns person's state as string
    return status;
  };
  void one_more_day(){     //update person's status to next day
    day=day+1;              //update day
    if (daysleft==0){          //if sick counter goes to 0, they recovered
      status="recovered";      
      statuscount++;            //in the case of multiple variants, this matches the variant counter until the variant mutates
    };
    if (daysleft>0){           //if daysleft is still counting, they're sick
      status="sick";
      daysleft=daysleft-1;
    };
  };
  void infect(Disease s) {
    double r = ((double) rand() / (RAND_MAX));                //random number to see if under rate of transmission-if so, then can get sick
    if(r<s.get_transmission() && statuscount<variantcounter){      //statuscount if what variant the person is currently immune from; if less than the current variant, can get sick
      daysleft=s.get_days();       //both conditions trigger the days counter, letting one_more_day() know the person is sick

      transmissioncounter++;        //a successful infection counts as a transmission
    };
    if (transmissioncounter>=50000){             //if transmissions exceed this number, the disease mutates and variant counter increases
      if (variantcounter<3){                 //there are this many variants
        variantcounter++;
      };
      transmissioncounter=0;                  //mutation means number of transmissions needs to count over again
    };
  };
  void initial_infect(Disease s){     //unlike infect(), this doesn't check if under transmission rate because it's used for the first person getting the disease (need to trigger the sim to start)
    daysleft=s.get_days();
  };
  bool is_recovered(){
    if(status=="recovered"){                  //checks for recovery
      return true;
    } else{
      return false;
    };
  };
  void update_counter(){
    touchcounter=touchcounter+1;               //updates touchcounter since it's private
  };
  int get_touch_counter(){                    //get function for touchcounter
    return touchcounter;
  };
  void reset_touch_counter(){                   //reset funciton for touchcounter at end of day when met quota
    touchcounter=0;
  };

  void touch(Person i,Disease d){    
    Disease s=d;                            //object used to trigger an infect (since every infect counts a transmission)
    if (touchcounter<6){                 //limiting interactions per day to 6
      touchcounter=touchcounter+1;
      if (i.get_touch_counter()<6){
	i.update_counter();
      };
      if(status == "susceptible" && i.status_string()=="sick"){       //if person isn't sick but the touched one is, person gets infected
	infect(s);
      };
      if(status == "recovered" && i.status_string()=="sick" && statuscount<i.statuscount){  //recovered is just for the first variant; after that statuscounts are compared to see if person gets infected
	infect(s);
      };
      
      if(status=="sick" && i.status_string()=="susceptible"){        //if person is sick but touched isn't, the touched person gets infected
	i.infect(s);
      };
      if(status=="sick" && i.status_string()=="recovered" && i.statuscount<statuscount){  //recovered is just for first variant; after that statuscounts are comparede to see if touched person gets infected
	i.infect(s);
      };
    };
  };
  void vaccinate(){
    status="vaccinated";
  };
};



class Population{
private:
  vector<Person>people;        //population is a vector of persons
  int numberpeople;            //count of persons
public:
  Population (int npeople):numberpeople(npeople),people(npeople) {};        //a number is passed in to size the vector of persons and the count
  
  void random_infection(Disease fever,double initial_infection){  
    double num=numberpeople*initial_infection;      
    int numpeopleinfected=static_cast<int>(num);      //the size of the population (int) that will get infected initially
    srand(static_cast<unsigned>(time(0)));
    set<int>indices;    
    while (indices.size()<numpeopleinfected){
      
      int index=rand() % people.size();                   //creating a vector/set of random indices that will represent those infected 
      indices.insert(index);
    };
    for (int i:indices){
      Person& per=people[i];
      per.infect(fever);                            //infecting the persons with such indices
    };
  };
  void random_vaccination(double initial_vaccination){
    double num=numberpeople*initial_vaccination;
    int numpeoplevaccinated=static_cast<int>(num);      //the size of the population (int) that will get vaccinated initially
    srand(static_cast<unsigned>(time(0)));
    set<int>indices;
    while (indices.size()<numpeoplevaccinated){
      int index=rand() % people.size();              //creating a vector/set of random indices that will represent those vaccinated
      indices.insert(index);
    };
    for (int i:indices){
      Person& per=people[i];                //vaccinating those with such indices
      per.vaccinate();
    };
  };
  int count_infected(){
    int count=0;
    for (Person& p:people){
      if(p.status_string()=="sick"){
	count=count+1;                         //counts and returns every person in the vector that's infected
      };
    }
    return count;
  };
  int count_vaccinated(){
    int count=0;
    for (Person& p:people){
      if(p.status_string()=="vaccinated"){                  //counts and returns every person in the vecotr that's vaccinated
	count=count+1;
      };
    };
    return count;
  };
  void one_more_day(){
    for (Person& p:people){                 //this triggers each person in the population to go through one more day
      p.one_more_day();
    };
  };
  vector<Person>& get_people(){
    return people;                            //get the people vector from private
  };
};
