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
    Polynomial& operator=(const Polynomial&);
    friend bool operator==(const Polynomial &, const Polynomial &);
    friend bool operator!=(const Polynomial &, const Polynomial &);
    Polynomial operator+(const Polynomial &) const;
    Polynomial operator-(const Polynomial &) const;
    friend Polynomial& operator+=(Polynomial &, const Polynomial &);
    friend Polynomial& operator-=(Polynomial &, const Polynomial &);
    Polynomial operator*(const Polynomial &) const;
    friend Polynomial operator*(const Polynomial &, int);
    friend Polynomial operator*(int, const Polynomial &);
    Polynomial operator/(int) const;
    friend Polynomial operator*=(Polynomial &, const Polynomial &);
    friend Polynomial operator/=(Polynomial&, int);
    friend ostream& operator<<(ostream&, const Polynomial&);
    friend istream& operator>>(istream&, Polynomial&);
    int operator[](int) const;
    int& operator[](int);
    ~Polynomial();
};

ostream& operator<<(ostream& output, const Polynomial &existing_polynomial);
istream& operator>>(istream& in, Polynomial &existing_polynomial);
Polynomial& operator+=(Polynomial &first_polynomial, const Polynomial &second_polynomial);
Polynomial& operator-=(Polynomial &first_polynomial, const Polynomial &second_polynomial);
Polynomial operator*(const Polynomial &first_polynomial, int number);
Polynomial operator*(int number, const Polynomial &first_polynomial);
Polynomial operator*=(Polynomial &first_polynomial, const Polynomial &second_polynomial);
Polynomial operator/=(Polynomial &first_polynomial, int number);
bool operator==(const Polynomial &first_polynomial, const Polynomial &second_polynomial);
bool operator!=(const Polynomial &first_polynomial, const Polynomial &second_polynomial);
#endif
