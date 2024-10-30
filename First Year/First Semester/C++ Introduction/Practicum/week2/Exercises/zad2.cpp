#include <iostream>

int main() {

    int dirStartHour, dirStartMin, dirEndHour, dirEndMin;
    int zam1StartHour, zam1StartMin, zam1EndHour, zam1EndMin;
    int zam2StartHour, zam2StartMin, zam2EndHour, zam2EndMin;

    std::cin >> dirStartHour >> dirStartMin >> dirEndHour >> dirEndMin;
    std::cin >> zam1StartHour >> zam1StartMin >> zam1EndHour >> zam1EndMin;
    std::cin >> zam2StartHour >> zam2StartMin >> zam2EndHour >> zam2EndMin;

    int currentHour, currentMin;
    std::cin >> currentHour >> currentMin;

    int dirStartMins = dirStartHour*60 + dirStartMin;
    int dirEndMins = dirEndHour*60 + dirEndMin;

    int zam1StartMins = zam1StartHour*60 + zam1StartMin;
    int zam1EndMins = zam1EndHour*60 + zam1EndMin;

    int zam2StartMins = zam2StartHour*60 + zam2StartMin;
    int zam2EndMins = zam2EndHour*60 + zam2EndMin;

    int totalCurrentMins = currentHour*60 + currentMin;

    if ((dirStartMins <= totalCurrentMins && dirEndMins >= totalCurrentMins) ||
        (zam1StartMins <= totalCurrentMins && zam1EndMins >= totalCurrentMins) ||
        (zam2StartMins <= totalCurrentMins && zam2EndMins >= totalCurrentMins))
    {
        std::cout <<"They will catch you!" << std::endl;
    }
    else std::cout << "Let's do it!" << std::endl;
    
    /* Example hours for checking:
    dir    10:30 - 11:00
    zam1   11:40 - 12:30 
    zam2   15:20 - 16:00
    */


}