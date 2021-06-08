#include "UserInterface.h"
#include <string>
#include <fstream>

using namespace std;
UI::UI(const RubiksCube& existing_cube){
    this->main_cube = existing_cube;
}
void UI::exit(){
    cout << "Thank you for choosing our Rubik's cube solver" << endl;
}
void UI::save(const string& file_name){
    ofstream output(file_name);
    output << main_cube;
    cout << endl;
    cout << "Type command (if you need help, type man)" << endl;
}
void UI::load(const string& file_name){
    ifstream input(file_name);
    input >> main_cube;
    cout << endl;
    cout << "Type command (if you need help, type man)" << endl;
}
void UI::move_cube(const string& file_name, const string& face){
    ofstream output(file_name);
    if (face == "up")
        main_cube.RotateUp(false);
    else if (face == "up'")
        main_cube.RotateUp(true);
    else if (face == "down")
        main_cube.RotateDown(false);
    else if (face == "down'")
        main_cube.RotateDown(true);
    else if (face == "right")
        main_cube.RotateRight(false);
    else if (face == "right'")
        main_cube.RotateRight(true);
    else if (face == "left")
        main_cube.RotateLeft(false);
    else if (face == "left'")
        main_cube.RotateLeft(true);
    else if (face == "front")
        main_cube.RotateFront(false);
    else if (face == "front'")
        main_cube.RotateFront(true);
    else if (face == "back")
        main_cube.RotateBack(false);
    else if (face == "back'")
        main_cube.RotateBack(true);
    output << main_cube;
    cout << endl;
    cout << endl;
    cout << "Type command (if you need help, type man)" << endl;
}
void UI::random_cube(const string& file_name){
    ofstream output(file_name);
    main_cube.RandomizedCube();
    output << main_cube;
    cout << endl;
    cout << endl;
    cout << "Type command (if you need help, type man)" << endl;
}
void UI::print(){
    cout << endl;
    cout << main_cube;
    cout << endl;
    cout << "Type command (if you need help, type man)" << endl;
}
void UI::man(){
    cout << "Here are the commands:" << endl;
    cout << "save - if you want to save cube into the file." << endl;
    cout << "load - if you want to get the current state of cube from the file." << endl;
    cout << "move 'one of six moves(up/down/right/left/front/back)' - to move face of the cube" << endl;
    cout << "random_cube - if you want to get the random state of cube to solve, which will be saved to file." << endl;
    cout << "solve - prints twists of faces to solve the cube, which was loaded from file." << endl;
    cout << "exit - if you want to finish working with solver." << endl;
    cout << endl;
    cout << "Type command (if you need help, type man)" << endl;
}
void UI::solve(const string& file_name){
    cout << endl;
    cout << "Flower: ";
    main_cube.Flower();
    cout << endl;
    cout << "Cross: ";
    main_cube.Cross();
    cout << endl;
    cout << "PifPuf: ";
    main_cube.PifPuf();
    cout << endl;
    cout << "MiddleLayer: ";
    main_cube.MiddleLayer();
    cout << endl;
    cout << "DownCross: ";
    main_cube.DownCross();
    cout << endl;
    cout << "TrueDownCross: ";
    main_cube.TrueDownCross();
    cout << endl;
    cout << "LastLayer: ";
    main_cube.LastLayer();
    cout << endl;
    if(main_cube.CubeIsSolved())
        cout << "Rubik's cube is solved!" << endl;
    cout << endl;
    cout << "Type command (if you need help, type man)" << endl;
}
void UI::start(){
    string command, load_name, save_name, face;
    cout << "Hello! First of all please type the name of loading file and saving file in format: name + enter + name" << endl;
    cout << "Name of the loading file: ";
    cin >> load_name;
    cout << endl;
    cout << "Name of the saving file: ";
    cin >> save_name;
    cout << endl;
    ofstream in(load_name);
    ofstream out(save_name);
    in.close();
    out.close();
    cout << "Type command (if you need help, type man)" << endl;
    while (cin >> command){
        if (command == "exit"){
            this->exit();
            return;
        }
        else if (command == "save")
            this->save(save_name);
        else if (command == "load")
            this->load(load_name);
        else if (command == "move"){
            cin >> face;
            this->move_cube(save_name, face);
        }
        else if (command == "random_cube")
            this->random_cube(save_name);
        else if (command == "solve")
            this->solve(save_name);
        else if (command == "print")
            this->print();
        else if (command == "man")
            this->man();
    }
}