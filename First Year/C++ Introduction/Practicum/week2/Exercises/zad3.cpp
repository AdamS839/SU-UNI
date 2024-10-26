#include <iostream>
#include <cmath>

int main() {

    //Use Pythagoras numbers for easy checking

    double teachRadius, roomX, roomY;

    std::cin >> teachRadius >> roomX >> roomY;

    double distanceToRoom = sqrt(pow(roomX, 2) + pow(roomY, 2));
    
    if (distanceToRoom <= teachRadius)
    {
        std::cout<< "Don't do it!" << std::endl;
    }
    else std::cout<< "Let's do it!" << std::endl;

    
}