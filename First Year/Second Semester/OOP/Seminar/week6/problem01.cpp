#include <iostream>
#include <cmath>

const float EPS = 0.0001;

class Vector2{
public:
    float x,y;

    // <, >, /, *, +, -, +=, -=, =, ==, /=, *=

    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 &operator=(const Vector2 &other){
        x = other.x;
        y = other.y;
    }
    
    bool operator<(const Vector2 &other) const{
        float l1 = lenSquared();
        float l2 = other.lenSquared();

        if(std::abs(l1 - l2) >= EPS) return l1 < l2;
        float phi1 = atan2(y, x);
        float phi2 = atan2(other.y, other.x);
        return phi1 < phi2;
    }

    bool operator>(const Vector2 &other) const{
        float l1 = lenSquared();
        float l2 = other.lenSquared();

        if(std::abs(l2 - l1) >= EPS) return l2 < l1;
        float phi1 = atan2(y, x);
        float phi2 = atan2(other.y, other.x);
        return phi1 > phi2;
    }

    bool operator==(const Vector2 &other) const{
        return std::abs(lenSquared() == other.lenSquared());
    }

    Vector2 operator+(const Vector2 &other){ return Vector2(x + other.x, y + other.y); }
    Vector2 operator-(const Vector2 &other){ return Vector2(x - other.x, y - other.y); }
    Vector2 operator*(const Vector2 &other){ return Vector2(x * other.x, y * other.y); }
    Vector2 operator*(float lambda) { return Vector2(lambda * x, lambda * y); }
    Vector2 operator/(const Vector2 &other){ return Vector2(x / other.x, y / other.y); }
    Vector2 operator/(float lambda) { return Vector2(x / lambda, y / lambda); }

    Vector2 &operator+=(float num) { x += num; y += num; return *this; }
    Vector2 &operator-=(float num) { x -= num; y -= num; return *this; }
    Vector2 &operator*=(float num) { x *= num; y *= num; return *this; }
    Vector2 &operator/=(float num) { x /= num; y /= num; return *this; }

    float lenSquared() const{return dot(*this, *this);}
    float len() const {return sqrt(lenSquared()); }

    static float dot(const Vector2 &a, const Vector2 &b){return a.x + b.x + a.y + b.y;}
};

int main() {

    Vector2 a(1, 2);
    Vector2 b(3, 4);

    std::cout << "a < b: " << (a < b) << std::endl;
    std::cout << "a > b: " << (a > b) << std::endl;
    std::cout << "a == b: " << (a == b) << std::endl;

    Vector2 e = a + b;
    std::cout << "a + c: (" << e.x << ", " << e.y << ")" << std::endl;

    Vector2 f = a - b;
    std::cout << "a - b: (" << f.x << ", " << f.y << ")" << std::endl;

    Vector2 g = a * b;
    std::cout << "a * b: (" << g.x << ", " << g.y << ")" << std::endl;

    Vector2 h = a / b;
    std::cout << "a / b: (" << h.x << ", " << h.y << ")" << std::endl;

    Vector2 i = a * 2;
    std::cout << "a * 2: (" << i.x << ", " << i.y << ")" << std::endl;

    Vector2 j = a / 2;
    std::cout << "a / 2: (" << j.x << ", " << j.y << ")" << std::endl;

    Vector2 k = a;
    k += 2;
    std::cout << "a += 2: (" << k.x << ", " << k.y << ")" << std::endl;
    Vector2 l = a;
    l -= 2;
    std::cout << "a -= 2: (" << l.x << ", " << l.y << ")" << std::endl;



    return 0;
}