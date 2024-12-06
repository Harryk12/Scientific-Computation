


class Disease{
private:
  int num_days_stay_sick;
  double chance_of_transmission;
public:
  //int variantcount=1;
  //int transmissioncount=0;
  Disease(int numdayssick, double transferprobability)
    : num_days_stay_sick(numdayssick), chance_of_transmission(transferprobability) {};
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
  int statuscount;    //didnt have
public:
  Person()
    : day(1),status("susceptible"),daysleft(-1),touchcounter(0),statuscount(0){srand(time(0));}; //srand(time(0));
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
      statuscount++;
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
    if(r<s.get_transmission() && statuscount<variantcounter){
      daysleft=s.get_days();

      transmissioncounter++;
      if (transmissioncounter>=20000){
	if (variantcounter<3){
	  variantcounter++;
	};
	transmissioncounter=0;
      };
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
  void initial_infect(Disease s){
    daysleft=s.get_days();
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
    Disease s(10,.1);
    if (touchcounter<6){
      touchcounter=touchcounter+1;
      if (i.get_touch_counter()<6){
	i.update_counter();
      };
      if(status == "susceptible" && i.status_string()=="sick"){ //|| status=="recovered") statuscount<=i.statuscount){      //status=="susceptible" && i.status_string()=="sick"
	//Disease s(5,.81);
	infect(s);
      };
      if(status == "recovered" && i.status_string()=="sick" && statuscount<i.statuscount){
	infect(s);
      };
      
      if(status=="sick" && i.status_string()=="susceptible"){        //i.status_string()=="susceptible" && status=="sick"
	//Disease s(5,.81);    //got to update this
	i.infect(s);
      };
      if(status=="sick" && i.status_string()=="recovered" && i.statuscount<statuscount){
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
