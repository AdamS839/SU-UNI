#include <iostream>
#include <cmath>

int main() {

    double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
    std::cout << "Add meters for each room (5 rows for x/y meters)\n";
    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    std::cin >> x3 >> y3;
    std::cin >> x4 >> y4;
    std::cin >> x5 >> y5;
    double RoomSq1 = x1 * y1;
    double RoomSq2 = x2 * y2;
    double RoomSq3 = x3 * y3;
    double RoomSq4 = x4 * y3;
    double RoomSq5 = x5 * y3;

    double AllRoomSq = RoomSq1 + RoomSq2 + RoomSq3 + RoomSq4 + RoomSq5;

    double LaminatePrice, LaminateSquarePerPacket;
    double PriceForSqMeter;

    std::cout << "Add price for laminate per packet: ";
    std::cin >> LaminatePrice;
    std::cout << "How much square meters is in the laminate packet: ";
    std::cin >> LaminateSquarePerPacket;
    std::cout << "Add price for placing laminate from the worker in square meters: ";
    std::cin >> PriceForSqMeter;

    double LaminateCount = ceil(AllRoomSq / LaminateSquarePerPacket);
    double AllRepairPrice = AllRoomSq * PriceForSqMeter + LaminateCount*LaminatePrice;

    std::cout<< "Laminate packets needed: " << LaminateCount << std::endl;
    std::cout<< "Reparing price for all rooms is: " << AllRepairPrice << std::endl;

}