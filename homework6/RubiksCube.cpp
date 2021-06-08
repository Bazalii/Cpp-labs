#include "RubiksCube.h"
#include <ctime>
#include <cstdlib>

using namespace std;


RubiksCube::RubiksCube(){
    //We generate a solved Rubik's cube
    this->faces[0] = 0x00000000;
    this->faces[1] = 0x11111111;
    this->faces[2] = 0x22222222;
    this->faces[3] = 0x33333333;
    this->faces[4] = 0x44444444;
    this->faces[5] = 0x55555555;
}
uint32_t RubiksCube::SetupEdge(uint32_t edge, int first_position, int second_position) {
    if (first_position == second_position)
        return edge;
    else if (first_position == 6)
        edge = ((edge & 0x000000FF) << (first_position - second_position) * 4) |
               ((edge & 0xF0000000) >> (second_position + 2) * 4);
    else if (second_position == 6)
        edge = (((edge & (0xFF000000 >> first_position * 4)) >> (second_position - first_position) * 4) |
                (edge & (0x00F00000 >> first_position * 4)) << (first_position + 2) * 4);

    else if (abs(first_position - second_position) == 2) {
        first_position > second_position ?
            edge = edge << 8 :
            edge = edge >> 8;
    }
    else if (abs(first_position - second_position) == 4) {
        first_position > second_position ?
            edge = edge << 16 :
            edge = edge >> 16;
    }
    return edge;
}
void RubiksCube::UniversalRotate(const int first_side, const int *second_side, int *position) {
    uint32_t first_mask = 0x000000FF;
    uint32_t temp = (this->faces[first_side] & first_mask) << 24;
    this->faces[first_side] = (this->faces[first_side] >> 8) | temp;
    uint32_t second_mask = 0x00000000;
    for (size_t j = 0; j < 3; ++j) {
        second_mask |= 0xF0000000 >> (((j + position[3]) % 8) * 4);
    }
    uint32_t prev_edge = this->faces[second_side[3]] & second_mask;
    size_t prev_side_offset = position[3];
    for (size_t i = 0; i < 4; ++i) {
        second_mask = 0x00000000;
        for (size_t j = 0; j < 3; ++j) {
            second_mask |= 0xF0000000 >> (((j + position[i]) % 8) * 4);
        }
        temp = this->faces[second_side[i]] & second_mask;
        this->faces[second_side[i]] = (this->faces[second_side[i]] & (~second_mask));
        prev_edge = SetupEdge(prev_edge, prev_side_offset, position[i]);
        this->faces[second_side[i]] |= prev_edge;
        prev_edge = temp;
        prev_side_offset = position[i];
    }
}
void RubiksCube::RotateUp(bool reverse){
    for (int i = 0; reverse ? i < 3 : i < 1; ++i) {
        int index_side[4] = { 2, 1, 4, 3 };
        int offset_mask[4] = { 0, 0, 0, 0 };
        UniversalRotate(0, index_side, offset_mask);
    }
    if (!reverse)
        cout << "U ";
    else
        cout << "U' ";
}
void RubiksCube::RotateDown(bool reverse) {
    for (int i = 0; reverse ? i < 3 : i < 1; ++i) {
        int index_side[4] = { 2, 3, 4, 1 };
        int offset_mask[4] = { 4, 4, 4, 4 };
        UniversalRotate(5, index_side, offset_mask);
    }
    if (!reverse)
        cout << "D ";
    else
        cout << "D' ";
}
void RubiksCube::RotateLeft(bool reverse){
    for (int i = 0; reverse ? i < 3 : i < 1; ++i) {
        int index_side[4] = { 0, 2, 5, 4 };
        int offset_mask[4] = { 6, 6, 6, 2 };
        UniversalRotate(1, index_side, offset_mask);
    }
    if (!reverse)
        cout << "L ";
    else
        cout << "L' ";
}
void RubiksCube::RotateRight(bool reverse){
     for (int i = 0; reverse ? i < 3 : i < 1; ++i) {
        int index_side[4] = { 2, 0, 4, 5 };
        int offset_mask[4] = { 2, 2, 6, 2 };
        UniversalRotate(3, index_side, offset_mask);
    }
     if (!reverse)
        cout << "R ";
     else
        cout << "R' ";
}
void RubiksCube::RotateFront(bool reverse){
    for (int i = 0; reverse ? i < 3 : i < 1; ++i) {
        int index_side[4] = { 1, 0, 3, 5 };
        int offset_mask[4] = { 2, 4, 6, 0 };
        UniversalRotate(2, index_side, offset_mask);
    }
    if (!reverse)
        cout << "F ";
    else
        cout << "F' ";
}
void RubiksCube::RotateBack(bool reverse){
    for (int i = 0; reverse ? i < 3 : i < 1; ++i) {
        int index_side[4] = { 0, 1, 5, 3 };
        int offset_mask[4] = { 0, 6, 4, 2 };
        UniversalRotate(4, index_side, offset_mask);
    }
    if (!reverse)
        cout << "B ";
    else
        cout << "B' ";
}
void RubiksCube::RandomizedCube(){
    srand(static_cast<unsigned int>(time(nullptr)));
    int counter = rand();
    for (int i = 0; i < counter%77; ++i) {
        for (int j = 0; j < counter % 3; ++j) {
            this->RotateUp(false);
        }
        for (int j = 0; j < counter % 4; ++j) {
            this->RotateDown(false);
        }
        for (int j = 0; j < counter % 2; ++j) {
            this->RotateLeft(false);
        }
        if (i % 2 == 0)
            this->RotateUp(true);
        this->RotateRight(true);
        for (int j = 0; j < counter % 2; ++j) {
            this->RotateRight(false);
        }
        if (i % 2 == 1)
            this->RotateUp(true);
        for (int j = 0; j < counter % 2; ++j) {
            this->RotateFront(false);
        }
        this->RotateRight(true);
        for (int j = 0; j < counter % 2; ++j) {
            this->RotateBack(false);
        }
    }
//    this->RotateLeft(false);
//    this->RotateBack(false);
//    this->RotateRight(false);
//    this->RotateUp(false);
//    this->RotateFront(false);
//    this->RotateDown(false);
//    this->RotateUp(false);
//    this->RotateLeft(true);
//    this->RotateFront(true);
    //#1
//    c.RotateLeft(false);
//    c.RotateBack(false);
//    c.RotateRight(false);
//    c.RotateUp(false);
//    c.RotateFront(false);
//    c.RotateDown(false);
//    c.RotateUp(false);
//    c.RotateLeft(true);
//    c.RotateFront(true);
    //#2
//    c.RotateBack(false);
//    c.RotateLeft(false);
//    c.RotateLeft(false);
//    c.RotateBack(true);
//    c.RotateRight(true);
//    c.RotateBack(true);
//    c.RotateLeft(false);
    //#3
//    c.RotateLeft(false);
//    c.RotateBack(false);
//    c.RotateLeft(true);
//    c.RotateRight(false);
//    c.RotateUp(true);
//    c.RotateLeft(false);
//    c.RotateUp(false);
//    c.RotateRight(false);
//    c.RotateRight(false);
//    c.RotateUp(true);
    //#4
//    c.RotateLeft(false);
//    c.RotateBack(false);
//    c.RotateBack(false);
//    c.RotateUp(false);
//    c.RotateLeft(true);
//    c.RotateLeft(true);
//    c.RotateRight(false);
//    c.RotateBack(false);
//    c.RotateUp(true);
//    c.RotateLeft(true);
//    c.RotateRight(false);
//    c.RotateUp(true);
    //#5
//    c.RotateBack(false);
//    c.RotateBack(true);
}
int RubiksCube::GetColor(int side, int cube){
    return (this->faces[side] << cube * 4) >> 28;
}
void RubiksCube::WhiteRotation(int cube){
    while (GetColor(5, cube) == 0){
        this->RotateDown(false);
    }
}
void RubiksCube::Flower() {
    int counter = 0;
    while(counter < 4){
        //up
        counter = 0;
        for (int j = 1; j <= 7; j += 2) {
            if (GetColor(5, j) == 0){
                counter += 1;
            }
        }
        if (GetColor(0, 1) == 0) {
            this->WhiteRotation(5);
            this->RotateBack(false);
            this->RotateBack(false);
        } else if (GetColor(0, 3) == 0) {
            this->WhiteRotation(3);
            this->RotateRight(false);
            this->RotateRight(false);
        } else if (GetColor(0, 5) == 0) {
            this->WhiteRotation(1);
            this->RotateFront(false);
            this->RotateFront(false);
        } else if (GetColor(0, 7) == 0) {
            this->WhiteRotation(7);
            this->RotateLeft(false);
            this->RotateLeft(false);
        }
        //left
        if (GetColor(1, 1) == 0) {
            this->WhiteRotation(7);
            this->RotateLeft(false);
            this->WhiteRotation(1);
            this->RotateFront(true);
        } else if (GetColor(1, 3) == 0) {
            this->WhiteRotation(1);
            this->RotateFront(true);
        } else if (GetColor(1, 5) == 0) {
            this->RotateLeft(false);
            this->RotateLeft(false);
            this->WhiteRotation(7);
            this->RotateLeft(false);
            this->WhiteRotation(1);
            this->RotateFront(true);
        } else if (GetColor(1, 7) == 0) {
            this->WhiteRotation(7);
            this->RotateBack(false);
        }
        //front
        if (GetColor(2, 1) == 0) {
            this->WhiteRotation(1);
            this->RotateFront(false);
            this->WhiteRotation(3);
            this->RotateRight(true);
        } else if (GetColor(2, 3) == 0) {
            this->WhiteRotation(3);
            this->RotateRight(true);
        } else if (GetColor(2, 5) == 0) {
            this->RotateFront(false);
            this->RotateFront(false);
            this->WhiteRotation(1);
            this->RotateFront(false);
            this->WhiteRotation(3);
            this->RotateRight(true);
        } else if (GetColor(2, 7) == 0) {
            this->WhiteRotation(7);
            this->RotateLeft(false);
        }
        //right
        if (GetColor(3, 1) == 0) {
            this->WhiteRotation(3);
            this->RotateRight(false);
            this->WhiteRotation(5);
            this->RotateBack(true);
        } else if (GetColor(3, 3) == 0) {
            this->WhiteRotation(5);
            this->RotateBack(true);
        } else if (GetColor(3, 5) == 0) {
            this->RotateRight(false);
            this->RotateRight(false);
            this->WhiteRotation(3);
            this->RotateRight(false);
            this->WhiteRotation(5);
            this->RotateBack(true);
        } else if (GetColor(3, 7) == 0) {
            this->WhiteRotation(1);
            this->RotateFront(false);
        }
        //back
        if (GetColor(4, 1) == 0) {
            this->WhiteRotation(5);
            this->RotateBack(false);
            this->WhiteRotation(7);
            this->RotateLeft(true);
        } else if (GetColor(4, 3) == 0) {
            this->WhiteRotation(7);
            this->RotateLeft(true);
        } else if (GetColor(4, 5) == 0) {
            this->RotateBack(false);
            this->RotateBack(false);
            this->WhiteRotation(5);
            this->RotateBack(false);
            this->WhiteRotation(7);
            this->RotateLeft(true);
        } else if (GetColor(4, 7) == 0) {
            this->WhiteRotation(3);
            this->RotateRight(false);
        }
    }
}
void RubiksCube::Cross(){
    while (GetColor(1, 5) != 1|| GetColor(5, 7) != 0){
        this->RotateDown(false);
    }
    this->RotateLeft(false);
    this->RotateLeft(false);
    while (GetColor(2, 5) != 2|| GetColor(5, 1) != 0){
        this->RotateDown(false);
    }
    this->RotateFront(false);
    this->RotateFront(false);
    while (GetColor(3, 5) != 3|| GetColor(5, 3) != 0){
        this->RotateDown(false);
    }
    this->RotateRight(false);
    this->RotateRight(false);
    while (GetColor(4, 5) != 4 || GetColor(5, 5) != 0){
        this->RotateDown(false);
    }
    this->RotateBack(false);
    this->RotateBack(false);
}
void RubiksCube::PifPuf() {
    int counter = 0;
    while (counter < 4){
        counter = 0;
        for (int j = 0; j <= 6; j += 2) {
            if (GetColor(0, j) == 0){
                if((j == 0 && GetColor(1, 0) == 1 && GetColor(4, 2) == 4) ||
                        (j == 2 && GetColor(3, 2) == 3 && GetColor(4, 0) == 4) ||
                        (j == 4 && GetColor(2, 2) == 2 && GetColor(3, 0) == 3) ||
                        (j == 6 && GetColor(1, 2) == 1 && GetColor(2, 0) == 2)){
                    counter += 1;
                }
            }
        }
//        if (counter == 2){
//            this->Print();
//            system("pause");
//        }
        int color1, color2;
        //on down
        if (GetColor(5, 0) == 0 || GetColor(1, 4) == 0 || GetColor(2, 6) == 0){
            if(GetColor(5, 0) == 0)
                color1 = GetColor(1, 4), color2 = GetColor(2, 6);
            else if(GetColor(1, 4) == 0)
                color1 = GetColor(5, 0), color2 = GetColor(2, 6);
            else if(GetColor(2, 6) == 0)
                color1 = GetColor(5, 0), color2 = GetColor(1, 4);
            if (color1 == 1 && color2 == 2 || color1 == 2 && color2 == 1){
                while(GetColor(0, 6) != 0){
                    this->RotateFront(true);
                    this->RotateDown(true);
                    this->RotateFront(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 2 && color2 == 3 || color1 == 3 && color2 == 2){
                this->RotateDown(false);
                while(GetColor(0, 4) != 0){
                    this->RotateRight(true);
                    this->RotateDown(true);
                    this->RotateRight(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 3 && color2 == 4 || color1 == 4 && color2 == 3){
                this->RotateDown(false);
                this->RotateDown(false);
                while(GetColor(0, 2) != 0){
                    this->RotateBack(true);
                    this->RotateDown(true);
                    this->RotateBack(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 1 && color2 == 4 || color1 == 4 && color2 == 1){
                this->RotateDown(true);
                while(GetColor(0, 0) != 0){
                    this->RotateLeft(true);
                    this->RotateDown(true);
                    this->RotateLeft(false);
                    this->RotateDown(false);
                }
            }
        }
        if (GetColor(5, 2) == 0 || GetColor(2, 4) == 0 || GetColor(3, 6) == 0){
            if(GetColor(5, 2) == 0)
                color1 = GetColor(2, 4), color2 = GetColor(3, 6);
            else if(GetColor(2, 4) == 0)
                color1 = GetColor(5, 2), color2 = GetColor(3, 6);
            else if(GetColor(3, 6) == 0)
                color1 = GetColor(5, 2), color2 = GetColor(2, 4);
            if (color1 == 1 && color2 == 2 || color1 == 2 && color2 == 1){
                this->RotateDown(true);
                while(GetColor(0, 6) != 0){
                    this->RotateFront(true);
                    this->RotateDown(true);
                    this->RotateFront(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 2 && color2 == 3 || color1 == 3 && color2 == 2){
                while(GetColor(0, 4) != 0){
                    this->RotateRight(true);
                    this->RotateDown(true);
                    this->RotateRight(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 3 && color2 == 4 || color1 == 4 && color2 == 3){
                this->RotateDown(false);
                while(GetColor(0, 2) != 0){
                    this->RotateBack(true);
                    this->RotateDown(true);
                    this->RotateBack(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 1 && color2 == 4 || color1 == 4 && color2 == 1){
                this->RotateDown(false);
                this->RotateDown(false);
                while(GetColor(0, 0) != 0){
                    this->RotateLeft(true);
                    this->RotateDown(true);
                    this->RotateLeft(false);
                    this->RotateDown(false);
                }
            }
        }
        if (GetColor(5, 4) == 0 || GetColor(3, 4) == 0 || GetColor(4, 6) == 0){
            if(GetColor(5, 4) == 0)
                color1 = GetColor(3, 4), color2 = GetColor(4, 6);
            else if(GetColor(3, 4) == 0)
                color1 = GetColor(5, 4), color2 = GetColor(4, 6);
            else if(GetColor(4, 6) == 0)
                color1 = GetColor(5, 4), color2 = GetColor(3, 4);
            if (color1 == 1 && color2 == 2 || color1 == 2 && color2 == 1){
                this->RotateDown(false);
                this->RotateDown(false);
                while(GetColor(0, 6) != 0){
                    this->RotateFront(true);
                    this->RotateDown(true);
                    this->RotateFront(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 2 && color2 == 3 || color1 == 3 && color2 == 2){
                this->RotateDown(true);
                while(GetColor(0, 4) != 0){
                    this->RotateRight(true);
                    this->RotateDown(true);
                    this->RotateRight(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 3 && color2 == 4 || color1 == 4 && color2 == 3){
                while(GetColor(0, 2) != 0){
                    this->RotateBack(true);
                    this->RotateDown(true);
                    this->RotateBack(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 1 && color2 == 4 || color1 == 4 && color2 == 1){
                this->RotateDown(false);
                while(GetColor(0, 0) != 0){
                    this->RotateLeft(true);
                    this->RotateDown(true);
                    this->RotateLeft(false);
                    this->RotateDown(false);
                }
            }
        }
        if (GetColor(5, 6) == 0 || GetColor(4, 4) == 0 || GetColor(1, 6) == 0){
            if(GetColor(5, 6) == 0)
                color1 = GetColor(4, 4), color2 = GetColor(1, 6);
            else if(GetColor(4, 4) == 0)
                color1 = GetColor(5, 6), color2 = GetColor(1, 6);
            else if(GetColor(1, 6) == 0)
                color1 = GetColor(5, 6), color2 = GetColor(4, 4);
            if (color1 == 1 && color2 == 2 || color1 == 2 && color2 == 1){
                this->RotateDown(false);
                while(GetColor(0, 6) != 0){
                    this->RotateFront(true);
                    this->RotateDown(true);
                    this->RotateFront(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 2 && color2 == 3 || color1 == 3 && color2 == 2){
                this->RotateDown(false);
                this->RotateDown(false);
                while(GetColor(0, 4) != 0){
                    this->RotateRight(true);
                    this->RotateDown(true);
                    this->RotateRight(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 3 && color2 == 4 || color1 == 4 && color2 == 3){
                this->RotateDown(true);
                while(GetColor(0, 2) != 0){
                    this->RotateBack(true);
                    this->RotateDown(true);
                    this->RotateBack(false);
                    this->RotateDown(false);
                }
            } else if (color1 == 1 && color2 == 4 || color1 == 4 && color2 == 1){
                while(GetColor(0, 0) != 0){
                    this->RotateLeft(true);
                    this->RotateDown(true);
                    this->RotateLeft(false);
                    this->RotateDown(false);
                }
            }
        }
        //on up
        if (!(GetColor(0, 0) == 0 && GetColor(1, 0) == 1 && GetColor(4, 2) == 4) &&
        (GetColor(0, 0) == 0 || GetColor(1, 0) == 0 || GetColor(4, 2) == 0)){
            this->RotateBack(false);
            this->RotateDown(false);
            this->RotateBack(true);
        }
        if (!(GetColor(0, 2) == 0 && GetColor(3, 2) == 3 && GetColor(4, 0) == 4) &&
        (GetColor(0, 2) == 0 || GetColor(3, 2) == 0 || GetColor(4, 0) == 0)){
            this->RotateBack(true);
            this->RotateDown(true);
            this->RotateBack(false);
        }
        if (!(GetColor(0, 4) == 0 && GetColor(2, 2) == 2 && GetColor(3, 0) == 3) &&
        (GetColor(0, 4) == 0 || GetColor(2, 2) == 0 || GetColor(3, 0) == 0)){
            this->RotateRight(true);
            this->RotateDown(true);
            this->RotateRight(false);
        }
        if (!(GetColor(0, 6) == 0 && GetColor(1, 2) == 1 && GetColor(2, 0) == 2) &&
        (GetColor(0, 6) == 0 || GetColor(1, 2) == 0 || GetColor(2, 0) == 0)){
            this->RotateLeft(false);
            this->RotateDown(false);
            this->RotateLeft(true);
        }
    }
}
void RubiksCube::MiddleLayer(){
    int count = 0;
    while (count != 4) {
        count = 0;
        if (GetColor(1, 3) == 1 && GetColor(2, 7) == 2)
            count += 1;
        if (GetColor(2, 3) == 2 && GetColor(3, 7) == 3)
            count += 1;
        if (GetColor(3, 3) == 3 && GetColor(4, 7) == 4)
            count += 1;
        if (GetColor(4, 3) == 4 && GetColor(1, 7) == 1)
            count += 1;
        //front face
        if (GetColor(2, 5) == 2) {
            if (GetColor(5, 1) == 1) {
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateFront(false);
            }
            else if (GetColor(5, 1) == 3) {
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(true);
                this->RotateFront(true);
            }
        }
        else if (GetColor(2, 5) == 3) {
            if (GetColor(5, 1) == 2) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(false);
                this->RotateRight(false);
            }
            else if (GetColor(5, 1) == 4) {
                this->RotateDown(false);
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(true);
                this->RotateRight(true);
            }
        }
        else if (GetColor(2, 5) == 4) {
            if (GetColor(5, 1) == 3) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateBack(false);
            }
            else if (GetColor(5, 1) == 1) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(true);
                this->RotateBack(true);
            }
        }
        else if (GetColor(2, 5) == 1) {
            if (GetColor(5, 1) == 4) {
                this->RotateDown(true);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateLeft(false);
            }
            else if (GetColor(5, 1) == 2) {
                this->RotateDown(true);
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(true);
                this->RotateLeft(true);
            }
        }
        //right face
        if (GetColor(3, 5) == 2) {
            if (GetColor(5, 3) == 1) {
                RotateDown(true);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateFront(false);
            }
            else if (GetColor(5, 3) == 3) {
                this->RotateDown(true);
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(true);
                this->RotateFront(true);
            }
        }
        else if (GetColor(3, 5) == 3) {
            if (GetColor(5, 3) == 2) {
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(false);
                this->RotateRight(false);
            }
            else if (GetColor(5, 3) == 4) {
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(true);
                this->RotateRight(true);
            }
        }
        else if (GetColor(3, 5) == 4) {
            if (GetColor(5, 3) == 3) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateBack(false);
            }
            else if (GetColor(5, 3) == 1) {
                this->RotateDown(false);
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(true);
                this->RotateBack(true);
            }
        }
        else if (GetColor(3, 5) == 1) {
            if (GetColor(5, 3) == 4) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateLeft(false);
            }
            else if (GetColor(5, 3) == 2) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(true);
                this->RotateLeft(true);
            }
        }
        //back face
        if (GetColor(4, 5) == 2) {
            if (GetColor(5, 5) == 1) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateFront(false);
            }
            else if (GetColor(5, 5) == 3) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(true);
                this->RotateFront(true);
            }
        }
        else if (GetColor(4, 5) == 3) {
            if (GetColor(5, 5) == 2) {
                this->RotateDown(true);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(false);
                this->RotateRight(false);
            }
            else if (GetColor(5, 5) == 4) {
                this->RotateDown(true);
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(true);
                this->RotateRight(true);
            }
        }
        else if (GetColor(4, 5) == 4) {
            if (GetColor(5, 5) == 3) {
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateBack(false);
            }
            else if (GetColor(5, 5) == 1) {
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(true);
                this->RotateBack(true);
            }
        }
        else if (GetColor(4, 5) == 1) {
            if (GetColor(5, 5) == 4) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateLeft(false);
            }
            else if (GetColor(5, 5) == 2) {
                this->RotateDown(false);
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(true);
                this->RotateLeft(true);
            }
        }
        //left face
        if (GetColor(1, 5) == 2) {
            if (GetColor(5, 7) == 1) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateFront(false);
            }
            else if (GetColor(5, 7) == 3) {
                this->RotateDown(false);
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(true);
                this->RotateFront(true);
            }
        }
        else if (GetColor(1, 5) == 3) {
            if (GetColor(5, 7) == 2) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(false);
                this->RotateRight(false);
            }
            else if (GetColor(5, 7) == 4) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(true);
                this->RotateRight(true);
            }
        }
        else if (GetColor(1, 5) == 4) {
            if (GetColor(5, 7) == 3) {
                this->RotateDown(true);
                this->RotateDown(false);
                this->RotateRight(false);
                this->RotateDown(true);
                this->RotateRight(true);
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateBack(false);
            }
            else if (GetColor(5, 7) == 1) {
                this->RotateDown(true);
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(true);
                this->RotateBack(true);
            }
        }
        else if (GetColor(1, 5) == 1) {
            if (GetColor(5, 7) == 4) {
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(true);
                this->RotateBack(true);
                this->RotateDown(true);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateLeft(false);
            }
            else if (GetColor(5, 7) == 2) {
                this->RotateDown(true);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(true);
                this->RotateLeft(true);
            }
        }
        if ((GetColor(1, 3) != 5 && GetColor(2, 7) != 5) &&
            !(GetColor(1, 3) == 1 && GetColor(2, 7) == 2)) {
            this->RotateLeft(false);
            this->RotateDown(true);
            this->RotateLeft(true);
            this->RotateDown(true);
            this->RotateFront(true);
            this->RotateDown(false);
            this->RotateFront(false);
        }
        if ((GetColor(2, 3) != 5 && GetColor(3, 7) != 5) &&
            !(GetColor(2, 3) == 2 && GetColor(3, 7) == 3)) {
            this->RotateFront(false);
            this->RotateDown(true);
            this->RotateFront(true);
            this->RotateDown(true);
            this->RotateRight(true);
            this->RotateDown(false);
            this->RotateRight(false);
        }
        if ((GetColor(3, 3) != 5 && GetColor(4, 7) != 5) &&
            !(GetColor(3, 3) == 3 && GetColor(4, 7) == 4)) {
            this->RotateRight(false);
            this->RotateDown(true);
            this->RotateRight(true);
            this->RotateDown(true);
            this->RotateBack(true);
            this->RotateDown(false);
            this->RotateBack(false);
        }
        if ((GetColor(4, 3) != 5 && GetColor(1, 7) != 5) &&
            !(GetColor(4, 3) == 4 && GetColor(1, 7) == 1)) {
            this->RotateBack(false);
            this->RotateDown(true);
            this->RotateBack(true);
            this->RotateDown(true);
            this->RotateLeft(true);
            this->RotateDown(false);
            this->RotateLeft(false);
        }
    }
}
void RubiksCube::DownCross(){
    if (GetColor(5, 1) == 5 &&
        GetColor(5, 3) == 5 &&
        GetColor(5, 5) == 5 &&
        GetColor(5, 7) == 5) {
        return;
    }
    if (GetColor(5, 1) != 5 &&
    GetColor(5, 3) != 5 &&
    GetColor(5, 5) != 5 &&
    GetColor(5, 7) != 5) {
        this->RotateFront(false);
        this->RotateLeft(false);
        this->RotateDown(false);
        this->RotateLeft(true);
        this->RotateDown(true);
        this->RotateFront(true);
    }
    if (GetColor(5, 1) == 5 && GetColor(5, 3) == 5){
        this->RotateDown(false);
        this->RotateFront(false);
        this->RotateLeft(false);
        this->RotateDown(false);
        this->RotateLeft(true);
        this->RotateDown(true);
        this->RotateFront(true);
    }
    else if (GetColor(5, 3) == 5 && GetColor(5, 5) == 5){
        this->RotateFront(false);
        this->RotateLeft(false);
        this->RotateDown(false);
        this->RotateLeft(true);
        this->RotateDown(true);
        this->RotateFront(true);
    }
    else if (GetColor(5, 5) == 5 && GetColor(5, 7) == 5){
        this->RotateDown(true);
        this->RotateFront(false);
        this->RotateLeft(false);
        this->RotateDown(false);
        this->RotateLeft(true);
        this->RotateDown(true);
        this->RotateFront(true);
    }
    else if (GetColor(5, 1) == 5 && GetColor(5, 7) == 5){
        this->RotateDown(false);
        this->RotateDown(false);
        this->RotateFront(false);
        this->RotateLeft(false);
        this->RotateDown(false);
        this->RotateLeft(true);
        this->RotateDown(true);
        this->RotateFront(true);
    }
    if (GetColor(5, 1) == 5 && GetColor(5, 5) == 5){
        this->RotateDown(false);
        this->RotateFront(false);
        this->RotateLeft(false);
        this->RotateDown(false);
        this->RotateLeft(true);
        this->RotateDown(true);
        this->RotateFront(true);
    }
    else if (GetColor(5, 3) == 5 && GetColor(5, 7) == 5){
        this->RotateFront(false);
        this->RotateLeft(false);
        this->RotateDown(false);
        this->RotateLeft(true);
        this->RotateDown(true);
        this->RotateFront(true);
    }
}
void RubiksCube::TrueDownCross(){
    int counter1 = 0, face = 1;
    while (counter1 < 4) {
        while (GetColor(face, 5) != face && face <= 3)
            this->RotateDown(false);
        counter1 = 0;
        for (int i = 1; i <= 4; ++i) {
            if (GetColor(i, 5) == i)
                counter1 += 1;
        }
        if (counter1 == 2 && face == 1) {
            if (GetColor(4, 5) == 4) {
                this->RotateLeft(false);
                this->RotateDown(false);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateLeft(true);
                this->RotateDown(false);
            }
            else if (GetColor(2, 5) == 2) {
                this->RotateFront(false);
                this->RotateDown(false);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateFront(true);
                this->RotateDown(false);
            }
            else if (GetColor(3, 5) == 3) {
                this->RotateBack(false);
                this->RotateDown(false);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateBack(true);
                this->RotateDown(false);
                face = 0;
            }
        }
        if (counter1 == 2 && face == 2) {
            if (GetColor(1, 5) == 1) {
                this->RotateDown(true);
                this->RotateLeft(false);
                this->RotateDown(false);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateDown(false);
            }
            else if (GetColor(2, 5) == 2) {
                this->RotateDown(true);
                this->RotateFront(false);
                this->RotateDown(false);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateDown(false);
            }
            else if (GetColor(3, 5) == 3) {
                this->RotateDown(true);
                this->RotateBack(false);
                this->RotateDown(false);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateDown(false);
                face = 0;
            }
        }
        if (counter1 == 2 && face == 3) {
            if (GetColor(1, 5) == 1) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(false);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateLeft(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateLeft(true);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateDown(false);
            }
            else if (GetColor(2, 5) == 2) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(false);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateFront(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateFront(true);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateDown(false);
            }
            else if (GetColor(3, 5) == 3) {
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(false);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateBack(false);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateBack(true);
                this->RotateDown(false);
                this->RotateDown(false);
                this->RotateDown(false);
                face = 0;
            }
        }
        face += 1;
    }
}
void RubiksCube::LastLayer(){
    int counter = 0, corner = -1;
    while (counter < 4){
        counter = 0;
        if ((GetColor(1, 4) == 1 || GetColor(2, 6) == 1 || GetColor(5, 0) == 1) &&
                (GetColor(1, 4) == 2 || GetColor(2, 6) == 2 || GetColor(5, 0) == 2)){
            corner = 0;
            counter += 1;
        }
        if ((GetColor(2, 4) == 2 || GetColor(3, 6) == 2 || GetColor(5, 2) == 2) &&
                (GetColor(2, 4) == 3 || GetColor(3, 6) == 3 || GetColor(5, 2) == 3)){
            corner = 1;
            counter += 1;
        }
        if ((GetColor(3, 4) == 3 || GetColor(4, 6) == 3 || GetColor(5, 4) == 3) &&
                (GetColor(3, 4) == 4 || GetColor(4, 6) == 4 || GetColor(5, 4) == 4)){
            corner = 2;
            counter += 1;
        }
        if ((GetColor(4, 4) == 1 || GetColor(1, 6) == 1 || GetColor(5, 6) == 1) &&
                (GetColor(4, 4) == 4 || GetColor(1, 6) == 4 || GetColor(5, 6) == 4)){
            corner = 3;
            counter += 1;
        }
        if (counter == 1 || counter == 0){
            for (int i = 0; i < corner; ++i) {
                this->RotateDown(true);
            }
            this->RotateDown(false);
            this->RotateLeft(false);
            this->RotateDown(true);
            this->RotateRight(true);
            this->RotateDown(false);
            this->RotateLeft(true);
            this->RotateDown(true);
            this->RotateRight(false);
            for (int i = 0; i < corner; ++i) {
                this->RotateDown(false);
            }
        }
    }
    while (GetColor(5, 0) != 5 || GetColor(1, 4) != GetColor(1, 5) || GetColor(2, 6) != GetColor(2, 5)){
        this->RotateLeft(true);
        this->RotateUp(false);
        this->RotateLeft(false);
        this->RotateUp(true);
    }
    this->RotateDown(false);
    while (GetColor(5, 0) != 5 || GetColor(1, 4) != GetColor(1, 5) || GetColor(2, 6) != GetColor(2, 5)){
        this->RotateLeft(true);
        this->RotateUp(false);
        this->RotateLeft(false);
        this->RotateUp(true);
    }
    this->RotateDown(false);
    while (GetColor(5, 0) != 5 || GetColor(1, 4) != GetColor(1, 5) || GetColor(2, 6) != GetColor(2, 5)){
        this->RotateLeft(true);
        this->RotateUp(false);
        this->RotateLeft(false);
        this->RotateUp(true);
    }
    this->RotateDown(false);
    while (GetColor(5, 0) != 5 || GetColor(1, 4) != GetColor(1, 5) || GetColor(2, 6) != GetColor(2, 5)){
        this->RotateLeft(true);
        this->RotateUp(false);
        this->RotateLeft(false);
        this->RotateUp(true);
    }
    while (GetColor(1, 4) != 1)
        this->RotateDown(false);
    while (GetColor(1, 2) != 1)
        this->RotateUp(false);
}
bool RubiksCube::CubeIsSolved(){
    //Checks if cube is solved correctly
    return faces[0] == 0x00000000 &&
    faces[1] == 0x11111111 &&
    faces[2] == 0x22222222 &&
    faces[3] == 0x33333333 &&
    faces[4] == 0x44444444 &&
    faces[5] == 0x55555555;
}
void InOutCube(int number, ostream &stream) {
    int a = number % 16;
    if (number / 16) InOutCube(number / 16, stream);
    stream << hex << number % 16;
}
void OutInCube(string number, istream &stream) {
    uint32_t out = 0;
    int power = 1;
    for (int i = 0; i < number.size(); ++i) {
        out += ((number[number.size() - i] - '0') * power);
        power *= 16;
    }
    stream >> out;
}
ostream& operator<<(ostream &out, RubiksCube &existing_cube){
    for (int i = 0; i < 6; ++i){
        InOutCube(existing_cube.faces[i], out);
        out << endl;
    }
    return out;
}
istream& operator>>(istream &in, RubiksCube &existing_cube){
    for (int i = 0; i < 6; ++i)
        OutInCube(to_string(existing_cube.faces[i]), in);
    return in;
}
RubiksCube::~RubiksCube(){
    delete []this->faces;
}

