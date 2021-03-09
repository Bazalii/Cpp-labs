#include "geometry.h"
#include <cmath>
#include <iostream>
//fixed indenation what

Point::Point(){
    this->x = 0;
    this->y = 0;
}
Point::Point(int x, int y){
    this->x = x;
    this->y = y;
}
//fixed no capital letters for variables
Point::Point(const Point &other){
    this->x = other.getX();
    this->y = other.getY();
}
Point& Point::operator=(const Point &other){
    if (&other == this)
        return *this;
    this->x = other.getX();
    this->y = other.getY();
    return *this;
}
int Point::getX() const{
    return this->x;
}
int Point::getY() const{
    return this->y;
}


PolygonalChain::PolygonalChain(int number, Point *array){
    this->number_of_points = number;
    this->array_of_points = new Point[number];
    for (int i = 0; i < number; ++i) {
        this->array_of_points[i] = array[i];
    }
}
PolygonalChain::PolygonalChain(const PolygonalChain &other){
    this->number_of_points = other.number_of_points;
    this->array_of_points = new Point[this->number_of_points];
    for (int i = 0; i < this->number_of_points; ++i) {
        this->array_of_points[i] = other.array_of_points[i];
    }
}
PolygonalChain& PolygonalChain::operator=(const PolygonalChain &other){
    if (&other == this)
        return *this;
    delete []this->array_of_points;
    this->number_of_points = other.getN();
    this->array_of_points = new Point[this->number_of_points];
    for (int i = 0; i < this->number_of_points; ++i) {
        this->array_of_points[i] = other.array_of_points[i];
    }
    return *this;
}
double PolygonalChain::perimeter() const {
    double pc_perimeter = 0;
    for (int i = 0; i < (number_of_points - 1); ++i) {
        pc_perimeter += pow(pow(array_of_points[i].getX() - array_of_points[i + 1].getX(), 2) + pow(array_of_points[i].getY() - array_of_points[i + 1].getY(), 2), 0.5);
    }
    return pc_perimeter;
}
int PolygonalChain::getN() const{
    return this->number_of_points;
}
Point * PolygonalChain::getArray() const {
    return this->array_of_points;
}
Point PolygonalChain::getPoint(int number) const {
    return this->array_of_points[number];
}
PolygonalChain::~PolygonalChain(){
    delete []this->array_of_points;
}


ClosedPolygonalChain::ClosedPolygonalChain(int number, Point *array) : PolygonalChain(number + 1, array) {
    this->array_of_points[number] = array[0];
}
ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain &other) : PolygonalChain(other) {}

int ClosedPolygonalChain::getN() const{
    return this->number_of_points - 1;
}
ClosedPolygonalChain::~ClosedPolygonalChain(){}


Polygon::Polygon(int number, Point *array) : ClosedPolygonalChain(number, array) {}
Polygon::Polygon(const Polygon &other) : ClosedPolygonalChain(other) {}
//fixed copy-paster opeartor
double Polygon::area() const {
    double p_area = 0;
    //fixed Heron's formula is banned
    if (this->getN() == 3)
        p_area += triangle_area(array_of_points[0], array_of_points[1], array_of_points[2]);
    else{
        for (int i = 0; i < this->getN() - 2; ++i) {
            p_area += triangle_area(array_of_points[i], array_of_points[i + 1], array_of_points[this->getN() - 1]);
    }
    }
    return p_area;
}
double Polygon::triangle_area(const Point& point1, const Point& point2, const Point& point3) {
    double t_area, cos, sin, coordinate_ax, coordinate_ay, coordinate_bx, coordinate_by;
    coordinate_ax = point2.getX() - point1.getX();
    coordinate_ay = point2.getY() - point1.getY();
    coordinate_bx = point3.getX() - point1.getX();
    coordinate_by = point3.getY() - point1.getY();
    cos = ((coordinate_ax) * (coordinate_bx) + (coordinate_ay) * (coordinate_by)) / (sqrt(pow(coordinate_ax, 2) + pow(coordinate_ay, 2)) * sqrt(pow(coordinate_bx, 2) + pow(coordinate_by, 2)));
    sin = sqrt(1 - pow(cos, 2));
    t_area = 0.5 * sqrt(pow(coordinate_ax, 2) + pow(coordinate_ay, 2)) * sqrt(pow(coordinate_bx, 2) + pow(coordinate_by, 2)) * sin;
    return t_area;
}
Polygon::~Polygon(){}


