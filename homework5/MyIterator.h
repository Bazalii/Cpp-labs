#ifndef MYITERATOR_H
#define MYITERATOR_H
#include <iostream>

using namespace std;

template<typename Type>
class MyIterator{
private:
    Type *begin;
    int actual_begin;
    int current_position;
    int size;
public:
    using iterator_category = random_access_iterator_tag;
    using value_type = Type;
    using difference_type = typename iterator<random_access_iterator_tag, Type>::difference_type;
    using pointer = value_type*;
    using reference = value_type&;
    MyIterator(Type *, int, int, int);
    int get_position();
    MyIterator<Type>& operator += (difference_type);
    MyIterator<Type>& operator -= (difference_type);
    Type& operator*();
    Type* operator->();
    Type& operator[] (difference_type);
    MyIterator<Type>& operator++();
    MyIterator<Type>& operator--();
    MyIterator<Type> operator+(difference_type);
    MyIterator<Type> operator-(difference_type);
    template<class T>
    friend MyIterator<T> operator+(difference_type, const MyIterator<T>&);
    difference_type operator-(const MyIterator<Type>&);
    bool operator==(const MyIterator<Type>&) const;
    bool operator!=(const MyIterator<Type>&) const;
    bool operator>(const MyIterator<Type>&) const;
    bool operator<(const MyIterator<Type>&) const;
    bool operator>=(const MyIterator<Type>&) const;
    bool operator<=(const MyIterator<Type>&) const;
};


template class MyIterator<int>;
#endif
