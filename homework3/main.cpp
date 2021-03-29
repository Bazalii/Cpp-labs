#include <fstream>
#include "pugixml.hpp"
#include "stop.h"

using namespace pugi;
using namespace std;


int main() {
    ofstream fout("output.txt");
    vector<Stop> stoppages;
    xml_document main_file;
    xml_parse_result result = main_file.load_file("D:/Ivan/ITMO/Cpp_projects/homework3/data.xml");
    if (!result)
        return -1;
    else {
        for (xml_node obj : main_file.child("dataset").children("transport_station")) {
            Stop current;
            current.set_number(obj.child_value("number"));
            current.set_transport(obj.child_value("type_of_vehicle"));
            current.set_streets(obj.child_value("location"));
            current.set_routes(obj.child_value("routes"));
            current.set_coordinates(obj.child_value("coordinates"));
            stoppages.push_back(current);
        }
    }

    return 0;
}
