#ifndef RUBICSCUBE_H
#define RUBICSCUBE_H
#include <iostream>

using namespace std;

class RubiksCube{
private:
    int32_t *faces = new int32_t[6];
    void rotate();
public:
    RubiksCube();
    void RotateUp();
    void RotateDown();
    void RotateLeft();
    void RotateRight();
    void RotateFront();
    void RotateBack();
    bool CubeIsSolved();
    RubiksCube& operator=(const RubiksCube&);
    ~RubiksCube();
};


#endif
