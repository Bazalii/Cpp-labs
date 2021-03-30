#include <map>
#include <cmath>
#include <fstream>
#include "pugixml.hpp"
#include "stop.h"

using namespace pugi;
using namespace std;

void all_statistics(map<string , pair<int, vector<double>>> &container, string place, Stop current_stop){
    if (!container.contains(place)){
        container[place].first = 1;
        container[place].second.resize(3);
    }
    else{
        container[place].first += 1;
        container[place].second[2] += sqrt(
                pow(current_stop.get_coordinates().first - container[place].second[0], 2) +
                pow(current_stop.get_coordinates().second -  container[place].second[1], 2));
        container[place].second[0] = current_stop.get_coordinates().first;
        container[place].second[1] = current_stop.get_coordinates().second;
    }
}

string find_maximum_stops(map<string , pair<int, vector<double>>> container){
    int maximum = 0;
    string name_of_maximum;
    for (auto it : container){
        if (it.second.first > maximum){
            maximum = it.second.first;
            name_of_maximum = it.first;
        }
    }
    return name_of_maximum;
}

string find_maximum_length(map<string , pair<int, vector<double>>> container){
    double maximum = 0;
    string name_of_maximum;
    for (auto it : container){
        if (it.second.second[2] > maximum){
            maximum = it.second.second[2];
            name_of_maximum = it.first;
        }
    }
    return name_of_maximum;
}

int main() {
    ofstream fout("output.txt");
    map<string , pair<int, vector<double>>> stops_of_the_street, bus_stops_of_the_route, trolleybus_stops_of_the_route, tram_stops_of_the_route;
    vector<Stop> stoppages;
    string street_with_maximum_stops, bus_route_with_maximum_stops, trolleybus_route_with_maximum_stops, tram_route_with_maximum_stops, maximum_bus_route_length, maximum_trolleybus_route_length, maximum_tram_route_length;
    xml_document main_file;
    xml_parse_result result = main_file.load_file("D:/Ivan/ITMO/Cpp_projects/homework3/data.xml");
    if (!result)
        return -1;
    else {
        for (xml_node obj : main_file.child("dataset").children("transport_station")) {
            Stop current_stop;
            current_stop.set_transport(obj.child_value("type_of_vehicle"));
            current_stop.set_streets(obj.child_value("location"));
            current_stop.set_routes(obj.child_value("routes"));
            current_stop.set_coordinates(obj.child_value("coordinates"));
            stoppages.push_back(current_stop);
        }
    }
    for (Stop current : stoppages) {
        for(string street : current.get_streets())
            if (!stops_of_the_street.contains(street) && street != "0")
                stops_of_the_street[street].first = 1;
            else
                stops_of_the_street[street].first += 1;
        for (string route : current.get_routes()){
            if (current.get_transport() == "Автобус")
                all_statistics(bus_stops_of_the_route, route, current);
            else if (current.get_transport() == "Троллейбус")
                all_statistics(trolleybus_stops_of_the_route, route, current);
            else if (current.get_transport() == "Трамвай")
                all_statistics(tram_stops_of_the_route, route, current);
        }
    }
    fout << "Маршрут автобуса с наибольшим числом остановок: " << find_maximum_stops(bus_stops_of_the_route) << endl;
    fout << "Маршрут автобуса с наибольшей длиной: " << find_maximum_length(bus_stops_of_the_route) << endl;
    fout << "Маршрут троллейбуса с наибольшим числом остановок: " << trolleybus_route_with_maximum_stops << endl;
    fout << "Маршрут троллейбуса с наибольшей длиной: " << find_maximum_stops(trolleybus_stops_of_the_route) << endl;
    fout << "Маршрут трамвая с наибольшим числом остановок: " << find_maximum_stops(tram_stops_of_the_route) << endl;
    fout << "Маршрут трамвая с наибольшей длиной: " << find_maximum_length(tram_stops_of_the_route) << endl;
    fout << "Улица с наибольшим числом остановок: " << find_maximum_stops(stops_of_the_street) << endl;
    return 0;
}
