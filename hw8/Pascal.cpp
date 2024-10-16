//Harry S Kang hsk697 hkangt

#include <iostream>
#include <vector>
using std::vector;
using std::endl;
using std::cout;


class storage {
protected:
  vector<int>data;
public:
  //constructor for storage parent class
  storage(int n) {};
  //set function is going to be overriten in Pascal child class
  virtual void set(int i, int j){};
  //get function 
  int get(int i, int j){
    //finding index
    int sum=0;
    for (int back=i-1;back>=0;back--){
      sum=sum+back;
    };
    //accounting for if current constructed triangle/array is big enough to index the value of interest
    if (sum+j>data.size()){
      data.insert(data.end(),(sum+i)-data.size(),0);
      //using set in Pascal function
      set(i,j);
    };
    //if big enough, return the number
    return data.at(sum+j);
  };
  
};

class Pascal: public storage {
public:
  //storage function in Pascal is initialized with 0 for all values
  Pascal(int n) : storage(n)  {
    for (int i=1;i<=n;i++){
      for (int j=1;j<=i;j++){
	data[(i-1)+(j-1)]=0;
      };
    };
  };
  //factorial calculation
   int factorial(int factor){
     int runningproduct=1;
     if (factor==0){
       return 1;
     } else{
       while(factor>0){
	 runningproduct=factor*runningproduct;
	 factor--;
       };
       return runningproduct; 
     };

   };
  //set function for Pascal class.   
   void set(int k, int l) override{
     //finding index
     int sum=0;
     for (int back=k-1;back>=0;back--){
       sum=sum+back;
     };
     //filling all rows and columns including where current point of interest is
     for (int iter=1;iter<=k;iter++){
       for (int jiter=1;jiter<=iter;jiter++){
	 data[(iter-1)+(jiter-1)]=factorial(iter-1)/(factorial(jiter-1)*factorial((iter-1)-(jiter-1))); 
       };
     };
   };
  //get function in Pascal that calls/uses get from parent
   int getvalue(int m, int n){
     return get(m,n);
   };
  //printing result
   void print(int p, int q){
     int todisplay=getvalue(p,q);
     cout<<todisplay<<endl;
   };
};
//main function
//args to ignore error
int main(int argc, char **argv){
  //creating the problem statement
  Pascal triangle(7);
  triangle.print(3,2);
  return 0;
};
