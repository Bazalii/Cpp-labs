#ifndef GEOMETRY_H
#define GEOMETRY_H

class Point{
private:
    int x;
    int y;
public:
    Point();
    Point(int x, int y);
    Point(const Point &Copy_point);
    Point& operator=(const Point&);
    int getX() const;
    int getY() const;
};

class PolygonalChain{
protected:
    int NumberOfPoints = 0;
    Point *Array;
public:
    PolygonalChain(int numberOfPoints, Point *array);
    PolygonalChain(const PolygonalChain &CopyPolygonalChain);
    PolygonalChain& operator=(const PolygonalChain&);
    double perimeter() const;
    virtual int getN() const;
    Point * getArray() const;
    Point getPoint(int number) const;
    virtual ~PolygonalChain();
};

class ClosedPolygonalChain : public PolygonalChain{
public:
    ClosedPolygonalChain(int numberOfPoints, Point *array);
    ClosedPolygonalChain(const ClosedPolygonalChain &CopyClosedPolygonalChain);
    ClosedPolygonalChain& operator=(const ClosedPolygonalChain&);
    int getN() const override;
    ~ClosedPolygonalChain();
};

class Polygon : public ClosedPolygonalChain{
public:
    Polygon(int numberOfPoints, Point *array);
    Polygon(const Polygon &CopyPolygon);
    Polygon& operator=(const Polygon&);
    double area() const;
    static double triangle_area(const Point& point1, const Point& point2, const Point& point3) ;
    ~Polygon();
};

class Triangle: public ClosedPolygonalChain{
public:
    Triangle(int numberOfPoints, Point *array);
    Triangle(const Triangle &CopyTriangle);
    Triangle& operator=(const Triangle&);
    bool hasRightAngle() const;
    double area();
    ~Triangle();
};

class Trapezoid: public ClosedPolygonalChain{
public:
    Trapezoid(int numberOfPoints, Point *array);
    Trapezoid(const Trapezoid &CopyTrapezoid);
    Trapezoid& operator=(const Trapezoid&);
    double height() const;
    double area() const;
    ~Trapezoid();
};

class RegularPolygon: public Polygon{
public:
    RegularPolygon(int numberOfPoints, Point *array);
    RegularPolygon(const RegularPolygon &CopyRegularPolygon);
    RegularPolygon& operator=(const RegularPolygon&);
    ~RegularPolygon();
};

#endif