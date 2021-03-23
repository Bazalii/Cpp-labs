#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <sstream>


using namespace std;

class Polynomial{
private:
    int minimum_degree, maximum_degree;
    int * array_of_indexes;
public:
    Polynomial();
    Polynomial(int, int, const int *);
    Polynomial(const Polynomial &);
    double get(int) const;
    Polynomial& minus();
    Polynomial& operator=(const Polynomial&);
    friend bool operator==(const Polynomial &, const Polynomial &);
    friend bool operator!=(const Polynomial &, const Polynomial &);
    friend Polynomial operator+(const Polynomial &, const Polynomial &);
    friend Polynomial operator-(const Polynomial &, Polynomial &);
    friend Polynomial operator-(const Polynomial&);
    Polynomial& operator+=(const Polynomial &);
    Polynomial& operator-=(Polynomial &);
    friend Polynomial operator*(const Polynomial &, const Polynomial &);
    friend Polynomial operator*(const Polynomial &, int);
    friend Polynomial operator*(int, const Polynomial &);
    friend Polynomial operator/(const Polynomial &, int);
    Polynomial operator*=(const Polynomial &);
    Polynomial operator/=(int);
    friend ostream& operator<<(ostream&, const Polynomial&);
    friend istream& operator>>(istream&, Polynomial&);
    int operator[](int) const;
    int& operator[](int);
    ~Polynomial();
};
#endif
