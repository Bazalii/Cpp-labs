#include "RubiksCube.h"

RubiksCube::RubiksCube(){
    //We generate a solved Rubik's cube
    this->faces[0] = 0x00000000;
    this->faces[1] = 0x11111111;
    this->faces[2] = 0x22222222;
    this->faces[3] = 0x33333333;
    this->faces[4] = 0x44444444;
    this->faces[5] = 0x55555555;
}
void RubiksCube::RotateUp(){

}
void RubiksCube::RotateDown() {

}
void RubiksCube::RotateLeft(){

}
void RubiksCube::RotateRight(){

}
void RubiksCube::RotateFront(){

}
void RubiksCube::RotateBack(){

}
bool RubiksCube::CubeIsSolved(){
    return faces[0] == 0x00000000 &&
    faces[1] == 0x11111111 &&
    faces[2] == 0x22222222 &&
    faces[3] == 0x33333333 &&
    faces[4] == 0x44444444 &&
    faces[5] == 0x55555555;
}
RubiksCube& RubiksCube::operator=(const RubiksCube& existing_rubiks_cube){
    for (int i = 0; i < 6; ++i)
        this->faces[i] = existing_rubiks_cube.faces[i];
    return *this;
}
RubiksCube::~RubiksCube(){
    delete []this->faces;
}
