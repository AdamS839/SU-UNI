#include <iostream>
#include "LineSegment.hpp"

int main() {

    LineSegment segment;
    Point p1 = {1,2};
    Point p2 = {9,6};

    Point containP = {1,5};

    segment.setStartingPoint(p1);
    segment.setEndpoint(p2);

    std::cout << "Segment start point - end point is: " << '(' << segment.getStartingPoint().x << ',' << segment.getStartingPoint().y << ')' << 
    " - " << '(' << segment.getEndpoint().x << ',' << segment.getEndpoint().y << ')' << std::endl;

    std::cout << "Segment length is: " << segment.length() << std::endl;

    std::cout << "Segment slope is: " << segment.slope() << std::endl;

    std::cout << "Middle point on segment is (x,y): " << '(' <<  segment.midpoint().x << ',' << segment.midpoint().y << ')' << std::endl;

    std::cout << "Segment to vector is (x,y): " << '(' <<  segment.toVector().x << ',' << segment.toVector().y << ')' << std::endl;

    std::cout << std::boolalpha << segment.containsPoint(containP) << std::endl;

    segment.translate(-2.3,10.7);

    return 0;
}