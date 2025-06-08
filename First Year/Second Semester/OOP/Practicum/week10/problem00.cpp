#include <iostream>
#include <cmath>
#include <cstring>

struct Points{
    double x, y;
};

class Shape{
private:
    char* name;
    char rgb[3];
    double perimeter = 0;
    double area = 0;
public:
    Shape(char* name, char r, char g, char b) : name(name), rgb{r, g, b} {}
    ~Shape(){ delete name; }
    virtual double Perimeter(){ std::cout << "ShapePerimeter" << std::endl; }
    virtual double Area() {std::cout << "ShapeArea" << std::endl; }
    void editName(const char* in){
        std::strcpy(this->name,in);
    }
    void editRGB(const char rgbNew[3]){
        std::strcpy(this->rgb, rgbNew);
    }
    const char *getName() const{
        return name;
    }
    const char *getrgb() const{
        return rgb;
    }
};

class Triangle : public Shape{
private:
    Points p1,p2,p3;
public:
    Triangle(char* name, char r, char g, char b, Points p1, Points p2, Points p3) : Shape(name, r, g, b), p1(p1), p2(p2), p3(p3) {}

    double distance(Points const &p1, Points const &p2){
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    }

    Points getTopLeftPoint(){
        double getX = std::min(p1.x, p2.x, p3.x);
        double getY = std::max(p1.y, p2.y, p3.y);
        return {getX, getY};
    }

    double Perimeter(){
        double a = distance(p1, p2);
        double b = distance(p2, p3);
        double c = distance(p3, p1);
        return a + b + c;
    }

    double Area(){
        double halfperim = Perimeter() / 2;
        double a = distance(p1, p2);
        double b = distance(p2, p3);
        double c = distance(p3, p1);
        return std::sqrt(halfperim * (halfperim - a) * (halfperim - b) * (halfperim - c));
    }
};

class RegularPolygon : public Shape{
private:
    int sides;
    double sideLength;
    Points center;
public:
    RegularPolygon(char* name, char r, char g, char b, int sides, double length, Points _center) : Shape(name, r, g, b), sides(sides), sideLength(length), center(_center) {}

    double Perimeter(){
        return sideLength * sides;
    }

    double Area(){
        return sides * sideLength * (1/(2*std::tan(180/sides))); // dano da raboti tangensa
    }

    double apothem(){
        return (1/(2*std::tan(180/sides)));
    }

    Points topleftPoint(){
        return {center.x - apothem(), center.y + apothem()};
    }

};

int main() {

    

    return 0;
}