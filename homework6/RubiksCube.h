#ifndef RUBICSCUBE_H
#define RUBICSCUBE_H
#include <iostream>


using namespace std;

/* My Rubik's Cube in 2D be like:

            0   1   2

            7   W   3

            6   5   4

0   1   2   0   1   2   0   1   2    0   1   2

7   B   3   7   R   3   7   G   3    7   O   3

6   5   4   6   5   4   6   5   4    6   5   4

            0   1   2

            7   Y   3

            6   5   4
*/



class RubiksCube{
private:
    int32_t *faces = new int32_t[6];
public:
    RubiksCube();
    static uint32_t SetupEdge(uint32_t, int, int);
    void UniversalRotate(int, const int*, int*);
    void WhiteRotation(int);
    int GetColor(int, int);
    void RotateUp(bool);
    void RotateDown(bool);
    void RotateLeft(bool);
    void RotateRight(bool);
    void RotateFront(bool);
    void RotateBack(bool);
    void Flower();
    void Cross();
    void PifPuf();
    void MiddleLayer();
    void DownCross();
    void TrueDownCross();
    void LastLayer();
    void RandomizedCube();
    bool CubeIsSolved();
    friend ostream& operator<<(ostream&, RubiksCube&);
    friend istream& operator>>(istream&, RubiksCube&);
    ~RubiksCube();
};


#endif


