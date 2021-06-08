#ifndef SOLVER_H
#define SOLVER_H
#include "RubiksCube.h"

class UI{
private:
    RubiksCube main_cube;
public:
    explicit UI(const RubiksCube&);
    static void exit();
    void save(const string&);
    void load(const string&);
    void move_cube(const string&, const string&);
    void random_cube(const string&);
    void solve(const string&);
    void print();
    static void man();
    void start();
};

#endif
