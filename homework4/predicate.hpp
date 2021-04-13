#ifndef PREDICATE_H
#define PREDICATE_H
#include <iostream>

using namespace std;


template<typename ForwardIterator, typename Type>
bool allOf(ForwardIterator first, ForwardIterator last, Type predicate){
    for (; first != last; ++first) {
        if (!predicate(*first))
            return false;
    }
    return true;
}
template<typename ForwardIterator, typename Type>
bool anyOf(ForwardIterator first, ForwardIterator last, Type predicate){
    for (; first != last; ++first) {
        if (predicate(*first))
            return true;
    }
    return false;
}
template<typename ForwardIterator, typename Type>
bool noneOf(ForwardIterator first, ForwardIterator last, Type predicate){
    for (; first != last; ++first) {
        if (predicate(*first))
            return false;
    }
    return true;
}
template<typename ForwardIterator, typename Type>
bool oneOf(ForwardIterator first, ForwardIterator last, Type predicate){
    int checker = 0;
    for (; first != last; ++first) {
        if (predicate(*first))
            checker += 1;
    }
    return checker == 1;
}
template<typename ForwardIterator, typename Type = less<int>>
bool isSorted(ForwardIterator first, ForwardIterator last, Type predicate = Type()){
    for (; first != last - 1; ++first) {
        if (!predicate(*first, *(first + 1)))
            return false;
    }
    return true;
}
template<typename ForwardIterator, typename Type>
bool isPartitioned(ForwardIterator first, ForwardIterator last, Type predicate){
    bool checker1 = predicate(*first), checker2 = false;
    for (first = first + 1; first != last; ++first) {
        if (predicate(*first) != checker1 && !checker2)
            checker2 = true;
        else if(predicate(*first) != checker1 && checker2)
            return false;
    }
    return true;
}
template<typename ForwardIterator, typename Type>
ForwardIterator findNot(ForwardIterator first, ForwardIterator last, Type value){
    for (; first != last; ++first) {
        if (value != *first)
            return first;
    }
    return first;
}
template<typename ForwardIterator, typename Type>
ForwardIterator findBackward(ForwardIterator first, ForwardIterator last, Type value){
    ForwardIterator checker = last;
    for (; first != last; ++first) {
        if (value == *first)
            checker = first;
    }
    return checker;
}
template<typename ForwardIterator, typename Type>
bool isPalindrome(ForwardIterator first, ForwardIterator last, Type predicate){
    ForwardIterator checker = last;
    for (; first != checker; ++first) {
        if (!predicate(*first, *(--last)))
            return false;
    }
    return true;
}


#endif
