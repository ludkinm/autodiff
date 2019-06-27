// #include "hug.hpp"
#include <iostream>
#include <eigen3/Eigen/Core>
#include <autodiff/autodiff/forward/forward.hpp>
#include <autodiff/autodiff/forward/eigen.hpp>

using namespace std;
using namespace Eigen;
using namespace autodiff;

// End-user supplied functions
dual NegSquare(const VectorXdual& x) //  base function
{
  // note gradient is -x
  return -0.5 * x.squaredNorm();
}

// The end-user function of interest
template<class... T>
dual SumNegSquare(const T&... vs)
{
  // Fold expression - return NegSquare(t0) + NegSquare(t1) + ...;
  return (NegSquare(vs) + ...);
}

// Can we take derivatives on arbitrarily many inputs?
int main(void)
{
  dual ux, uy;
  VectorXdual x, y;
  VectorXd gx, gy, g;

  // Simple one argument function
  x  = 2.0 * VectorXdual::Ones(3);
  gx = gradient(NegSquare, wrt(x), at(x), ux);
  cout << "x =\n" << x.transpose()  << endl; //  2  2  2
  cout << "gx=\n" << gx.transpose() << endl; // -2 -2 -2
  cout << "ux=\n" << ux << endl;	     // -0.5 * (2^2+2^2+2^2) = -6

  // Simple one argument function
  y = VectorXdual::Ones(5);
  gy = gradient(NegSquare, wrt(y), at(y), uy);
  cout << "y =\n" << y.transpose()  << endl; //  1  1  1  1  1
  cout << "gy=\n" << gy.transpose() << endl; // -1 -1 -1 -1 -1
  cout << "uy=\n" << uy << endl;	     // -0.5 * (1^2..) = -2.5

  // The variadic function works
  // Note length of x and y differ
  cout << "SumNegSquare(x,y) = " << ux << " + " << uy << " = " << SumNegSquare(x,y) << endl;
  // -6 + -2.5 = -8.5

  // compile error - template argument deduction/substitution failed: note: couldn't deduce template parameter ‘Function’ i.e. SumNegSquare
  // gradient(SumNegSquare, wrt(x), at(x, y));

  // Need to include the template parameters - but now gradients works
  g = gradient(SumNegSquare<VectorXdual, VectorXdual>, wrt(x), at(x, y));
  // Shouldn't these be deducible from at(x,y)?

  // check matching
  cout << g.transpose() << endl;
  cout << gx.transpose() << endl;

  g = gradient(SumNegSquare<VectorXdual, VectorXdual>, wrt(y), at(x, y));
  cout << g.transpose() << endl;
  cout << gy.transpose() << endl;

  return 0;
}
