#include "CircularBuffer.hpp"
#include <iostream>

template<typename Type>
CircularBuffer<Type>::CircularBuffer(int value){
    this->buffer = new int[value + 1];
    this->size = value + 1;
    this->number_of_elements = 0;
}
template<typename Type>
int CircularBuffer<Type>::get_size(){
    return this->number_of_elements;
}
template<typename Type>
int CircularBuffer<Type>::get_start(){
    return this->buf_begin;
}
template<typename Type>
int CircularBuffer<Type>::get_end(){
    return this->buf_end;
}
template<typename Type>
void CircularBuffer<Type>::addFirst(Type value){
    if (number_of_elements == 0){
        this->buf_begin = 0;
        this->buf_end = 0;
        this->number_of_elements += 1;
    }
    else {
        this->buf_begin -= 1;
        if (this->buf_begin == -1)
            this->buf_begin = this->size - 1;
        if (this->number_of_elements < this->size - 1)
            this->number_of_elements += 1;
    }
    this->buffer[this->buf_begin] = value;
}
template<typename Type>
void CircularBuffer<Type>::addLast(Type value){
    if (number_of_elements == 0){
        this->buf_begin = 0;
        this->buf_end = 0;
        this->number_of_elements += 1;
    }
    if (this->number_of_elements < this->size - 1){
        this->buf_end += 1;
        if (this->buf_end == this->size + 1)
            this->buf_end = 0;
        this->number_of_elements += 1;
    }
    this->buffer[this->buf_end] = value;
}
template<typename Type>
Type CircularBuffer<Type>::first(){
    return this->buffer[this->buf_begin];
}
template<typename Type>
Type CircularBuffer<Type>::last(){
    return this->buffer[this->buf_end];
}
template<typename Type>
void CircularBuffer<Type>::delFirst(){
    if (this->buf_begin != this->buf_end){
        if (this->buf_begin + 1 > size)
        this->buf_begin = 0;
    else
        this->buf_begin += 1;
    }
    this->number_of_elements -= 1;
}
template<typename Type>
void CircularBuffer<Type>::delLast(){
    if (this->buf_begin != this->buf_end) {
        if (this->buf_begin - 1 < 0)
            this->buf_begin = this->size - 1;
        else
            this->buf_begin -= 1;
    }
    this->number_of_elements -= 1;
}
template<typename Type>
void CircularBuffer<Type>::changeCapacity(int value){
    if (value + 1 < this->size)
        throw overflow_error("cannot pack all the elements");
    else{
        Type *new_buffer = new Type[value + 1];
        int old_buf_begin = this->buf_begin;
        this->buf_begin = 0;
        this->buf_end = this->number_of_elements - 1;
        for (int i = this->buf_begin; i < this->number_of_elements; ++i)
            new_buffer[i] = this->buffer[(old_buf_begin + i) % this->size];
        delete []this->buffer;
        this->buffer = new_buffer;
        this->size = value + 1;
    }
}
template<typename Type>
Type CircularBuffer<Type>::operator[](int index) const {
    //todo more information in exception
    if (index > (this->size - 2) || index < 0 || this->number_of_elements == 0)
        throw out_of_range("out of range");
    else{
        if (index + this->buf_begin >= size)
            return buffer[index + this->buf_begin - size];
        return buffer[index + this->buf_begin];
    }

}
template< typename Type>
Type& CircularBuffer<Type>::operator[](int index){
    if (index > (this->size - 2) || index < 0 || this->number_of_elements == 0)
        throw out_of_range("out of range");
    else{
        if (index + this->buf_begin >= size)
            return buffer[index + this->buf_begin - size];
        return buffer[index + this->buf_begin];
    }
}
template<typename Type>
MyIterator<Type> CircularBuffer<Type>::begin() const{
    return MyIterator<Type> (this->buffer, this->size, this->buf_begin, 0);
}
template<typename Type>
MyIterator<Type> CircularBuffer<Type>::end() const{
    return MyIterator<Type> (this->buffer, this->size, this->buf_begin, this->number_of_elements);
}
template<typename Type>
CircularBuffer<Type>::~CircularBuffer(){
    delete []this->buffer;
}
template class CircularBuffer<int>;