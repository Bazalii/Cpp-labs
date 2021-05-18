#include "MyIterator.h"

template<typename Type>
MyIterator<Type>::MyIterator(Type *inp_begin, int inp_size, int inp_actual_begin, int inp_current_position){
        this->begin = inp_begin;
        this->actual_begin = inp_actual_begin;
        this->current_position = inp_current_position;
        this->size = inp_size;
    }
template<typename Type>
int MyIterator<Type>::get_position(){
    return this->current_position;
}
template<typename Type>
MyIterator<Type>& MyIterator<Type>::operator += (difference_type second_position){
    this->current_position += second_position;
    return *this;
}
template<typename Type>
MyIterator<Type>& MyIterator<Type>::operator -= (difference_type second_position){
    this->current_position -= second_position;
    return *this;
}
template<typename Type>
Type& MyIterator<Type>::operator*(){
    return begin[(actual_begin + current_position) % this->size];
}
template<typename Type>
Type* MyIterator<Type>::operator->(){
    return begin + (actual_begin + current_position) % this->size;
}
template<typename Type>
Type& MyIterator<Type>::operator[] (difference_type position){
    return this->begin[(this->actual_begin + position) % this->size];
}
template<typename Type>
MyIterator<Type>& MyIterator<Type>::operator++(){
    ++this->current_position;
    return *this;
}
template<typename Type>
MyIterator<Type>& MyIterator<Type>::operator--(){
    --this->current_position;
    return *this;
}
template<typename Type>
MyIterator<Type> MyIterator<Type>::operator+(difference_type second_iter){
    return MyIterator(this->begin, this->size, this->actual_begin, this->current_position + second_iter);
}
template<typename Type>
MyIterator<Type> MyIterator<Type>::operator-(difference_type second_iter){
    return MyIterator(this->begin, this->size, this->actual_begin, this->current_position - second_iter);
}
template<typename Type>
MyIterator<Type> operator+(typename iterator<random_access_iterator_tag, Type>::difference_type position, const MyIterator<Type>& second_iter){
    return MyIterator<Type>(second_iter.begin, second_iter.size, second_iter.actual_begin, second_iter.current_position + position);
}
template<typename Type>
typename iterator<random_access_iterator_tag, Type>::difference_type MyIterator<Type>::operator-(const MyIterator& second_iter){
    return this->current_position - second_iter.current_position;
}
template<typename Type>
bool MyIterator<Type>::operator==(const MyIterator<Type>& second_iter) const{
    return this->current_position == second_iter.current_position;
}
template<typename Type>
bool MyIterator<Type>::operator!=(const MyIterator<Type>& second_iter) const{
    return this->current_position != second_iter.current_position;
}
template<typename Type>
bool MyIterator<Type>::operator>(const MyIterator<Type>& second_iter) const{
    return this->current_position > second_iter.current_position;
}
template<typename Type>
bool MyIterator<Type>::operator<(const MyIterator<Type>& second_iter) const{
    return this->current_position < second_iter.current_position;
}
template<typename Type>
bool MyIterator<Type>::operator>=(const MyIterator<Type>& second_iter) const{
    return this->current_position >= second_iter.current_position;
}
template<typename Type>
bool MyIterator<Type>::operator<=(const MyIterator<Type>& second_iter) const{
    return this->current_position <= second_iter.current_position;
}
