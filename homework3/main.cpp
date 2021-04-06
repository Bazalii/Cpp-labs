#include <map>
#include <cmath>
#include <fstream>
#include "pugixml.hpp"
#include "stop.h"

using namespace pugi;
using namespace std;

void all_statistics(map<string , pair<int, vector<double>>> &container, const string& place, Stop current_stop){
    //fixed use unpacking for pairs
    //auto [x, y] = p;
    if (!container.contains(place)){
        container[place] = {1, {0, 0, 0}};
    }
    else{
        auto& [number, array] = container[place];
        number += 1;
        array[2] += sqrt(
                pow(current_stop.get_coordinates().first - array[0], 2) +
                pow(current_stop.get_coordinates().second -  array[1], 2));
        array[0] = current_stop.get_coordinates().first;
        array[1] = current_stop.get_coordinates().second;
    }
}

string find_maximum_stops(const map<string , pair<int, vector<double>>>& container){
    int maximum = 0;
    string name_of_maximum;
    for (const auto& [name, statistic_pair] : container){
        const auto& [number, array] = statistic_pair;
        if (number > maximum){
            maximum = number;
            name_of_maximum = name;
        }
    }
    return name_of_maximum;
}

string find_maximum_length(const map<string , pair<int, vector<double>>>& container){
    double maximum = 0;
    string name_of_maximum;
    for (const auto& [name, statistic_pair] : container){
        const auto& [number, array] = statistic_pair;
        if (array[2] > maximum){
            maximum = array[2];
            name_of_maximum = name;
        }
    }
    return name_of_maximum;
}

int main() {
    ofstream fout("output.txt");
    map<string , pair<int, vector<double>>> stops_of_the_street, bus_stops_of_the_route, trolleybus_stops_of_the_route, tram_stops_of_the_route;
    vector<Stop> stoppages;
    xml_document main_file;
    xml_parse_result result = main_file.load_file("D:/Ivan/ITMO/Cpp_projects/homework3/data.xml");
    if (!result)
        return -1;
    else {
        for (xml_node obj : main_file.child("dataset").children("transport_station")){
            Stop current_stop;
            current_stop.set_transport(obj.child_value("type_of_vehicle"));
            current_stop.set_streets(obj.child_value("location"));
            current_stop.set_routes(obj.child_value("routes"));
            current_stop.set_coordinates(obj.child_value("coordinates"));
            stoppages.push_back(current_stop);
        }
    }
    for (Stop current : stoppages){
        for(const string& street : current.get_streets())
            if (!stops_of_the_street.contains(street) && street != "0")
                stops_of_the_street[street].first = 1;
            else
                stops_of_the_street[street].first += 1;
        for (const string& route : current.get_routes()){
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
    fout << "Маршрут троллейбуса с наибольшим числом остановок: " << find_maximum_stops(trolleybus_stops_of_the_route) << endl;
    fout << "Маршрут троллейбуса с наибольшей длиной: " << find_maximum_length(trolleybus_stops_of_the_route) << endl;
    fout << "Маршрут трамвая с наибольшим числом остановок: " << find_maximum_stops(tram_stops_of_the_route) << endl;
    fout << "Маршрут трамвая с наибольшей длиной: " << find_maximum_length(tram_stops_of_the_route) << endl;
    fout << "Улица с наибольшим числом остановок: " << find_maximum_stops(stops_of_the_street) << endl;
    return 0;
}
