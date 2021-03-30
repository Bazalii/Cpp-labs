#include "stop.h"

void Stop::set_transport(const string& input_string){
    this->transport = input_string;
}
void Stop::set_streets(const string& input_string){
    if (!input_string.empty()){
        string help_string = input_string;
        int pos = 0;
        while (help_string.find(".") != -1)
            help_string.replace(help_string.find("."), 1, "");
        if (input_string.find(",") == -1){
            this->streets.push_back(help_string);
        }
        else{
            while (help_string.find(",") != -1){
                this->streets.push_back(help_string.substr(pos, help_string.find(",") - pos));
                pos = help_string.find(",") + 1;
                help_string.replace(help_string.find(","), 1, " ");
            }
        this->streets.push_back(help_string.substr(pos, help_string.size() - pos));
        }
    }
}
void Stop::set_routes(const string& input_string){
    if (!input_string.empty()){
        string help_string = input_string;
        int pos = 0;
        while (help_string.find(".") != -1)
            help_string.replace(help_string.find("."), 1, ",");
        while (help_string.find(" ") != -1)
            help_string.replace(help_string.find(" "), 1, "");
        if (help_string.find(",") == -1){
            this->routes.push_back(help_string);
        }
        else{
            while (help_string.find(",") != -1){
                this->routes.push_back(help_string.substr(pos, help_string.find(",") - pos));
                pos = help_string.find(",") + 1;
                help_string.replace(help_string.find(","), 1, " ");
            }
            this->routes.push_back(help_string.substr(pos, help_string.size() - pos));
        }
    }
}
void Stop::set_coordinates(const string& input_string){
    this->coordinates = make_pair(stod(input_string.substr(0, input_string.find(","))), stod(input_string.substr(input_string.find(",") + 1, input_string.size())));
}
string Stop::get_transport(){
    return this->transport;
}
vector<string> Stop::get_streets(){
    return this->streets;
}
vector<string> Stop::get_routes(){
    return this->routes;
}
pair<double, double> Stop::get_coordinates(){
    return this->coordinates;
}