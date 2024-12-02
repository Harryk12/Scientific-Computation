//Harry Singh Kang   hkangt   hsk697
#include <iostream>
using std::cout,std::cin;
#include <chrono>
#include <string>
using std::string;

#include <ranges>
using std::ranges::views::iota,
  std::ranges::views::filter,
  std::ranges::views::transform;

#include <numeric>
using std::accumulate;

#include <Eigen/Dense>
using namespace Eigen;
// ::Matrix, Eigen::Vector;

/*
 *Index Approach
 */
template < typename MatrixType, typename VectorType >
void JacobiSolve0( MatrixType A, VectorType sol, VectorType rhs) {
  auto tmp{sol};    //save actual for comparison
  int siz=A.rows();
  for (auto& v : sol )   //initial guess for sol (vector of ones)
    v=1;
  Vector<double,5>xnew;
  for (auto it: iota(0,10)){    //double loop
    for (int i=0;i<siz;i++){
      double sum=0.;
      for (int j=0;j<siz;j++){
	if (j!=i){                        
	  sum=sum+(A(i,j)*sol(j));     //jacobi equation
	};
      };
      xnew(i)=(rhs(i)-sum)/A(i,i);
    };
    sol=xnew;
    cout<<"it: "<<it<<'\n'<<sol<<'\n';
  };
};	
			



/*
 * Jacobi Iterative method with seq/blocks
 */
template< typename MatrixType,typename VectorType >
void JacobiSolve1( MatrixType A,VectorType sol,VectorType rhs ) {

  auto tmp{sol};  //save actual for comparison
  int siz = A.rows();
  for ( auto& v : sol )    //initial guess of solution
    v = 1.;
  Vector<double,5> xnplus1;
  MatrixXd Diag=MatrixXd::Zero(siz,siz);    //dynamic matrices
  MatrixXd Lower=MatrixXd::Zero(siz,siz);
  MatrixXd Upper=MatrixXd::Zero(siz,siz);
  for ( auto it : iota(0,10) ) {
    for (int i=0;i<siz;i++){
      Diag(i,i)=A(i,i);   //diag matrix
      if (i<(siz-1)){
	Upper.block(i,i+1,1,siz-i-1)=A.block(i,i+1,1,siz-i-1);   //making upper triangle
      };
      if (i>0){
	Lower.block(i,0,1,i)=A.block(i,0,1,i);    //making lower triangle
      }
    }
    xnplus1=Diag.inverse()*(rhs-((Upper+Lower)*sol));   //jacobi equation
    sol=xnplus1;
    cout << "it: " << it << '\n' << sol << '\n';
  }
}

/*
 * Jacobi Iterative method with ranges (not needed/optional ***)
 */
template< typename MatrixType,typename VectorType >
void JacobiSolve2( MatrixType A,VectorType sol,VectorType rhs ) {

  auto tmp{sol};
  // set initial guess to identically one
  int siz = A.rows();
  for ( auto& v : sol )
    v = 1.;
  // for a number of iteration
  for ( auto it : iota(0,10) ) {
    // one step of Jacobi
    cout << "it: " << it << '\n' << sol << '\n';
  }
}

/*
 *Jacobi method until certain precision reached
 */
template < typename MatrixType, typename VectorType >
void JacobiSolve3( MatrixType A, VectorType sol, VectorType rhs) {
  auto tmp{sol};   //saved to compare
  int siz=A.rows();
  for (auto& v : sol )    //initial guess for solution
    v=1;
  Vector<double,5>xnew;
  int it=0;
  while (true){
    auto stored=sol;                            //store current value of solution to compare to end of iteration for estimate of jumpsize
    for (int i=0;i<siz;i++){
      double sum=0.;
      for (int j=0;j<siz;j++){                   //chose to use index approach here
	if (j!=i){                 
	  sum=sum+(A(i,j)*sol(j));
	};
      };
      xnew(i)=(rhs(i)-sum)/A(i,i);
    };
    sol=xnew;
    cout<<"it: "<<it<<'\n'<<sol<<'\n';
    it=it+1;
    if((sol-stored).norm()<1.e-2){       //breaks when certain tolerance is reached
      break;
    }
  };
};

/*
 *Jacobi method until certain precision reached but with bigger matrix
 */
