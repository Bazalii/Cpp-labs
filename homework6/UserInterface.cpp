#include "UserInterface.h"
#include <string>
#include <fstream>

using namespace std;


UI::UI(const RubiksCube& existing_cube){
    this->main_cube = existing_cube;
}
void UI::exit(){
    cout << "Thank you for choosing my Rubik's cube solver" << endl;
}
void UI::save(const string& file_name){
    ofstream output(file_name);
    output << main_cube;
    cout << endl;
    cout << "You have saved this state:" << endl;
    this->print();
}
void UI::load(const string& file_name){
    ifstream input(file_name);
    input >> main_cube;
    cout << endl;
    cout << "You have loaded this state:" << endl;
    this->print();
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
    cout << "Also the saved state itself:" << endl;
    this->print();
}
void UI::random_cube(const string& file_name){
    ofstream output(file_name);
    cout << "Moves, which you have to perform to get to founded randomized state:" << endl << endl;
    main_cube.RandomizedCube();
    cout << endl;
    cout << endl;
    cout << "Also the saved state itself:" << endl;
    this->print();
    output << main_cube;
}
void UI::print(){
    cout << endl;
    cout << main_cube;
    cout << endl;
    cout << "Type command (if you need the list of all commands, type man)" << endl;
}
void UI::man(){
    cout << endl;
    cout << "Here are the commands:" << endl;
    cout << "save - if you want to save cube into the file." << endl;
    cout << "load - if you want to get the current state of cube from the file." << endl;
    cout << "move 'one of six moves(up/down/right/left/front/back, for anticlockwise add ')' - to move face of the cube" << endl;
    cout << "random_cube - if you want to get the random state of cube to solve, which will be saved to file." << endl;
    cout << "solve - prints twists of faces to solve the cube, which was loaded from file." << endl;
    cout << "exit - if you want to finish working with solver." << endl;
    cout << endl;
    cout << "Type command (if you need the list of all commands, type man)" << endl;
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
    cout << "Type command (if you need the list of all commands, type man)" << endl;
}
void UI::start(){
    string command, load_name, save_name, face;
    cout << endl;
    cout << "Hello! I implemented universal algorithm for solving Rubik's Cube." << endl;
    cout << "It performs consistent moves from one state of the cube to the other:" << endl;
    cout << "Flower -> Cross -> PifPuf -> MiddleLayer -> DownCross -> TrueDownCross -> LastLayer" << endl;
    cout << "It is rather big to implement, because there are many positions that should be considered." << endl;
    cout << "However, it has its own advantages over other 'clever' algorithms." << endl;
    cout << "Firstly, you have to consider many positions, but you don't have to think about difficult moves." << endl;
    cout << "For example, in Thistlethwaite's algorithm you have to come up with a solution how to move from one group to the other." << endl;
    cout << "You also have to solve the problem with belongings to groups and these two problems are rather complicated." << endl;
    cout << "The same can be said about Korf's Optimal Algorithm, which is the hardest to implement out of these three." << endl;
    cout << "Secondly, my algorithm is the fastest when we talk about time limits, because it comes through several if statements." << endl;
    cout << "It performs the solution within a split second while others can work for several minutes. " << endl;
    cout << "It is worth mentioning that the solution, made with universal algorithm, is not optimal, but it is working." << endl;
    cout << "Usually the number of movements is not much longer than the solution, made with Thistlethwaite's 52-moves algorithm." << endl;
    cout << "So, in my opinion, it is the best algorithm to implement in our case." << endl;
    cout << "My Rubik's Cube in 2D looks like:" << endl << endl;
    cout << "            0   1   2" << endl << endl;
    cout << "            7   W   3" << endl << endl;
    cout << "            6   5   4" << endl << endl;
    cout << "0   1   2   0   1   2   0   1   2   0   1   2" << endl << endl;
    cout << "7   B   3   7   R   3   7   G   3   7   O   3" << endl << endl;
    cout << "6   5   4   6   5   4   6   5   4   6   5   4" << endl << endl;
    cout << "            0   1   2" << endl << endl;
    cout << "            7   Y   3" << endl << endl;
    cout << "            6   5   4" << endl << endl;
    cout << "When the state of the cube is printed in console it shows the same 2D picture but each face is on new line." << endl;
    cout << "W = 0, B = 1, R = 2, G = 3, O = 4, Y = 5, but all insignificant zeros are dropped out. It is simple and convenient." << endl;
    cout << "For example, for the solved face W you'll see only 0 instead of 00000000." << endl;
    cout << "Another example for cooked up face 01004352 you'll see 1004352" << endl;
    cout << "Here is the example of fully solved cube in this representation:" << endl << endl;
    cout << "0" << endl;
    cout << "11111111" << endl;
    cout << "22222222" << endl;
    cout << "33333333" << endl;
    cout << "44444444" << endl;
    cout << "55555555" << endl << endl;
    cout << "Let's move on to main program." << endl;
    cout << "First of all please type the name of loading file and saving file in format: name + enter + name" << endl;
    cout << "These files will be created using standard path for your compiler." << endl;
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
    cout << "Type command (if you need the list of commands, type man)" << endl;
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
        else
            cout << "Please, type man and don't try to use other commands!" << endl;
    }
}