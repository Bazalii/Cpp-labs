#include "polynomial.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <assert.h>

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
    for (int i = this->minimum_degree; i <= this->maximum_degree; ++i) {
        this->array_of_indexes[i] = copy_polynomial.array_of_indexes[i];
    }
}
float Polynomial::get (int number) const{
    float result = 0;
    for (int i = this->minimum_degree; i <= this->maximum_degree; ++i) {
        result += this->array_of_indexes[i - this->minimum_degree] * pow(number, i);
    }
    return result;
}
Polynomial& Polynomial::operator=(const Polynomial &existing_polynomial){
    this->minimum_degree = existing_polynomial.minimum_degree;
    this->maximum_degree = existing_polynomial.maximum_degree;
    delete []this->array_of_indexes;
    this->array_of_indexes = new int[this->maximum_degree - this->minimum_degree + 1];
    for (int i = this->minimum_degree; i <= this->maximum_degree; ++i) {
        this->array_of_indexes[i] = existing_polynomial.array_of_indexes[i];
    }
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
    first_index = first_polynomial.minimum_degree;
    second_index = second_polynomial.minimum_degree;
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
    !operator==(first_polynomial, second_polynomial);
}
const Polynomial operator+(const Polynomial &first_polynomial, const Polynomial &second_polynomial){
    int minimum, maximum, first_index, second_index;
    minimum = (first_polynomial.minimum_degree < second_polynomial.minimum_degree) ? first_polynomial.minimum_degree : second_polynomial.minimum_degree;
    maximum = (first_polynomial.maximum_degree > second_polynomial.maximum_degree) ? first_polynomial.maximum_degree : second_polynomial.maximum_degree;
    int *array = new int[maximum - minimum + 1];
    for (int i = minimum; i <= maximum; ++i) {
        if (first_polynomial.minimum_degree <= i && i <= first_polynomial.maximum_degree)
            first_index = first_polynomial.array_of_indexes[i - first_polynomial.minimum_degree];
        else
            first_index = 0;
        if (second_polynomial.minimum_degree <= i && i <= second_polynomial.maximum_degree)
            second_index = second_polynomial.array_of_indexes[i - second_polynomial.minimum_degree];
        else
            second_index = 0;
        array[i - minimum] = first_index + second_index;
    }
    return Polynomial(minimum, maximum, array);
}
const Polynomial operator-(const Polynomial &first_polynomial, const Polynomial &second_polynomial){
    int minimum, maximum, first_index, second_index;
    minimum = (first_polynomial.minimum_degree < second_polynomial.minimum_degree) ? first_polynomial.minimum_degree : second_polynomial.minimum_degree;
    maximum = (first_polynomial.maximum_degree > second_polynomial.maximum_degree) ? first_polynomial.maximum_degree : second_polynomial.maximum_degree;
    int *array = new int[maximum - minimum + 1];
    for (int i = minimum; i <= maximum; ++i) {
        if (first_polynomial.minimum_degree <= i && i <= first_polynomial.maximum_degree)
            first_index = first_polynomial.array_of_indexes[i - first_polynomial.minimum_degree];
        else
            first_index = 0;
        if (second_polynomial.minimum_degree <= i && i <= second_polynomial.maximum_degree)
            second_index = second_polynomial.array_of_indexes[i - second_polynomial.minimum_degree];
        else
            second_index = 0;
        array[i - minimum] = first_index - second_index;
    }
    return Polynomial(minimum, maximum, array);
}
Polynomial& operator+=(Polynomial &first_polynomial, const Polynomial &second_polynomial){
    int minimum, maximum, first_index, second_index;
    minimum = (first_polynomial.minimum_degree < second_polynomial.minimum_degree) ? first_polynomial.minimum_degree : second_polynomial.minimum_degree;
    maximum = (first_polynomial.maximum_degree > second_polynomial.maximum_degree) ? first_polynomial.maximum_degree : second_polynomial.maximum_degree;
    int *array = new int[maximum - minimum + 1];
    for (int i = minimum; i <= maximum; ++i) {
        if (first_polynomial.minimum_degree <= i && i <= first_polynomial.maximum_degree)
            first_index = first_polynomial.array_of_indexes[i - first_polynomial.minimum_degree];
        else
            first_index = 0;
        if (second_polynomial.minimum_degree <= i && i <= second_polynomial.maximum_degree)
            second_index = second_polynomial.array_of_indexes[i - second_polynomial.minimum_degree];
        else
            second_index = 0;
        array[i - minimum] = first_index + second_index;
    }
    delete first_polynomial.array_of_indexes;
    first_polynomial = Polynomial(minimum, maximum, array);
    return first_polynomial;
}
Polynomial& operator-=(Polynomial &first_polynomial, const Polynomial &second_polynomial){
    int minimum, maximum, first_index, second_index;
    minimum = (first_polynomial.minimum_degree < second_polynomial.minimum_degree) ? first_polynomial.minimum_degree : second_polynomial.minimum_degree;
    maximum = (first_polynomial.maximum_degree > second_polynomial.maximum_degree) ? first_polynomial.maximum_degree : second_polynomial.maximum_degree;
    int *array = new int[maximum - minimum + 1];
    for (int i = minimum; i <= maximum; ++i) {
        if (first_polynomial.minimum_degree <= i && i <= first_polynomial.maximum_degree)
            first_index = first_polynomial.array_of_indexes[i - first_polynomial.minimum_degree];
        else
            first_index = 0;
        if (second_polynomial.minimum_degree <= i && i <= second_polynomial.maximum_degree)
            second_index = second_polynomial.array_of_indexes[i - second_polynomial.minimum_degree];
        else
            second_index = 0;
        array[i - minimum] = first_index - second_index;
    }
    delete first_polynomial.array_of_indexes;
    first_polynomial = Polynomial(minimum, maximum, array);
    return first_polynomial;
}
const Polynomial operator*(const Polynomial &first_polynomial, const Polynomial &second_polynomial){
    if  (first_polynomial == Polynomial() || second_polynomial == Polynomial())
        return Polynomial();
    int size = (first_polynomial.maximum_degree - first_polynomial.minimum_degree + 1) * (second_polynomial.maximum_degree - second_polynomial.minimum_degree + 1);
    int *array = new int[size];
    int *degree = new int[size];
    int iter = 0;
    int new_size = first_polynomial.maximum_degree + second_polynomial.maximum_degree - (first_polynomial.minimum_degree + second_polynomial.minimum_degree) + 1;
    int minimal = first_polynomial.minimum_degree + second_polynomial.minimum_degree;
//    first_polynomial.minimum_degree <= second_polynomial.minimum_degree ? minimal = first_polynomial.minimum_degree : minimal = second_polynomial.minimum_degree;
    for (int i = 0; i <= first_polynomial.maximum_degree - first_polynomial.minimum_degree; ++i) {
        for (int j = 0; j <= second_polynomial.maximum_degree - second_polynomial.minimum_degree; ++j) {
            array[iter] = first_polynomial.array_of_indexes[i] * second_polynomial.array_of_indexes[j];
            degree[iter] = first_polynomial.minimum_degree + second_polynomial.minimum_degree + i + j;
            iter += 1;
        }
    }
    int *final_degree = new int[new_size];
    for (int i = 0; i < new_size; ++i) {
        final_degree[i] = 0;
    }
    for (int i = 0; i < size; ++i) {
        final_degree[degree[i] - minimal] += array[i];
    }
    return Polynomial(first_polynomial.minimum_degree + second_polynomial.minimum_degree, first_polynomial.maximum_degree + second_polynomial.maximum_degree, final_degree);
}
const Polynomial operator*(const Polynomial &first_polynomial, int number){
    int *array = new int [first_polynomial.maximum_degree - first_polynomial.minimum_degree + 1];
    for (int i = first_polynomial.minimum_degree; i <= first_polynomial.maximum_degree; ++i) {
        array[i - first_polynomial.minimum_degree] = first_polynomial.array_of_indexes[i - first_polynomial.minimum_degree] * number;
    }
    return Polynomial(first_polynomial.minimum_degree, first_polynomial.maximum_degree, array);
}
const Polynomial operator*(int number, const Polynomial &first_polynomial){
    return first_polynomial * number;
}
const Polynomial operator/(const Polynomial& first_polynomial, int number){
    int *array = new int [first_polynomial.maximum_degree - first_polynomial.minimum_degree + 1];
    for (int i = first_polynomial.minimum_degree; i <= first_polynomial.maximum_degree; ++i) {
        array[i - first_polynomial.minimum_degree] = first_polynomial.array_of_indexes[i - first_polynomial.minimum_degree] / number;
    }
    return Polynomial(first_polynomial.minimum_degree, first_polynomial.maximum_degree, array);
}
Polynomial operator*=(Polynomial &first_polynomial, const Polynomial &second_polynomial){

}
Polynomial operator/=(Polynomial &first_polynomial, int number){
    int *array = new int [first_polynomial.maximum_degree - first_polynomial.minimum_degree + 1];
    for (int i = first_polynomial.minimum_degree; i <= first_polynomial.maximum_degree; ++i) {
        array[i - first_polynomial.minimum_degree] = first_polynomial.array_of_indexes[i - first_polynomial.minimum_degree] / number;
    }
    first_polynomial = Polynomial(first_polynomial.minimum_degree, first_polynomial.maximum_degree, array);
    return first_polynomial;
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
                out << "+" << "x^" << i;
            else if (existing_polynomial.array_of_indexes[i - existing_polynomial.minimum_degree] == -1)
                out << "-" << "x^" << i;
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
    in >> existing_polynomial.minimum_degree;
    for (int i = 0; i <= existing_polynomial.maximum_degree - existing_polynomial.minimum_degree; ++i) {
        in >> existing_polynomial.array_of_indexes[i];
    }
    return in;
}
const int Polynomial::operator[](int index) const {
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
Polynomial::~Polynomial(){}



