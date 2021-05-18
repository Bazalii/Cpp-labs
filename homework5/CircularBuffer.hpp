#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#include <iterator>

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
    MyIterator(Type *inp_begin, int inp_size, int inp_actual_begin, int inp_current_position){
        this->begin = inp_begin;
        this->actual_begin = inp_actual_begin;
        this->current_position = inp_current_position;
        this->size = inp_size;
    }
    int get_position(){
        return this->current_position;
    }
    MyIterator& operator += (difference_type second_position){
        this->current_position += second_position;
        return *this;
    }
    MyIterator& operator -= (difference_type second_position){
        this->current_position -= second_position;
        return *this;
    }
    Type& operator*(){
        return begin[(actual_begin + current_position) % this->size];
    }
    Type* operator->(){
        return begin + (actual_begin + current_position) % this->size;
    }
    Type& operator[] (difference_type position){
        return this->begin[(this->actual_begin + position) % this->size];
    }
    MyIterator& operator++(){
        ++this->current_position;
        return *this;
    }
    MyIterator& operator--(){
        --this->current_position;
        return *this;
    }
    MyIterator operator+(difference_type second_iter){
        return MyIterator(this->begin, this->size, this->actual_begin, this->current_position + second_iter);
    }
    MyIterator operator-(difference_type second_iter){
        return MyIterator(this->begin, this->size, this->actual_begin, this->current_position - second_iter);
    }
    friend MyIterator operator+(difference_type position, const MyIterator& second_iter){
        return MyIterator(second_iter.begin, second_iter.size, second_iter.actual_begin, second_iter.current_position + position);
    }
    difference_type operator-(const MyIterator& second_iter){
        return this->current_position - second_iter.current_position;
    }
    bool operator==(const MyIterator& second_iter) const{
        return this->current_position == second_iter.current_position;
    }
    bool operator!=(const MyIterator& second_iter) const{
        return this->current_position != second_iter.current_position;
    }
    bool operator>(const MyIterator& second_iter) const{
        return this->current_position > second_iter.current_position;
    }
    bool operator<(const MyIterator& second_iter) const{
        return this->current_position < second_iter.current_position;
    }
    bool operator>=(const MyIterator& second_iter) const{
        return this->current_position >= second_iter.current_position;
    }
    bool operator<=(const MyIterator& second_iter) const{
        return this->current_position <= second_iter.current_position;
    }
};

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

template class MyIterator<int>;

#endif