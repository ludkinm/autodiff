// C++ includes
#include <iostream>
using namespace std;

// autodiff include
#include <autodiff/reverse.hpp>
using namespace autodiff;

var g(const var& t)
{
    return 1 + t*t;
}

var f(const var& x)
{
    return 1 + x*x;
}

int main()
{
    var t = 3.0;
    var x = g(t);
    var u = f(x);
    wrt dudx {u.derivativex(x)};
    wrt dxdt {u.derivativex(x)};
    wrt dudt {u.derivativex(t)};

    cout << "t: " << t << endl; // 3
    cout << "x: " << x << endl; // 10 = 1+(3)*(3)
    cout << "u: " << u << endl; // 101 = 1+(1+(3*3))*(1+(3*3))
    cout << "du/dx: " << dudx << " = " << dudx.expr << endl;
    cout << "dx/dt: " << dxdt << " = " << dxdt.expr << endl;
    cout << "du/dt: " << dudt << " = " << dudt.expr << endl;

    return 0;
}
