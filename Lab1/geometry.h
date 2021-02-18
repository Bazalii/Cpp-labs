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
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
};

class PolygonalChain{
protected:
    int NumberOfPoints = 0;
    Point *Array{};
public:
    PolygonalChain(int numberOfPoints, Point *array); // затемнение?}
    PolygonalChain(const PolygonalChain &CopyPolygonalChain);
    [[nodiscard]] double perimeter() const;

    [[nodiscard]] virtual int getN() const;
    [[maybe_unused]] [[nodiscard]] Point * getArray() const;
    [[nodiscard]] Point getPoint(int number) const;
};

class ClosedPolygonalChain : public PolygonalChain{
public:
    ClosedPolygonalChain(int numberOfPoints, Point *array);
    ClosedPolygonalChain(const ClosedPolygonalChain &CopyClosedPolygonalChain);
    [[nodiscard]] int getN() const override;
};

class Polygon : public ClosedPolygonalChain{
public:
    Polygon(int numberOfPoints, Point *array);
    Polygon(const Polygon &CopyPolygon);
    [[nodiscard]] double area() const;
    static double triangle_area(const Point& point1, const Point& point2, const Point& point3) ;
};

class Triangle: public ClosedPolygonalChain{
public:
    Triangle(int numberOfPoints, Point *array);
    [[maybe_unused]] Triangle(const Triangle &CopyTriangle);
    [[nodiscard]] bool hasRightAngle() const;
    [[maybe_unused]] double area();
};

class Trapezoid: public ClosedPolygonalChain{
public:
    Trapezoid(int numberOfPoints, Point *array);
    Trapezoid(const Trapezoid &CopyTrapezoid);
    [[nodiscard]] double height() const;
    [[maybe_unused]] [[nodiscard]] double area() const;
};

class RegularPolygon: public Polygon{
public:
    RegularPolygon(int numberOfPoints, Point *array);
    RegularPolygon(const RegularPolygon &CopyRegularPolygon);
};

#endif