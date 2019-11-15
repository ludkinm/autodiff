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

    x = 4.0;				     // would be nice if this triggered a tree update
    v.update();                              // update the values
    cout << "u = " << u.expr << endl;        // 17
    cout << "du/dx = " << dudx.expr << endl;
    cout << "du/dx = " << dudx << endl;      //  8

    return 0;
}
