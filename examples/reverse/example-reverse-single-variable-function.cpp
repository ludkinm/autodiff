// C++ includes
#include <iostream>
using namespace std;

// autodiff include
#include <autodiff/reverse.hpp>
using namespace autodiff;

// The single-variable function for which derivatives are needed
var f(var x)
{
    return 1 + x + x*x + 1/x + log(x);
}

int main()
{
    var x = 2.0;                         // the input variable x
    var u = f(x);                        // the output variable u
    cout << "u = " << u.expr << endl;         // print evaluation of  u

    var dudx = u.derivativex(x);
    cout << "du/dx(x=2.0) = " << dudx.expr << endl; // print the evaluated derivative du/dx

    // want to update the value of x really...
    x.expr->val = 3.0;
    u = f(x);
    cout << "du/dx(x=3.0) = " << dudx.expr << endl; // print the evaluated derivative du/dx

// x = 3.0;                         // the input variable x
    // u = f(x);                        // the output variable u
    // cout << "u = " << u.expr << endl;         // print evaluation of  u
    // cout << "du/dx(x=3.0) = " << u.derivative(x) << endl; // print the evaluated derivative du/dx

    return 0;
}
