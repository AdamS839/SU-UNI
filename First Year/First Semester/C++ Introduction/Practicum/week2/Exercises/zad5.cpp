#include <iostream>
#include <cmath>
#include <algorithm>

int main() {

    // Pythagoras Numbers for easy checking /3,4,5/ /5,12,13/ /8,15,17/

    double zeleX, zeleY;

    double room1X, room1Y;
    double room2X, room2Y;
    double room3X, room3Y;

    std::cin >> zeleX >> zeleY;
    std::cin >> room1X >> room1Y;
    std::cin >> room2X >> room2Y;
    std::cin >> room3X >> room3Y;

    double distanceMax, distanceMin;

    double distTo1 = sqrt(pow(room1X - zeleX, 2)+ pow(room1Y - zeleY, 2));
    double distTo2 = sqrt(pow(room2X - zeleX, 2)+ pow(room2Y - zeleY, 2));
    double distTo3 = sqrt(pow(room3X - zeleX, 2)+ pow(room3Y - zeleY, 2));


    // I 
    /*
    distanceMax = std::max(std::max(distTo1, distTo2), distTo3);
    distanceMin = std::min(std::min(distTo1, distTo2), distTo3);
    */

    // II
    distanceMax = distanceMin = distTo1;

    if (distTo2 > distanceMax) distanceMax = distTo2;
    if (distTo3 > distanceMax) distanceMax = distTo3;

    if (distTo2 < distanceMin) distanceMin = distTo2;
    if (distTo3 < distanceMin) distanceMin = distTo3;

    std::cout<< "Max distance is " << distanceMax << std::endl;
    std::cout<< "Min distance is " << distanceMin << std::endl;
}