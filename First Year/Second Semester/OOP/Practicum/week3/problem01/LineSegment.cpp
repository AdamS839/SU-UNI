#include <iostream>
#include <cmath>
#include "LineSegment.hpp"

void LineSegment::setStartingPoint(Point const& point){
    this->s = point;
}

void LineSegment::setEndpoint(Point const& point){
    this->e = point;
}

Point const& LineSegment::getStartingPoint() const{
    return this->s;
}

Point const& LineSegment::getEndpoint() const{
    return this->e;
}

double LineSegment::length() const{
    return sqrt((s.x - e.x)*(s.x - e.x) + (s.y - e.y) * (s.y - e.y));
}

double LineSegment::slope() const{
    return (e.y - s.y)/(e.x - s.x);
}

Point LineSegment::midpoint() const{
    // Point m;
    // m.x = (this->s.x + this->e.x)/2;
    // m.y = (this->s.y + this->e.y)/2;
    // return m;
    return {(s.x + e.x)/2, (s.y + e.y)/2};
}

Point LineSegment::toVector() const{
    // Point v;
    // v.x = this->e.x - this->s.x;
    // v.y = this->e.y - this->s.y;
    // return v;
    return {(e.x - s.x), (e.y - s.y)};
}

bool LineSegment::containsPoint(Point const& point) const{
    if((point.x - s.x) * (e.y - s.y) != (point.y - s.y) * (e.x - s.x)) return false;
    return(point.x >= std::min(s.x, e.x) && point.x <= std::max(s.x, e.x) && point.y >= std::min(s.y, e.y) && point.y <= std::max(s.y, e.y));
}

void LineSegment::translate(double dx, double dy) {
    s.x += dx;
    e.x += dx;
    s.y += dy;
    e.y += dy;
}