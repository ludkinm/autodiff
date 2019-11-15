// C++ includes
#include <iostream>
using namespace std;

// autodiff include
#include <autodiff/reverse.hpp>
using namespace autodiff;

// The single-variable function for which derivatives are needed
var f(var x)
{
    return 1 + x*x;
}

int main()
{
    var x = 10.0;                            // the input variable x
    var u = f(x);                            // the output variable u
    wrt dudx {u.derivativex(x)};	     // maybe need a new type just to hold the Expr

    cout << "u = " << u.expr << endl;        // 101
    cout << "du/dx = " << dudx.expr << endl; // 20

    x.expr->val = 4.0;
    u.update();			      // update the values
    // dudx = u.derivativex(x);
    cout << "u = " << u.expr << endl;        // 17
    cout << "du/dx = " << dudx.expr << endl; //  8
    cout << "du/dx = " << dudx << endl; //  8


    // cout << endl;

    // // want to update the value of x really...

    // u.eval(); //    u = f(x);
    // cout << "u = " << u.expr << endl;

    // cout << "du/dx(x=3.0) = " << dudx.expr << endl; // print the evaluated derivative du/dx

// x = 3.0;                         // the input variable x
    // u = f(x);                        // the output variable u
    // cout << "u = " << u.expr << endl;         // print evaluation of  u
    // cout << "du/dx(x=3.0) = " << u.derivative(x) << endl; // print the evaluated derivative du/dx

    return 0;
}
