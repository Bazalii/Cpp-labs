#include "polynomial.h"
#include <iostream>
#include <algorithm>

Polynomial::Polynomial(){
    this->minimum_degree = 0;
    this->maximum_degree = 0;
    this->array_of_indexes = new int[1];
    this->array_of_indexes[0] = 0;
}
Polynomial::Polynomial(int first_degree, int second_degree, const int *array){
    this->minimum_degree = first_degree;
    this->maximum_degree = second_degree;
    this->array_of_indexes = new int[this->maximum_degree - this->minimum_degree + 1];
    for (int i = 0; i <= this->maximum_degree - this->minimum_degree; ++i) {
        this->array_of_indexes[i] = array[i];
    }
}
Polynomial::Polynomial(const Polynomial &copy_polynomial){
    this->minimum_degree = copy_polynomial.minimum_degree;
    this->maximum_degree = copy_polynomial.maximum_degree;
    this->array_of_indexes = new int[copy_polynomial.maximum_degree - copy_polynomial.minimum_degree + 1];
    for (int i = 0; i <= this->maximum_degree - this->minimum_degree; ++i) {
        this->array_of_indexes[i] = copy_polynomial.array_of_indexes[i];
    }
}
double Polynomial::get(int number) const{
    double result = 0, value = 1;
    if (this->minimum_degree < 0){
        for (int i = 0; i < -this->minimum_degree; ++i) {
            value /= number;
        }
    }
    else if (this->minimum_degree > 0){
        for (int i = 0; i < this->minimum_degree; ++i) {
            value *= number;
        }
    }
    //fixed get O(n)
    for_each(this->array_of_indexes, this->array_of_indexes + this->maximum_degree - this->minimum_degree + 1,[&](int &x){result += x * value; value *= number;});
    return result;
}
Polynomial& Polynomial::operator=(const Polynomial &existing_polynomial){
    this->minimum_degree = existing_polynomial.minimum_degree;
    this->maximum_degree = existing_polynomial.maximum_degree;
    delete []this->array_of_indexes;
    this->array_of_indexes = new int[this->maximum_degree - this->minimum_degree + 1];
    for (int i = 0; i <= this->maximum_degree - this->minimum_degree; ++i) {
        this->array_of_indexes[i] = existing_polynomial.array_of_indexes[i];
    }
    return *this;
}
bool operator==(const Polynomial &first_polynomial, const Polynomial &second_polynomial){
    int minimum, maximum, first_index, second_index;
    if (first_polynomial.minimum_degree == second_polynomial.minimum_degree && first_polynomial.maximum_degree == second_polynomial.maximum_degree){
        for (int i = 0; i <= second_polynomial.maximum_degree - second_polynomial.minimum_degree; ++i) {
            if (first_polynomial.array_of_indexes[i] != second_polynomial.array_of_indexes[i])
                return false;
        }
    }
    minimum = (first_polynomial.minimum_degree < second_polynomial.minimum_degree) ? first_polynomial.minimum_degree : second_polynomial.minimum_degree;
    maximum = (first_polynomial.maximum_degree > second_polynomial.maximum_degree) ? first_polynomial.maximum_degree : second_polynomial.maximum_degree;
    for (int i = minimum; i <= maximum; ++i) {
        if (first_polynomial.minimum_degree <= i && i <= first_polynomial.maximum_degree)
            first_index = first_polynomial.array_of_indexes[i - first_polynomial.minimum_degree];
        else
            first_index = 0;
        if (second_polynomial.minimum_degree <= i && i <= second_polynomial.maximum_degree)
            second_index = second_polynomial.array_of_indexes[i - second_polynomial.minimum_degree];
        else
            second_index = 0;
        if (first_index != second_index)
            return false;
    }
    return true;
}
bool operator!=(const Polynomial &first_polynomial, const Polynomial &second_polynomial){
    return !operator==(first_polynomial, second_polynomial);
}
Polynomial operator+(const Polynomial &first_polynomial, const Polynomial &second_polynomial){
    Polynomial new_polynomial { first_polynomial };
    return new_polynomial += second_polynomial;
}
Polynomial operator-(const Polynomial &first_polynomial, const Polynomial &second_polynomial){
    Polynomial new_polynomial { first_polynomial };
    return new_polynomial -= second_polynomial;
}
Polynomial operator-(const Polynomial& existing_polynomial){
    int *array = new int[existing_polynomial.maximum_degree - existing_polynomial.minimum_degree + 1];
    for (int i = 0; i <= existing_polynomial.maximum_degree - existing_polynomial.minimum_degree; ++i) {
        array[i] = -existing_polynomial.array_of_indexes[i];
    }
    return Polynomial(existing_polynomial.minimum_degree, existing_polynomial.maximum_degree, array);
}
//fixed copy-paste +-
Polynomial& Polynomial::operator+=(const Polynomial &second_polynomial){
    int minimum, maximum, first_index, second_index;
    minimum = (this->minimum_degree < second_polynomial.minimum_degree) ? this->minimum_degree : second_polynomial.minimum_degree;
    maximum = (this->maximum_degree > second_polynomial.maximum_degree) ? this->maximum_degree : second_polynomial.maximum_degree;
    int *array = new int[maximum - minimum + 1];
    for (int i = minimum; i <= maximum; ++i) {
        if (this->minimum_degree <= i && i <= this->maximum_degree)
            first_index = this->array_of_indexes[i - this->minimum_degree];
        else
            first_index = 0;
        if (second_polynomial.minimum_degree <= i && i <= second_polynomial.maximum_degree)
            second_index = second_polynomial.array_of_indexes[i - second_polynomial.minimum_degree];
        else
            second_index = 0;
        array[i - minimum] = first_index + second_index;
    }
    *this = Polynomial(minimum, maximum, array);
    return *this;
}
Polynomial& Polynomial::operator-=(const Polynomial &second_polynomial){
    return *this += -(second_polynomial);
}
Polynomial operator*(const Polynomial &first_polynomial, const Polynomial &second_polynomial){
    Polynomial new_polynomial { first_polynomial };
    return new_polynomial *= second_polynomial;
}
//fixed *=
Polynomial operator*(const Polynomial &first_polynomial, int number){
    Polynomial new_polynomial = Polynomial(0, 0, new int[1]{number});
    //fixed for_each
    /* added for_each where it is convenient and possible*/
    return new_polynomial *= first_polynomial;
}
Polynomial operator*(int number, const Polynomial &first_polynomial){
    return first_polynomial * number;
}
Polynomial operator/(const Polynomial &existing_polynomial, int number){
    Polynomial new_polynomial { existing_polynomial };
    return new_polynomial /= number;
}
Polynomial Polynomial::operator*=(const Polynomial &second_polynomial){
    if  (*this == Polynomial() || second_polynomial == Polynomial())
        return Polynomial();
    int size = (this->maximum_degree - this->minimum_degree + 1) * (second_polynomial.maximum_degree - second_polynomial.minimum_degree + 1);
    int *array = new int[size];
    int *degree = new int[size];
    int iter = 0;
    int new_size = this->maximum_degree + second_polynomial.maximum_degree - (this->minimum_degree + second_polynomial.minimum_degree) + 1;
    int minimal = this->minimum_degree + second_polynomial.minimum_degree;
    for (int i = 0; i <= this->maximum_degree - this->minimum_degree; ++i) {
        for (int j = 0; j <= second_polynomial.maximum_degree - second_polynomial.minimum_degree; ++j) {
            array[iter] = this->array_of_indexes[i] * second_polynomial.array_of_indexes[j];
            degree[iter] = this->minimum_degree + second_polynomial.minimum_degree + i + j;
            iter += 1;
        }
    }
    delete []this->array_of_indexes;
    this->array_of_indexes = new int[new_size];
    for (int i = 0; i < new_size; ++i) {
        this->array_of_indexes[i] = 0;
    }
    for (int i = 0; i < size; ++i) {
        this->array_of_indexes[degree[i] - minimal] += array[i];
    }
    this->minimum_degree = minimal;
    this->maximum_degree = this->maximum_degree + second_polynomial.maximum_degree;
    return *this;
}
Polynomial Polynomial::operator/=(int number){
    for_each(this->array_of_indexes, this->array_of_indexes + this->maximum_degree - this->minimum_degree + 1, [&](int &x){x /= number;});
    return *this;
}
ostream& operator<<(ostream &out, const Polynomial &existing_polynomial){
    if (existing_polynomial.maximum_degree == 0 && existing_polynomial.minimum_degree == 0 && existing_polynomial.array_of_indexes[0] == 0)
        out << "0";
    for (int i = existing_polynomial.maximum_degree ; i >= existing_polynomial.minimum_degree; --i) {
        if ((1 < i && i < existing_polynomial.maximum_degree) || i <= -1){
            if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] > 1)
                out << "+" << existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] << "x^" << i;
            else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] < -1)
                out << existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] << "x^" << i;
            else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] == 1)
                out << "+x^" << i;
            else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] == -1)
                out << "-x^" << i;
        }
        else if (i == 0){
            if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] >= 1)
                out << "+" << existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree];
            else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] <= -1)
                out << existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree];
        }
        else if (i == 1){
            if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] > 1)
                out << "+" << existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] << "x";
            else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] < -1)
                out << existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] << "x";
            else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] == 1)
                out << "+" << "x";
            else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] == -1)
                out << "-" << "x";
        }
        else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] != 0){
            if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] > 1)
                out << existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] << "x^" << i;
            else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] < -1)
                out << existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] << "x^" << i;
            else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] == 1)
                out << "x^" << i;
            else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] == -1)
                out << "-x^" << i;
        }
    }
    return out;
}
istream& operator>>(istream &in, Polynomial &existing_polynomial){
    in >> existing_polynomial.minimum_degree;
    in >> existing_polynomial.maximum_degree;
    for (int i = 0; i <= existing_polynomial.maximum_degree - existing_polynomial.minimum_degree; ++i) {
        in >> existing_polynomial.array_of_indexes[i];
    }
    return in;
}
int Polynomial::operator[](int index) const {
    if (index > (this->maximum_degree - this->minimum_degree + 1))
        return 0;
    else
        return array_of_indexes[index];
}
int& Polynomial::operator[](int index){
    int size = index - this->minimum_degree + 1;
    if (index > this->maximum_degree){
        int *array = new int[size];
        for (int i = 0; i <= this->maximum_degree - this->minimum_degree; ++i) {
            array[i] = this->array_of_indexes[i];
        }
        delete this->array_of_indexes;
        this->array_of_indexes = new int[size];
        for (int i = 0; i < size; ++i) {
            if (i <= this->maximum_degree - this->minimum_degree)
                this->array_of_indexes[i] = array[i];
            else
                this->array_of_indexes[i] = 0;
        }
        this->maximum_degree = index;
    }
    return array_of_indexes[size - 1];
}
Polynomial::~Polynomial(){
    delete []this->array_of_indexes;
}





