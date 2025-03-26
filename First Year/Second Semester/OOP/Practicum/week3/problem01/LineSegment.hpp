#ifndef __LineSegment_HPP
#define __LineSegment_HPP

struct Point
{
    double x, y;
};

class LineSegment{
public:
void setStartingPoint(Point const&);
void setEndpoint(Point const&);
Point const& getStartingPoint() const;
Point const& getEndpoint() const;
double length() const;
double slope() const;
Point midpoint() const;
Point toVector() const;
bool containsPoint(Point const&) const;
void translate(double dx, double dy);
private:
Point s;
Point e;
};

#endif