template < typename MatrixType, typename VectorType >
void JacobiSolve4( MatrixType Anew, VectorType solnew, VectorType rhsnew) {
  auto tmp{solnew};     //saved to compare
  int size=Anew.rows();
  for (auto& v : solnew )
    v=1;                                   //initial guess for solution
  Vector<double,7>xnew2;                          //tested using a 7x7 matrix here
  int it=0;
  while (true){
    auto stored=solnew;
    for (int i=0;i<size;i++){
      double sum=0.;                                 //again index approach used
      for (int j=0;j<size;j++){
	if (j!=i){ 
	  sum=sum+(Anew(i,j)*solnew(j));
	};
      };
      xnew2(i)=(rhsnew(i)-sum)/Anew(i,i);
    };
    solnew=xnew2;
    cout<<"it: "<<it<<'\n'<<solnew<<'\n';
    it=it+1;
    if((solnew-stored).norm()<1.e-2){                                  //stops when tolerance reached
      break;
    }
  };
};




int main()
{
  const int siz=5;
  Matrix<double,siz,siz> A;
  Vector<double,siz> sol,rhs,tmp;
  //Matrix dimensions
  cout << "Matrix size: " << A.rows() << "," << A.cols() << " (" << A.size() << ")\n";

  //Setting initial guess for rhs to be vector of ones
  for ( auto& v : rhs )
    v = 1.;
  cout << "rhs initial guess: \n"<< rhs << '\n';

  //Generating sol vector and A matrix
  for ( auto row : iota(0,siz) ) {
    sol(row) = static_cast<double>( row );
    A(row,row) = siz;
    for ( auto col : iota(0,siz) ) {
      if (row==col) continue;
      A(row,col) = -1;
    }
  }

  //Using index method to compute rhs manually using A and sol
  Vector<double,siz> x;
  for (int i=0;i<siz;i++){
    int sum=0;
    for (int j=0;j<siz;j++){
      int prod=A(i,j)*sol(j);
      sum=sum+prod;
    };
    x(i)=sum;
  };
  cout<<"rhs calculated through index method:\n"<<x<<'\n';

  //Expected sol 
  cout << "sol (supposed to be):\n" << sol << '\n';
  rhs = A*sol;

  //Expected rhs - using matrix multiplication
  cout << "rhs (supposed to be):\n" << rhs << '\n';

  //Jacobi solved using index method
  cout << "================ Solve using index method:\n";
  JacobiSolve0( A,sol,rhs );

  //Jacobi solved using seq and blocks
  cout << "================ Solve using seq or blocks:\n";
  JacobiSolve1( A,sol,rhs );
  cout << "Using seq/blocks matches very close to the index approach in terms of accuracy\n";

  //Jacobi solved using ranges (not needed!)
  cout << "================ Solve using ranges (not needed):\n";
  JacobiSolve2( A,sol,rhs );

  //Jacobi solved using index until a certian precision
  cout << "================ Solve until a certain precision:\n";
  JacobiSolve3( A,sol,rhs );

  
  //generating bigger matrices and vectors
  const int size=7;
  Matrix<double,size,size> Anew;
  Vector<double,size> solnew,rhsnew,tmpnew;

  for ( auto row : iota(0,size) ) {                   //generating A matrix and sol vector
    solnew(row) = static_cast<double>( row );
    Anew(row,row) = size;
    for ( auto col : iota(0,size) ) {
      if (row==col) continue;
      Anew(row,col) = -1;
    }
  }

  rhsnew=Anew*solnew;     //actual rhs using matrix multiplication

  //Jacobi solved using index until certain precision with bigger matrix   - solution is re-intialized within the function
  cout << "================ Solve until a certain precision varying matrix size\n";
  JacobiSolve4( Anew,solnew,rhsnew );

  //Increasing diagonal dominance
  for (auto row: iota(0,size)){
    solnew(row)=static_cast<double>(row);
    Anew(row,row)=size*2;
  };
  rhsnew=Anew*solnew;   //regenerate rhs using matrix multiply
  
  cout << "================ Solve until a certain precision varying matrix size and increasing diagonal dominance\n";
  JacobiSolve4( Anew,solnew,rhsnew );

  cout<<"Increasing diagonal dominance reduces number of iterations to reach solution\n";

  Matrix<float,Dynamic,Dynamic> Af(20,20);
  // or: MatrixXf Af(20,20);

  return 0;
}
