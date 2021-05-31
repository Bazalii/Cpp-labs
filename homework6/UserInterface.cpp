#include "UserInterface.h"
#include <string>
#include <fstream>


UI::UI(const RubiksCube& existing_cube){
    this->main_cube = existing_cube;
}
void UI::start(){
    string command, file_name;
    cout << "Hello! These are the commands:" << endl;
    cout << "save 'filename' - if you want to save cube into the file." << endl;
    cout << "load 'filename' - if you want to get the current state of cube from the file." << endl;
    cout << "random_cube 'filename' - if you want to get the random state of cube to solve, which will be saved to file." << endl;
    cout << "solve 'filename' - prints twists of faces to solve the cube, which was loaded from file." << endl;
    cout << "exit - if you want to finish working with solver." << endl;
    while (cin >> command){
        if (command == "exit"){
           cout << "Thank you for choosing our Rubik's cube solver" << endl;
           break;
        }
        else if(command == "save"){
            cin >> file_name;
            ofstream output(file_name);
//            output << this->main_cube;
        }
        else if(command == "load"){
            cin >> file_name;
            ifstream input(file_name);
        }
        else if(command == "random_cube"){
            cin >> file_name;
        }
        else if(command == "solve"){
            cin >> file_name;
        }
    }
}