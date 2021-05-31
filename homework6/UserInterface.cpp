#include "UserInterface.h"
#include <string>
#include <sstream>


UI::UI(const RubiksCube& existing_cube){
    this->main_cube = existing_cube;
}
void UI::start(){
    string command, buffer;
    while (getline(cin, command)){
        if (command == "exit")
            break;
    }
}