#include "geometry.h"
#include <cmath>
#include <iostream>
//todo indenation what

    Point::Point(){
        this->x = 0;
        this->y = 0;
    }
    Point::Point(int x, int y){
        this->x = x;
        this->y = y;
    }
    //todo no capital letters for variables
    Point::Point(const Point &Copy_point){
        this->x = Copy_point.getX();
        this->y = Copy_point.getY();
    }
    Point& Point::operator=(const Point &ExistingPoint){
        if (&ExistingPoint == this)
            return *this;
        this->x = ExistingPoint.getX();
        this->y = ExistingPoint.getY();
        return *this;
    }
    int Point::getX() const{
        return this->x;
    }
    int Point::getY() const{
        return this->y;
    }


    PolygonalChain::PolygonalChain(int numberOfPoints, Point *array){
        this->NumberOfPoints = numberOfPoints;
        this->Array = new Point[numberOfPoints];
        for (int i = 0; i < numberOfPoints; ++i) {
            this->Array[i] = array[i];
        }
    }
    PolygonalChain::PolygonalChain(const PolygonalChain &CopyPolygonalChain){
        this->NumberOfPoints = CopyPolygonalChain.NumberOfPoints;
        this->Array = new Point[this->NumberOfPoints];
        for (int i = 0; i < this->NumberOfPoints; ++i) {
            this->Array[i] = CopyPolygonalChain.Array[i];
        }
    }
    PolygonalChain& PolygonalChain::operator=(const PolygonalChain &ExistingPolygonalChain){
        if (&ExistingPolygonalChain == this)
            return *this;
        delete []this->Array;
        this->NumberOfPoints = ExistingPolygonalChain.getN();
        this->Array = new Point[this->NumberOfPoints];
        for (int i = 0; i < this->NumberOfPoints; ++i) {
            this->Array[i] = ExistingPolygonalChain.Array[i];
        }
        return *this;
    }
    double PolygonalChain::perimeter() const {
        double Perimeter = 0;
        for (int i = 0; i < (NumberOfPoints - 1); ++i) {
            Perimeter += pow(pow(Array[i].getX() - Array[i + 1].getX(), 2) + pow(Array[i].getY() - Array[i + 1].getY(), 2), 0.5);
        }
        return Perimeter;
    }
    int PolygonalChain::getN() const{
        return this->NumberOfPoints;
    }
    Point * PolygonalChain::getArray() const {
        return this->Array;
    }
    Point PolygonalChain::getPoint(int number) const {
        return this->Array[number];
    }
    PolygonalChain::~PolygonalChain(){
        delete []this->Array;
    }


    ClosedPolygonalChain::ClosedPolygonalChain(int numberOfPoints, Point *array) : PolygonalChain(numberOfPoints + 1, array) {
        this->Array[numberOfPoints] = array[0];
    }
    ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain &CopyClosedPolygonalChain) : PolygonalChain(CopyClosedPolygonalChain) {}
    ClosedPolygonalChain& ClosedPolygonalChain::operator=(const ClosedPolygonalChain &ExistingClosedPolygonalChain){
        if (&ExistingClosedPolygonalChain == this)
            return *this;
        delete []this->Array;
        this->NumberOfPoints = ExistingClosedPolygonalChain.getN();
        this->Array = new Point[this->NumberOfPoints];
        for (int i = 0; i < this->NumberOfPoints; ++i) {
            this->Array[i] = ExistingClosedPolygonalChain.Array[i];
        }
        return *this;
    }
    int ClosedPolygonalChain::getN() const{
        return this->NumberOfPoints - 1;
    }
    ClosedPolygonalChain::~ClosedPolygonalChain(){}


    Polygon::Polygon(int numberOfPoints, Point *array) : ClosedPolygonalChain(numberOfPoints, array) {}
    Polygon::Polygon(const Polygon &CopyPolygon) : ClosedPolygonalChain(CopyPolygon) {}
    //todo copy-paster opeartor
    Polygon& Polygon::operator=(const Polygon &ExistingPolygon){
        if (&ExistingPolygon == this)
            return *this;
        delete []this->Array;
        this->NumberOfPoints = ExistingPolygon.getN();
        this->Array = new Point[this->NumberOfPoints];
        for (int i = 0; i < this->NumberOfPoints; ++i) {
            this->Array[i] = ExistingPolygon.Array[i];
        }
        return *this;
    }
    double Polygon::area() const {
        double Area = 0;
        //todo Heron's formula is banned
        if (this->getN() == 3)
            Area += triangle_area(Array[0], Array[1], Array[2]);
        else{
            for (int i = 0; i < this->getN() - 2; ++i) {
            Area += triangle_area(Array[i], Array[i + 1], Array[this->getN() - 1]);
        }
        }
        return Area;
    }
    double Polygon::triangle_area(const Point& point1, const Point& point2, const Point& point3) {
        double SideA, SideB, SideC, TriangleArea;
        SideA = pow(pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2), 0.5);
        SideB = pow(pow(point1.getX() - point3.getX(), 2) + pow(point1.getY() - point3.getY(), 2), 0.5);
        SideC = pow(pow(point2.getX() - point3.getX(), 2) + pow(point2.getY() - point3.getY(), 2), 0.5);
        double HalfPerimeter = (SideA + SideB + SideC) / 2;
        TriangleArea = sqrt(HalfPerimeter * (HalfPerimeter - SideA) * (HalfPerimeter - SideB) * (HalfPerimeter - SideC));
        return TriangleArea;
    }
    Polygon::~Polygon(){}


    Triangle::Triangle(int numberOfPoints, Point *array) : ClosedPolygonalChain(numberOfPoints, array) {}
    Triangle::Triangle(const Triangle &CopyTriangle) : ClosedPolygonalChain(CopyTriangle) {}
    Triangle& Triangle::operator=(const Triangle &ExistingTriangle){
        if (&ExistingTriangle == this)
            return *this;
        for (int i = 0; i < this->NumberOfPoints; ++i) {
            this->Array[i] = ExistingTriangle.Array[i];
        }
        return *this;
    }
    //todo without sqrt
    bool Triangle::hasRightAngle() const {
        double SideA, SideB, SideC;
        SideA = pow(pow(Array[0].getX() - Array[1].getX(), 2) + pow(Array[0].getY() - Array[1].getY(), 2), 0.5);
        SideB = pow(pow(Array[0].getX() - Array[2].getX(), 2) + pow(Array[0].getY() - Array[2].getY(), 2), 0.5);
        SideC = pow(pow(Array[1].getX() - Array[2].getX(), 2) + pow(Array[1].getY() - Array[2].getY(), 2), 0.5);
        //todo return expression
        if  (pow(SideA, 2) == pow(SideB, 2) + pow(SideC, 2) || pow(SideB, 2) == pow(SideA, 2) + pow(SideC, 2) || pow(SideC, 2) == pow(SideA, 2) + pow(SideB, 2))
            return true;
        else
            return false;
    }
    double Triangle::area(){
        double SideA, SideB, SideC, Area;
        SideA = pow(pow(Array[0].getX() - Array[1].getX(), 2) + pow(Array[0].getY() - Array[1].getY(), 2), 0.5);
        SideB = pow(pow(Array[0].getX() - Array[2].getX(), 2) + pow(Array[0].getY() - Array[2].getY(), 2), 0.5);
        SideC = pow(pow(Array[1].getX() - Array[2].getX(), 2) + pow(Array[1].getY() - Array[2].getY(), 2), 0.5);
        double HalfPerimeter = (SideA + SideB + SideC) / 2;
        Area = sqrt(HalfPerimeter * (HalfPerimeter - SideA) * (HalfPerimeter - SideB) * (HalfPerimeter - SideC));
        return Area;
    }
    Triangle::~Triangle(){}


    Trapezoid::Trapezoid(int numberOfPoints, Point *array) : ClosedPolygonalChain(numberOfPoints, array) {}
    Trapezoid::Trapezoid(const Trapezoid &CopyTrapezoid) : ClosedPolygonalChain(CopyTrapezoid) {}
    Trapezoid& Trapezoid::operator=(const Trapezoid &ExistingTrapezoid){
        if (&ExistingTrapezoid == this)
            return *this;
        for (int i = 0; i < this->NumberOfPoints; ++i) {
            this->Array[i] = ExistingTrapezoid.Array[i];
        }
        return *this;
    }
    double Trapezoid::height() const {
        double Height, cos, sin, CoordinateAX, CoordinateAY, CoordinateBX, CoordinateBY;
        CoordinateAX = Array[1].getX() - Array[0].getX();
        CoordinateAY = Array[1].getY() - Array[0].getY();
        CoordinateBX = Array[3].getX() - Array[0].getX();
        CoordinateBY = Array[3].getY() - Array[0].getY();
        cos = ((CoordinateAX) * (CoordinateBX)  + (CoordinateAY) * (CoordinateBY)) / (sqrt(pow(CoordinateAX, 2) + pow(CoordinateAY, 2)) * sqrt(pow(CoordinateBX, 2) + pow(CoordinateBY, 2)));
        sin = sqrt(1 - pow(cos, 2));
        Height = sqrt(pow(CoordinateAX, 2) + pow(CoordinateAY, 2)) * sin;
        return Height;
    }
    double Trapezoid::area() const{
        double Area, SideA, SideB;
        SideA = pow(pow(Array[0].getX() - Array[3].getX(), 2) + pow(Array[0].getY() - Array[3].getY(), 2), 0.5);
        SideB = pow(pow(Array[1].getX() - Array[2].getX(), 2) + pow(Array[1].getY() - Array[2].getY(), 2), 0.5);
        Area = this->height() * (SideA + SideB) / 2;
        return Area;
    }
    Trapezoid::~Trapezoid(){}

    //todo area and perimeter
    RegularPolygon::RegularPolygon(int numberOfPoints, Point *array) : Polygon(numberOfPoints, array) {}
    RegularPolygon::RegularPolygon(const RegularPolygon &CopyRegularPolygon) : Polygon(CopyRegularPolygon) {}
    RegularPolygon& RegularPolygon::operator=(const RegularPolygon &ExistingRegularPolygon){
        if (&ExistingRegularPolygon == this)
            return *this;
        delete []this->Array;
        this->NumberOfPoints = ExistingRegularPolygon.getN();
        this->Array = new Point[this->NumberOfPoints];
        for (int i = 0; i < this->NumberOfPoints; ++i) {
            this->Array[i] = ExistingRegularPolygon.Array[i];
        }
        return *this;
    }
    RegularPolygon::~RegularPolygon(){}