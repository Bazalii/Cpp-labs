#ifndef STOP_H
#define STOP_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Stop {
private:
    int number;
    string transport;
    vector<string> streets;
    vector<string> routes;
    pair<double, double> coordinates;
public:
    Stop(){};
    void set_number(const string&);
    void set_transport(const string&);
    void set_streets(const string&);
    void set_routes(const string&);
    void set_coordinates(const string&);
};


#endif
