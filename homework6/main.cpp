#include <iostream>
#include "UserInterface.h"

int main() {
    RubiksCube cube_to_solve = RubiksCube();
    UI app = UI(cube_to_solve);
    app.start();
    return 0;
}
