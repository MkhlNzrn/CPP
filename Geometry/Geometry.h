#pragma once
#define MAIN_CPP_GEOMETRY_H
#define M_PI 3.14159265358979323846

#include <vector>
#include <cmath>

class Point {
private:
	long x_;
	long y_;

public:
	Point(long x, long y);

	Point();

	Point(const Point &point);

	Point &operator=(const Point &pointCopy);

	 long getX() const;

	 long getY() const;

};
//fixed remove size
class PolygonalChain {
protected:
	std::vector<Point> vec;
public:

	PolygonalChain(long size, Point array[]);

	PolygonalChain(const PolygonalChain &polyChain);

	PolygonalChain &operator=(const PolygonalChain &polygonalChainCopy);

	virtual ~PolygonalChain();

	 long getN() const;

	 Point getPoint(long position) const;

	 double lenght(long i = 0) const;

	 virtual double perimeter() const;
};

class ClosedPolygonalChain : public PolygonalChain {
public:
	ClosedPolygonalChain(long size, Point array[]);

	ClosedPolygonalChain(const ClosedPolygonalChain &other);
};

class Polygon : public ClosedPolygonalChain {
public:
	Polygon(long size, Point array[]);

	Polygon(const Polygon &other);

	 virtual double area() const;

	Polygon &operator=(const Polygon &polygonCopy);
};

class Triangle : public Polygon {
public:
	Triangle(long size, Point array[]);

	Triangle(const Triangle &other);

	Triangle &operator=(const Triangle &other);

	 bool hasRightAngle() const;
};

class Trapezoid : public Polygon {
public:
	Trapezoid(long size, Point array[]);

	Trapezoid(const Trapezoid &other);

	Trapezoid &operator=(const Trapezoid &other);

	 double height() const;
};

class RegularPolygon : public Polygon {
public:
	RegularPolygon(long size, Point array[]);

	RegularPolygon(const RegularPolygon &other);

	 double perimeter() const override;

	 double area() const override;
};