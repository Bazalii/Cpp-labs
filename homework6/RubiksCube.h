#ifndef RUBICSCUBE_H
#define RUBICSCUBE_H
#include <iostream>


using namespace std;

/* My Rubik's Cube in 2D be like:

              1   2   3

              4   R   5

              6   7   8

 9  10  11   12  13  14   15  16  17    18  19  20

21   B  22   23   W  24   25   G  26    27   Y  28

29  30  31   32  33  34   35  36  37    38  39  40

             41  42  43

             44   O  45

             46  47  48
*/



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
    void RandomizedCube();
    bool CubeIsSolved();
    bool BelongsToFirstGroup();
    bool BelongsSecondGroup();
    bool BelongsToThirdGroup();
    bool BelongsToFourthGroup();
    RubiksCube& operator=(const RubiksCube&);
    ~RubiksCube();
};


#endif
