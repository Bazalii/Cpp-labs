#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include "geometry.h"

using namespace std;

const double EPS = 1e-9;

//class Point{
//private:
//    int x;
//    int y;
//public:
//    Point(){
//        this->x = 0;
//        this->y = 0;
//    }
//    Point(int x, int y){
//        this->x = x;
//        this->y = y;
//    }
//    Point(const Point &Copy_point){
//        this->x = Copy_point.getX();
//        this->y = Copy_point.getY();
//    }
//    [[nodiscard]] int getX() const{ //?
//        return this->x;
//    }
//    [[nodiscard]] int getY() const{
//        return this->y;
//    }
//};
//
//class PolygonalChain{
//protected:
//    int NumberOfPoints = 0;
//    Point *Array;
//public:
//    PolygonalChain(int numberOfPoints, Point *array){ // затемнение?
//        this->NumberOfPoints = numberOfPoints;
//        Array = new Point[numberOfPoints + 1];
//        for (int i = 0; i < numberOfPoints; ++i) {
//            this->Array[i] = array[i];
//        }
//    }
//    PolygonalChain(const PolygonalChain &CopyPolygonalChain){
//        this->NumberOfPoints = CopyPolygonalChain.NumberOfPoints;
//        this->Array = CopyPolygonalChain.Array;
//    }
//
//    PolygonalChain() {}
//
//
//    double perimeter() const {
//        double Perimeter = 0;
//        for (int i = 0; i < (NumberOfPoints - 1); ++i) {
//            Perimeter += pow(pow(Array[i].getX() - Array[i + 1].getX(), 2) + pow(Array[i].getY() - Array[i + 1].getY(), 2), 0.5);
//        }
//        return Perimeter;
//    }
//    [[nodiscard]] int getN() const{
//        return this->NumberOfPoints;
//    }
//    Point * getArray() const {
//        return this->Array;
//    }
//    Point getPoint(int number) const {
//        return this->Array[number];
//    }
//};
//
//class ClosedPolygonalChain : public PolygonalChain{
//public:
//    ClosedPolygonalChain(int numberOfPoints, Point *array) : PolygonalChain(numberOfPoints, array) {
//        this->NumberOfPoints = numberOfPoints + 1;
//        Array[numberOfPoints] = array[0];
//    }
//    ClosedPolygonalChain(const ClosedPolygonalChain &CopyClosedPolygonalChain){
//        this->NumberOfPoints = CopyClosedPolygonalChain.NumberOfPoints;
//        this->Array = CopyClosedPolygonalChain.Array;
//    }
//
//    ClosedPolygonalChain() {}
//
//    [[nodiscard]] int getN() const{
//        return this->NumberOfPoints - 1;
//    }
//};
//
//class Polygon : public ClosedPolygonalChain{
////private:
////    int NumberOfPoints = 0;
////    Point *Array;
//public:
//    Polygon(int numberOfPoints, Point *array) : ClosedPolygonalChain(numberOfPoints, array) {}
//    Polygon(const Polygon &CopyPolygon){
//        this->NumberOfPoints = CopyPolygon.NumberOfPoints;
//        this->Array = CopyPolygon.Array;
//    }
//
//    Polygon() {}
//
//    double area() const {
//        double Area = 0;
//        if (this->getN() == 3)
//            Area += triangle_area(Array[0], Array[1], Array[2]);
//        else{
//            for (int i = 0; i < this->getN() - 2; ++i) {
//            Area += triangle_area(Array[i], Array[i + 1], Array[this->getN() - 1]);
//        }
//        }
//        return Area;
//    }
//    double triangle_area(Point point1, Point point2, Point point3) const {
//        double SideA, SideB, SideC, TriangleArea;
//        SideA = pow(pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2), 0.5);
//        SideB = pow(pow(point1.getX() - point3.getX(), 2) + pow(point1.getY() - point3.getY(), 2), 0.5);
//        SideC = pow(pow(point2.getX() - point3.getX(), 2) + pow(point2.getY() - point3.getY(), 2), 0.5);
//        double HalfPerimeter = (SideA + SideB + SideC) / 2;
//        TriangleArea = sqrt(HalfPerimeter * (HalfPerimeter - SideA) * (HalfPerimeter - SideB) * (HalfPerimeter - SideC));
//        return TriangleArea;
//    }
//};
//
//class Triangle: public ClosedPolygonalChain{
//public:
//    Triangle(int numberOfPoints, Point *array) : ClosedPolygonalChain(numberOfPoints, array) {}
//    Triangle(const Triangle &CopyTriangle){
//        this->NumberOfPoints = CopyTriangle.NumberOfPoints;
//        this->Array = CopyTriangle.Array;
//    }
//    bool hasRightAngle() const {
//        double SideA, SideB, SideC, Area;
//        SideA = pow(pow(Array[0].getX() - Array[1].getX(), 2) + pow(Array[0].getY() - Array[1].getY(), 2), 0.5);
//        SideB = pow(pow(Array[0].getX() - Array[2].getX(), 2) + pow(Array[0].getY() - Array[2].getY(), 2), 0.5);
//        SideC = pow(pow(Array[1].getX() - Array[2].getX(), 2) + pow(Array[1].getY() - Array[2].getY(), 2), 0.5);
//        if  (pow(SideA, 2) == pow(SideB, 2) + pow(SideC, 2))
//            return true;
//        else if (pow(SideB, 2) == pow(SideA, 2) + pow(SideC, 2))
//            return true;
//        else if (pow(SideC, 2) == pow(SideA, 2) + pow(SideB, 2))
//            return true;
//        else
//            return false;
//    }
//    double area(){
//        double SideA, SideB, SideC, Area;
//        SideA = pow(pow(Array[0].getX() - Array[1].getX(), 2) + pow(Array[0].getY() - Array[1].getY(), 2), 0.5);
//        SideB = pow(pow(Array[0].getX() - Array[2].getX(), 2) + pow(Array[0].getY() - Array[2].getY(), 2), 0.5);
//        SideC = pow(pow(Array[1].getX() - Array[2].getX(), 2) + pow(Array[1].getY() - Array[2].getY(), 2), 0.5);
//        double HalfPerimeter = (SideA + SideB + SideC) / 2;
//        Area = sqrt(HalfPerimeter * (HalfPerimeter - SideA) * (HalfPerimeter - SideB) * (HalfPerimeter - SideC));
//        return Area;
//    }
//};
//
//class Trapezoid: public ClosedPolygonalChain{
//public:
//    Trapezoid(int numberOfPoints, Point *array) : ClosedPolygonalChain(numberOfPoints, array) {}
//    Trapezoid(const Trapezoid &CopyTrapezoid){
//        this->NumberOfPoints = CopyTrapezoid.NumberOfPoints;
//        this->Array = CopyTrapezoid.Array;
//    }
//    double height() const {
//        double Height, cos, sin, CoordinateAX, CoordinateAY, CoordinateBX, CoordinateBY;
//        CoordinateAX = Array[1].getX() - Array[0].getX();
//        CoordinateAY = Array[1].getY() - Array[0].getY();
//        CoordinateBX = Array[3].getX() - Array[0].getX();
//        CoordinateBY = Array[3].getY() - Array[0].getY();
//        cos = ((CoordinateAX) * (CoordinateBX)  + (CoordinateAY) * (CoordinateBY)) / (sqrt(pow(CoordinateAX, 2) + pow(CoordinateAY, 2)) * sqrt(pow(CoordinateBX, 2) + pow(CoordinateBY, 2)));
//        sin = sqrt(1 - pow(cos, 2));
//        Height = sqrt(pow(CoordinateAX, 2) + pow(CoordinateAY, 2)) * sin;
////        SideA = pow(pow(Array[0].getX() - Array[3].getX(), 2) + pow(Array[0].getY() - Array[3].getY(), 2), 0.5);
////        SideB = pow(pow(Array[1].getX() - Array[2].getX(), 2) + pow(Array[1].getY() - Array[2].getY(), 2), 0.5);
////        SideC = pow(pow(Array[0].getX() - Array[1].getX(), 2) + pow(Array[0].getY() - Array[1].getY(), 2), 0.5);
////        SideD = pow(pow(Array[2].getX() - Array[3].getX(), 2) + pow(Array[2].getY() - Array[3].getY(), 2), 0.5);
////        Height = sqrt(pow(SideC, 2) + pow((pow(SideA - SideB, 2) + pow(SideC, 2) - pow(SideD, 2))/(2 * (SideA - SideB)), 2));
//        return Height;
//    }
//    [[nodiscard]] double area() const{
//        double Area, SideA, SideB;
//        SideA = pow(pow(Array[0].getX() - Array[3].getX(), 2) + pow(Array[0].getY() - Array[3].getY(), 2), 0.5);
//        SideB = pow(pow(Array[1].getX() - Array[2].getX(), 2) + pow(Array[1].getY() - Array[2].getY(), 2), 0.5);
//        Area = this->height() * (SideA + SideB) / 2;
//        return Area;
//    }
//};
//
//class RegularPolygon: public Polygon{
//public:
//    RegularPolygon(int numberOfPoints, Point *array) : Polygon(numberOfPoints, array) {}
//    RegularPolygon(const RegularPolygon &CopyRegularPolygon){
//        this->NumberOfPoints = CopyRegularPolygon.NumberOfPoints;
//        this->Array = CopyRegularPolygon.Array;
//    }
//};

