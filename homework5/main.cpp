#include<iostream>
#include<sstream>
#include<vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <string>
#include <exception>
#include <cassert>
#include "CircularBuffer.hpp"

using namespace std;


#define DEBUG

#ifndef DEBUG
#define cerr cerr1
#define endl '\n'
struct emptyClass{                                                                               //remove cerr in release (it works fast also)
};                                                                                               //don't use with functions (compiler doesn't know if function changes state of variables)
                                                                                                 //                         (it still doesn't print but functions run)
template <class T>
emptyClass& operator<<(emptyClass& cl, const T& t){
    return cl;
}

template <emptyClass& out, typename T>
void print([[maybe_unused]] const T& t)
{
}

template<emptyClass& out, class T, class... Args>
void print([[maybe_unused]] const T& el, [[maybe_unused]] Args... args)
{
}


emptyClass cerr;
#define cerr cerr1
#endif

#ifdef DEBUG                                                                                     //check vector range in debug
template <class T>
struct vector1 : public vector<T>{
    using vector<T>::vector;
    decltype(auto) operator[](size_t t) {
        return (*this).at(t);
    }
    decltype(auto) operator[](size_t t)  const {
        return (*this).at(t);
    }
};
#define vector vector1
#endif

int depth = 0;
int maxDepth = 0;


ostream& operator<<(ostream& out, const CircularBuffer<int>& a){
    depth++;
    int myDepth = depth;
    maxDepth = max(maxDepth, depth);
    for (auto iter = a.begin(); iter != a.end(); ++iter){
        if (iter != a.begin()){
            if (maxDepth - myDepth == 0)
                out << " ";
            else
                for (int i = 0; i < maxDepth - myDepth; i++)
                    cout << endl;
        }
        auto el = *iter;
        out << el;
    }
    if (myDepth == 1){
        out << endl;
    }
    depth--;
    if (myDepth == 1)
        maxDepth = 0;
    return out;
}


template<class Ch, class Tr, class... Args>                                                      //cout tuple
auto& operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) {
    maxDepth = max(depth + 1, maxDepth);
    std::apply([&os](auto&&... args) {((os << args << " "), ...);}, t);
    return os;
}

template<class T, class U>                                                                       //cout pair
ostream& operator<<(ostream& out, const pair<T, U>& p){
    maxDepth = max(depth + 1, maxDepth);
    return (out << p.first << " " << p.second);
}

template<class T>                                                                                //cin vector (any dimension)
istream& operator>>(istream& in, vector<T>& v){
    for (auto& e : v){
        in >> e;
    }
    return in;
}

template<class T>                                                                                //two-dimensional array for more comfortable constructor
struct matrix : public vector<vector<T>>{
    using vector<vector<T>>::vector;
    matrix (size_t n = 0, size_t m = 0, T el = T()) : vector<vector<T>>(n, vector<T>(m, el)){};
    void resize(size_t n, size_t m, T el = T()){
        vector<vector<T>>::resize(n, vector<T>(m, el));
    }
};

stringstream ss;


template <auto& out=cout, typename T>                                                         //function that prints any values with space delimeter
void print(const T& t)                                                                           //and make endl in the end (but it doesn't even matter)
{                                                                                                //e.g print(1, "plus", 2, '=', 3);
    out << t << endl;                                                                            //1 plus 2 = 3
}                                                                                                //use template for another ostream
//e.g. print<cerr>("I am here")
template<auto& out=cout, class T, class... Args>
void print(const T& el, Args... args)
{
    out << el << " ";
    print<out>(args...);
}

#define callAssert(...) assert(assertPrint(__VA_ARGS__))

template<class P, class... Args>
bool assertPrint(const P& pred, Args&&... args) {
    if (!pred(forward<Args>(args)...)) {
        print<cerr>(forward<Args>(args)...);
        return false;
    }
    return true;
}

void checkConstOperator(const CircularBuffer<int>& cb) {
	print(cb[2]);
}


int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    CircularBuffer<int> c(4);
    c.addFirst(1);
    callAssert(equal_to<>(), c.first(), 1);
    callAssert(equal_to<>(), c.last(), 1);
    c.addLast(2);
    callAssert(equal_to<>(), c.first(), 1);
    callAssert(equal_to<>(), c.last(), 2);
    callAssert(equal_to<>(), c[0], 1);
    callAssert(equal_to<>(), c[1], 2);
    c.delFirst();
    callAssert(equal_to<>(), c[0], 2);
    callAssert(equal_to<>(), c.first(), 2);
    callAssert(equal_to<>(), c.last(), 2);
    c.delLast();
    try {
        c[0] = 1;
        throw "out of range";
    }
    catch (const exception& e) {
        print(e.what());
    }
    c.addFirst(1);
    c.addFirst(2);
    c.addFirst(3);
    c.addFirst(4);
    checkConstOperator(c);
	try {
        c[4] = 1;
        throw "out of range";
    }
    catch (const exception& e) {
        print(e.what());
    }
    print<ss>(c);
    c.addFirst(5);
    print<ss>(c);
    c.changeCapacity(5);
    print<ss>(c);
    c.addFirst(6);
    print<ss>(c);
	sort(c.begin(), c.end());
    print<ss>(c);
    callAssert(equal_to<>(), ss.str(), "4 3 2 1\n"
                                       "\n"
                                       "5 4 3 2\n"
                                       "\n"
                                       "5 4 3 2\n"
                                       "\n"
                                       "6 5 4 3 2\n"
                                       "\n"
                                       "2 3 4 5 6\n"
                                       "\n");
    print("Everything is ok");
}