Triangle::Triangle(int number, Point *array) : ClosedPolygonalChain(number, array) {}
Triangle::Triangle(const Triangle &other) : ClosedPolygonalChain(other) {}
//fixed without sqrt
bool Triangle::hasRightAngle() const {
    double first_side_deg, second_side_deg, third_side_deg;
    first_side_deg = pow(array_of_points[0].getX() - array_of_points[1].getX(), 2) + pow(array_of_points[0].getY() - array_of_points[1].getY(), 2);
    second_side_deg = pow(array_of_points[0].getX() - array_of_points[2].getX(), 2) + pow(array_of_points[0].getY() - array_of_points[2].getY(), 2);
    third_side_deg = pow(array_of_points[1].getX() - array_of_points[2].getX(), 2) + pow(array_of_points[1].getY() - array_of_points[2].getY(), 2);
    //fixed return expression
    return ((first_side_deg == second_side_deg + third_side_deg) || (second_side_deg == first_side_deg + third_side_deg) || (third_side_deg == first_side_deg + second_side_deg));
}
float Triangle::area(){
    double cos, sin, coordinate_ax, coordinate_ay, coordinate_bx, coordinate_by;
    float t_area;
    coordinate_ax = array_of_points[1].getX() - array_of_points[0].getX();
    coordinate_ay = array_of_points[1].getY() - array_of_points[0].getY();
    coordinate_bx = array_of_points[2].getX() - array_of_points[0].getX();
    coordinate_by = array_of_points[2].getY() - array_of_points[0].getY();
    cos = ((coordinate_ax) * (coordinate_bx) + (coordinate_ay) * (coordinate_by)) / (sqrt(pow(coordinate_ax, 2) + pow(coordinate_ay, 2)) * sqrt(pow(coordinate_bx, 2) + pow(coordinate_by, 2)));
    sin = sqrt(1 - pow(cos, 2));
    t_area = 0.5 * sqrt(pow(coordinate_ax, 2) + pow(coordinate_ay, 2)) * sqrt(pow(coordinate_bx, 2) + pow(coordinate_by, 2)) * sin;
    return t_area;
}
Triangle::~Triangle(){}


Trapezoid::Trapezoid(int number, Point *array) : ClosedPolygonalChain(number, array) {}
Trapezoid::Trapezoid(const Trapezoid &other) : ClosedPolygonalChain(other) {}
double Trapezoid::height() const {
    double height, cos, sin, coordinate_ax, coordinate_ay, coordinate_bx, coordinate_by;
    coordinate_ax = array_of_points[1].getX() - array_of_points[0].getX();
    coordinate_ay = array_of_points[1].getY() - array_of_points[0].getY();
    coordinate_bx = array_of_points[3].getX() - array_of_points[0].getX();
    coordinate_by = array_of_points[3].getY() - array_of_points[0].getY();
    cos = ((coordinate_ax) * (coordinate_bx) + (coordinate_ay) * (coordinate_by)) / (sqrt(pow(coordinate_ax, 2) + pow(coordinate_ay, 2)) * sqrt(pow(coordinate_bx, 2) + pow(coordinate_by, 2)));
    sin = sqrt(1 - pow(cos, 2));
    height = sqrt(pow(coordinate_ax, 2) + pow(coordinate_ay, 2)) * sin;
    return height;
}
double Trapezoid::area() const{
    double tr_area, first_side, second_side;
    first_side = pow(pow(array_of_points[0].getX() - array_of_points[3].getX(), 2) + pow(array_of_points[0].getY() - array_of_points[3].getY(), 2), 0.5);
    second_side = pow(pow(array_of_points[1].getX() - array_of_points[2].getX(), 2) + pow(array_of_points[1].getY() - array_of_points[2].getY(), 2), 0.5);
    tr_area = this->height() * (first_side + second_side) / 2;
    return tr_area;
}
Trapezoid::~Trapezoid(){}

//fixed area and perimeter
RegularPolygon::RegularPolygon(int number, Point *array) : Polygon(number, array) {}
RegularPolygon::RegularPolygon(const RegularPolygon &other) : Polygon(other) {}
double RegularPolygon::getSide() const{
    double coordinate_ax, coordinate_ay;
    coordinate_ax = array_of_points[1].getX() - array_of_points[0].getX();
    coordinate_ay = array_of_points[1].getY() - array_of_points[0].getY();
    return sqrt(pow(coordinate_ax, 2) + pow(coordinate_ay, 2));
}
double RegularPolygon::perimeter() const{
    return (number_of_points - 1) * getSide();
}
double RegularPolygon::area() const{
    return (number_of_points - 1) * ((pow(getSide(), 2)) / (4 * tan(M_PI / (number_of_points - 1))));
}
RegularPolygon::~RegularPolygon(){}