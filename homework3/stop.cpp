#include "stop.h"
#include <algorithm>

//Stop::Stop(string tr, string str, int *numbers, int size, double x, double y){
//    this->transport = tr;
//    this->street = str;
//    this->coordinate_1 = x;
//    this->coordinate_2 = y;
//    this->routes = new int[size];
//    int i = 0;
//    for_each(this->routes, this->routes + size, [&](int &x){x = numbers[i]; i += 1;});
//}

void Stop::set_number(const string& input_string){
    this->number = stoi(input_string);
};
void Stop::set_transport(const string& input_string){
    this->transport = input_string;
};
void Stop::set_streets(const string& input_string){
//    this->streets = input_string;
};
void Stop::set_routes(const string& input_string){
    string symbol(", ");
    
};
void Stop::set_coordinates(const string& input_string){

};