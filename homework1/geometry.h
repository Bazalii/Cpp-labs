#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cmath>

class Point{
private:
    int x;
    int y;
public:
    Point();
    Point(int x, int y);
    Point(const Point &other);
    Point& operator=(const Point&);
    int getX() const;
    int getY() const;
};

class PolygonalChain{
protected:
    int number_of_points = 0;
    Point *array_of_points;
public:
    PolygonalChain(int number, Point *array);
    PolygonalChain(const PolygonalChain &other);
    PolygonalChain& operator=(const PolygonalChain&);
    double perimeter() const;
    virtual int getN() const;
    Point * getArray() const;
    Point getPoint(int number) const;
    virtual ~PolygonalChain();
};

class ClosedPolygonalChain : public PolygonalChain{
public:
    ClosedPolygonalChain(int number, Point *array);
    ClosedPolygonalChain(const ClosedPolygonalChain &other);
    using PolygonalChain::operator=;
    int getN() const override;
    ~ClosedPolygonalChain();
};

class Polygon : public ClosedPolygonalChain{
public:
    Polygon(int number, Point *array);
    Polygon(const Polygon &CopyPolygon);
    using PolygonalChain::operator=;
    double area() const;
    static double triangle_area(const Point& point1, const Point& point2, const Point& point3) ;
    ~Polygon();
};

class Triangle: public ClosedPolygonalChain{
public:
    Triangle(int number, Point *array);
    Triangle(const Triangle &CopyTriangle);
    using PolygonalChain::operator=;
    bool hasRightAngle() const;
    float area();
    ~Triangle();
};

class Trapezoid: public ClosedPolygonalChain{
public:
    Trapezoid(int number, Point *array);
    Trapezoid(const Trapezoid &other);
    using PolygonalChain::operator=;
    double height() const;
    double area() const;
    ~Trapezoid();
};

class RegularPolygon: public Polygon{
public:
    RegularPolygon(int number, Point *array);
    RegularPolygon(const RegularPolygon &other);
    double getSide() const;
    double perimeter() const;
    double area() const;
    using PolygonalChain::operator=;
    ~RegularPolygon();
};

#endif