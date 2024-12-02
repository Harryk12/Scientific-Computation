//Harry S Kang   hsk697    hkangt
#include <vector>

class polynomial {
private:
  std::vector<double> coefficients;
public:
  polynomial();
  polynomial( std::vector<double> c );
  bool is_odd() const;
  double evaluate_at(double x) const;
  double operator()(double x) const { return evaluate_at(x); };
};

void find_initial_bounds( const polynomial&,double &left,double &right);

void move_bounds_closer( const polynomial&,double& left,double& right,bool trace=false );

double find_zero( const polynomial&,double precision,bool trace=false );
