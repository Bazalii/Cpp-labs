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
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
};

class PolygonalChain{
protected:
    int NumberOfPoints = 0;
    Point *Array;
public:
    PolygonalChain(int numberOfPoints, Point *array);
    PolygonalChain(const PolygonalChain &CopyPolygonalChain);
    PolygonalChain& operator=(const PolygonalChain&);
    [[nodiscard]] double perimeter() const;
    [[nodiscard]] virtual int getN() const;
    [[maybe_unused]] [[nodiscard]] Point * getArray() const;
    [[nodiscard]] Point getPoint(int number) const;
    ~PolygonalChain();
};

class ClosedPolygonalChain : public PolygonalChain{
public:
    ClosedPolygonalChain(int numberOfPoints, Point *array);
    ClosedPolygonalChain(const ClosedPolygonalChain &CopyClosedPolygonalChain);
    ClosedPolygonalChain& operator=(const ClosedPolygonalChain&);
    [[nodiscard]] int getN() const override;
    ~ClosedPolygonalChain();
};

class Polygon : public ClosedPolygonalChain{
public:
    Polygon(int numberOfPoints, Point *array);
    Polygon(const Polygon &CopyPolygon);
    Polygon& operator=(const Polygon&);
    [[nodiscard]] double area() const;
    static double triangle_area(const Point& point1, const Point& point2, const Point& point3) ;
    ~Polygon();
};

class Triangle: public ClosedPolygonalChain{
public:
    Triangle(int numberOfPoints, Point *array);
    [[maybe_unused]] Triangle(const Triangle &CopyTriangle);
    Triangle& operator=(const Triangle&);
    [[nodiscard]] bool hasRightAngle() const;
    [[maybe_unused]] double area();
    ~Triangle();
};

class Trapezoid: public ClosedPolygonalChain{
public:
    Trapezoid(int numberOfPoints, Point *array);
    Trapezoid(const Trapezoid &CopyTrapezoid);
    Trapezoid& operator=(const Trapezoid&);
    [[nodiscard]] double height() const;
    [[maybe_unused]] [[nodiscard]] double area() const;
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