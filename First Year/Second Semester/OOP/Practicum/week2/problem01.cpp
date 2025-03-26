#include <iostream>
#include <limits>


struct Points{
    double x, y;
};

template<class T>
void swap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

int main(){
    int a = 10;
    int b = 12;
    swap<int>(a,b);
    std::cout << a << ' ' << b << std::endl;

    Points p1{4.5,2.5};
    Points p2{9.8,12.4};
    swap<Points>(p1,p2);

    std::cout << p1.x << ' ' << p1.y << std::endl;
    std::cout << p2.x << ' ' << p2.y << std::endl;
    
    return 0;
}