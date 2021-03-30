#ifndef STOP_H
#define STOP_H
#include <string>
#include <vector>

using namespace std;

class Stop {
private:
    string transport;
    vector<string> streets;
    vector<string> routes;
    pair<double, double> coordinates;
public:
    Stop(){};
    void set_transport(const string&);
    void set_streets(const string&);
    void set_routes(const string&);
    void set_coordinates(const string&);
    string get_transport();
    vector<string> get_streets();
    vector<string> get_routes();
    pair<double, double> get_coordinates();
};


#endif
