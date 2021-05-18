#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#include "MyIterator.h"

using namespace std;


template<typename Type>
class CircularBuffer{
private:
    Type *buffer;
    int size;
    int number_of_elements;
    int buf_begin;
    int buf_end;
public:
    friend class MyIterator<Type>;
    explicit CircularBuffer(int);
    int get_size();
    int get_start();
    int get_end();
    void addFirst(Type);
    void addLast(Type);
    Type first();
    Type last();
    void delFirst();
    void delLast();
    void changeCapacity(int);
    Type operator[](int) const;
    Type& operator[](int);
    MyIterator<Type> begin() const;
    MyIterator<Type> end() const;
    ~CircularBuffer();
};

template class CircularBuffer<int>;

#endif