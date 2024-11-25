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
 *Index approach to Jacobi
 */
template < typename MatrixType, typename VectorType >
void JacobiSolve0( MatrixType A, VectorType sol, VectorType rhs) {
  auto tmp{sol};
  int siz=A.rows();
  for (auto& v : sol )
    v=1;
  Vector<double,5>xnew;
  for (auto it: iota(0,10)){
    for (int i=0;i<siz;i++){
      double sum=0.;
      for (int j=0;j<siz;j++){
	if (j!=i){
	  sum=sum+(A(i,j)*sol(j));
	};
      };
      xnew(i)=(rhs(i)-sum)/A(i,i);
    };
    sol=xnew;
    cout<<"it: "<<it<<'\n'<<sol<<'\n';
  };
};	
			



/*
 * Jacobi Iterative method with seq
 */
template< typename MatrixType,typename VectorType >
void JacobiSolve1( MatrixType A,VectorType sol,VectorType rhs ) {

  auto tmp{sol};
  // set initial guess to identically one
  int siz = A.rows();
  for ( auto& v : sol )
    v = 1.;
  // for a number of iteration
  //VectorXd D=A.diagonal();
  Vector<double,5> xnplus1;
  MatrixXd Diag=MatrixXd::Zero(siz,siz);
  MatrixXd Lower=MatrixXd::Zero(siz,siz);
  MatrixXd Upper=MatrixXd::Zero(siz,siz);
  for ( auto it : iota(0,10) ) {
    // one step of Jacobi
    for (int i=0;i<siz;i++){
      Diag(i,i)=A(i,i);
      if (i<(siz-1)){
	Upper.block(i,i+1,1,siz-i-1)=A.block(i,i+1,1,siz-i-1);
      };
      if (i>0){
	Lower.block(i,0,1,i)=A.block(i,0,1,i);
      }
    }
    // double sum=0.;
    // sum=sum+(A.row(i).seq(0,i)*sol.head(i)).sum();
      //   um+(A.row(i).seq(i+1,n-i-1)*sol.tail(n-i-1)).sum();
    // if (i+1<siz){
    //	sum=sum+(A.row(i).seq(i+1,n-i-1)*sol.tail(n-i-1)).sum();
    // };
    // xnplus1(i)=(rhs(i)-sum)/A(i,i);
    //};
    xnplus1=Diag.inverse()*(rhs-((Upper+Lower)*sol));
    sol=xnplus1;
    cout << "it: " << it << '\n' << sol << '\n';
  }
}

/*
 * Jacobi Iterative method with ranges
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

template < typename MatrixType, typename VectorType >
void JacobiSolve3( MatrixType A, VectorType sol, VectorType rhs) {
  auto tmp{sol};
  int siz=A.rows();
  for (auto& v : sol )
    v=1;
  Vector<double,5>xnew;
  int it=0;
  while (true){
    auto stored=sol;
    for (int i=0;i<siz;i++){
      double sum=0.;
      for (int j=0;j<siz;j++){
	if (j!=i){
	  sum=sum+(A(i,j)*sol(j));
	};
      };
      xnew(i)=(rhs(i)-sum)/A(i,i);
    };
    sol=xnew;
    cout<<"it: "<<it<<'\n'<<sol<<'\n';
    it=it+1;
    if((sol-stored).norm()<1.e-2){
      break;
    }
  };
};


template < typename MatrixType, typename VectorType >
void JacobiSolve4( MatrixType Anew, VectorType solnew, VectorType rhsnew) {
  auto tmp{solnew};
  int size=Anew.rows();
  for (auto& v : solnew )
    v=1;
  Vector<double,7>xnew2;
  int it=0;
  while (true){
    auto stored=solnew;
    for (int i=0;i<size;i++){
      double sum=0.;
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
    if((solnew-stored).norm()<1.e-4){
      break;
    }
  };
};




int main()
{

  const int siz=5;
  Matrix<double,siz,siz> A;
  Vector<double,siz> sol,rhs,tmp;
  
  cout << "Matrix size: " << A.rows() << "," << A.cols() << " (" << A.size() << ")\n";

  for ( auto& v : rhs )
    v = 1.;
  cout << rhs << '\n';

  for ( auto row : iota(0,siz) ) {
    sol(row) = static_cast<double>( row );
    A(row,row) = siz;
    for ( auto col : iota(0,siz) ) {
      if (row==col) continue;
      A(row,col) = -1;
    }
  }
  Vector<double,siz> x;
  for (int i=0;i<siz;i++){
    int sum=0;
    for (int j=0;j<siz;j++){
      int prod=A(i,j)*sol(j);
      sum=sum+prod;
    };
    x(i)=sum;
  };
  cout<<"rhs iterated soln:\n"<<x<<'\n';
  
  cout << "sol:\n" << sol << '\n';
  rhs = A*sol;
  cout << "rhs:\n" << rhs << '\n';

  cout << "================ Solve iterations style\n";
  JacobiSolve0( A,sol,rhs );
  cout << "================ Solve using seq or blocks\n";
  JacobiSolve1( A,sol,rhs );
  cout << "================ Solve 2\n";
  JacobiSolve2( A,sol,rhs );
  cout << "================ Solve until a certain precision\n";
  JacobiSolve3( A,sol,rhs );


  const int size=7;
  Matrix<double,size,size> Anew;
  Vector<double,size> solnew,rhsnew,tmpnew;

  for ( auto& v : rhsnew )
    v = 1.;
  //cout << rhs << '\n';

  for ( auto row : iota(0,size) ) {
    solnew(row) = static_cast<double>( row );
    Anew(row,row) = size;
    for ( auto col : iota(0,size) ) {
      if (row==col) continue;
      Anew(row,col) = -1;
    }
  }

  cout << "================ Solve until a certain precision varying matrix size\n";
  JacobiSolve4( Anew,solnew,rhsnew );

  Matrix<float,Dynamic,Dynamic> Af(20,20);
  // or: MatrixXf Af(20,20);

  return 0;
}
