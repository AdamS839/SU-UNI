#ifndef __Shape_HPP_
#define __Shape_HPP_
#include <iostream> 
#include <cmath>
#include <cstring>

struct Points{
double x, y;
};

class Shape{
char *name;
char rgb[3];
public:

Shape() : name(nullptr){
    rgb[0] = rgb[1] = rgb[2] = 255;
}

Shape(const char* input) : name(new char[std::strlen(input) + 1]), rgb({255, 255, 255}){
    std::strcpy(name, input);
}

~Shape() { delete name; }

Shape(const Shape &other){
    name = new char[std::strlen(other.name) + 1];
    strcpy(name, other.name);
    rgb[0] = other.rgb[0];
    rgb[1] = other.rgb[1];
    rgb[2] = other.rgb[2];
}

Shape &operator=(const Shape &other){
    if(this != &other){
        delete[] name;
        rgb[0] = other.rgb[0];
        rgb[1] = other.rgb[1];
        rgb[2] = other.rgb[2];
        name = new char[std::strlen(other.name) + 1];
        std::strcpy(name, other.name);
    }
    return *this;
}
virtual double perimeter() const = 0;
virtual double area() const = 0;
virtual Points findTopLeftRectCorner() = 0;
virtual void print(std::ostream &os) const{
os << name << rgb[0] << "-" << rgb[1] << "-" << rgb[2] << " ";
}
virtual Shape* clone() = 0;

// why friend??
friend std::ostream &operator<<(std::ostream &os, const Shape &shape){
    shape.print(os);
    return os;
}
};

class Triangle : public Shape{
Points p1, p2, p3;
public:

double getlength(const Points &p1,const Points &p2) const{
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double perimeter()const override{
    return getlength(p1, p2) + getlength(p2, p3) + getlength(p3, p1);
}

double area() const override{
    return std::sqrt((perimeter()/2*(perimeter()/2 - getlength(p1,p2))*(perimeter()/2 - getlength(p2, p3))*(perimeter()/2 - getlength(p3, p1))));
}

Points findTopLeftRectCorner(){
    return {std::min(p1.x,p2.x,p3.x), std::max(p1.y,p2.y,p3.y)};
}

void print(std::ostream &os) const override{
    Shape::print(os);
    os << p1.x << " " << p1.y << " : " << p2.x << " " << p2.y << " : " << p3.x << " " << p3.y << "\n";
}
};

class RegularPolygon : public Shape{
int sideCount;
double sideLength;
Points center;
public:

double perimeter() const override{
    return sideCount * sideLength;
}

double area() const override{
    //apothem = (sideLength/2*std::tan(180/sideCount)
    return ((sideLength/(2*std::tan(180/sideCount))) * perimeter()/2)/2;
}

Points findTopLeftRectCorner(){
    return {center.x - (sideLength/(2*std::tan(180/sideCount))), center.y + (sideLength/(2*std::tan(180/sideCount)))};
}

void print(std::ostream &os) const override{
    Shape::print(os);
    os << "Side count" << sideCount << ", " << "Side length" << sideLength << ", Center point: " << center.x << "," << center.y;
}
};

class Group : public Shape{
Shape** parts;
int capacity;
int size;
public:

Shape* clone() override{
    return new Group(*this);
}

Group(int cap) : parts(new Shape*[cap]), capacity(cap), size(0) {}

~Group(){
    for (int i = 0; i < capacity; ++i)
    {
    delete parts[i];
    }
    delete[] parts;
}
Group(const Group &other) : size(other.size), capacity(other.capacity), parts(new Shape*[other.capacity]), Shape(other) {
    for (int i = 0; i < other.size; ++i)
    {
        parts[i] = other.parts[i]->clone();
    }
}

double area() const override {
    double area = 0;
    for (int i = 0; i < size; ++i)
    {
        area += parts[i]->area();
    }
    return area;
}

double perimeter() const override{
    double sum = 0;
    for (int i = 0; i < size; ++i)
    {
        sum += parts[i]->perimeter();
    }
    return sum;
}
Points findTopLeftRectCorner() {
    if(size == 0 ) return {0,0};
    Points topLeft = parts[0]->findTopLeftRectCorner();
    for (int i = 0; i < size; ++i)
    {
        Points p = parts[i]->findTopLeftRectCorner();
        if(p.x < topLeft.x) topLeft.x = p.x;
        if(p.y > topLeft.y) topLeft.y = p.y;
    }
    return topLeft;
}

void print(std::ostream &os) const override{
    Shape::print(os);
    os << "Group size: " << size << "\n";
    for (int i = 0; i < size; ++i)
    {
        parts[i]->print(os);
        os << "\n";
    }
}

};

#endif