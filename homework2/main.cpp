#include <iostream>
#include "polynomial.h"
#include <sstream>
#include <assert.h>


using namespace std;

void checkOut() {
    stringstream ss;
    ss << Polynomial(0, 2, new int[3]{1, 2, 3}) << " ";
    ss << Polynomial(1, 2, new int[2]{-3, 4}) << " ";
    ss << Polynomial(-1, 2, new int[4]{1, -3, 0, -1}) << " ";
    ss << Polynomial() << " ";
    ss << Polynomial(0, 2, new int[3]{0, 3, -3}) << " ";
    ss << Polynomial(-2, 2, new int[5]{1, 0, 0, 0, 1}) << " ";
    assert(ss.str() == "3x^2+2x+1 4x^2-3x -x^2-3+x^-1 0 -3x^2+3x x^2+x^-2 ");
}

void PolynomialOperators() {
    stringstream ss;
    const auto a =  Polynomial(0, 2, new int[3]{1, 2, 3}) ;
    const auto b = Polynomial(1, 2, new int[2]{-3, 4});
    auto c = Polynomial(-1, 2, new int[4]{1, -3, 0, -1});
    const auto d = Polynomial();
    const auto e =  Polynomial(0, 2, new int[3]{0, 3, -3});
    const auto f = Polynomial(-2, 2, new int[5]{1, 0, 0, 0, 1});
    assert(a * b == b * a);
    assert(d * e == d);
    assert(a * b * c == a * (b * c));
    assert(a * b == Polynomial(1, 4, new int[4]{-3, -2, -1, 12}));
    assert(a + b == b + a);
    assert(d + e == e);
    assert(a + b + c == a + (b + c));
    assert(5 * a == a * 5);
    assert(a + b + c == Polynomial(-1, 2, new int[4]{1, -2, -1, 6}));
    assert(c / 2 == Polynomial(0, 0, new int[1]{-1}));
    assert(c.get(4) == -18.75);
    assert(a[1] == 2);
    assert(a[10] == 0);
    c[5] = 3;
    assert(c.get(4) == 3053.25);
    assert((-c) == (-(-(-c))));
    auto h = -c;
    assert(c[5] == 3 && h[5] == -3);
    assert((-c)[5] == -3);
   	auto g = b;
   	g[3] = 0;
   	assert(g == b);
}


int main() {
    checkOut();
    PolynomialOperators();
    return 0;
}