void PointCheck() {
    const Point p1;
    assert(p1.getX() == 0 && p1.getY() == 0);
    const Point p2(3, 4);
    assert(p2.getX() == 3 && p2.getY() == 4);
}

void InheritancePolygonalChainCheck(const PolygonalChain *pc, const PolygonalChain *cpc) {
    assert(pc->perimeter() == 9);
    assert(cpc->perimeter() == 12);
}

void PolygonsCheck() {
    Point *a = new Point[3]{Point(0, 0), Point(3, 4), Point(3, 0)};
    Point *b = new Point[4]{Point(0, 0), Point(1, 4), Point(3, 4), Point(3, 0)};
    const Polygon p(3, a);
    const Triangle t(3, a);
    const Trapezoid tr(4, b);
    const PolygonalChain pc(3, a);
    assert(pc.getN() == 3 && pc.getPoint(1).getX() == 3 && pc.getPoint(1).getY() == 4);
    assert(pc.perimeter() == 9);
    const ClosedPolygonalChain cpc(3, a);
    a[1] = Point();
    assert(cpc.getN() == 3 && cpc.getPoint(1).getX() == 3 && cpc.getPoint(1).getY() == 4);
    assert(cpc.perimeter() == 12);
    InheritancePolygonalChainCheck(&pc, &cpc);
    assert(p.area() == 6);
    assert(abs(tr.height() - 4) < EPS);
    assert(t.hasRightAngle());
    Triangle trSharpestAsMyHand(3, new Point[3]{Point(0, 0), Point(1, 1), Point(0, 100)});
    assert(!trSharpestAsMyHand.hasRightAngle());
    RegularPolygon rp(4, new Point[4]{Point(0, 0), Point(0, 2), Point(2, 2), Point(2, 0)});
    assert(abs(rp.area() - 4) < EPS && abs(rp.perimeter() - 8) < EPS);
    Trapezoid tra(4, b);
    tra = tr;
    assert(abs(tra.height() - 4) < EPS);
    Trapezoid* trap = new Trapezoid(4, b);
    Trapezoid trCopy(*trap);
    delete trap;
    assert(abs(trCopy.height() - 4) < EPS);
}

int main() {
    PointCheck();
    PolygonsCheck();
}
