#ifndef SOLVER_H
#define SOLVER_H
#include "RubiksCube.h"

class UI{
private:
    RubiksCube main_cube;
public:
    UI(const RubiksCube&);
    void start();
};

#endif
