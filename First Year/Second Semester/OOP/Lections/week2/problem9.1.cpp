#include <iostream>

class Time{
public:
int hours;
int minutes;
Time(int h = 0, int m = 0) : hours(h), minutes(m) {}
void printTime() const {
    std::cout << (hours < 10 ? "0" : "") << hours << ":"
              << (minutes < 10 ? "0" : "") << minutes << std::endl;
}
void addHours(){
int hours;
std::cin >> hours;
    while (hours < 0 || hours > 24)
    {
        std::cin >> hours;
    }
    this->hours = hours;
}
void addMinutes(){
int minutes;    
std::cin >> minutes;
    while (minutes < 0 || minutes > 60)
    {
        std::cin >> minutes;
    }
    this->minutes = minutes;
}
void changeTime(){
int hours;
int minutes;
    std::cin >> hours;
    while (hours < 0 || hours > 24 || hours == this->hours)
    {
        std::cout << "Wrong number/same hour" << std::endl;
        std::cin >> hours;
    }
    std::cin >> minutes;
    while (minutes < 0 || minutes > 60 || minutes == this->minutes)
    {
        std::cout << "Wrong number/same minute" << std::endl;
        std::cin >> minutes;
    }
    this->hours = hours;
    this->minutes = minutes;
}
int calculateTotalMins() const{
    return hours * 60 + minutes;
}
// void addTime(int hours, int minutes){
//     addHours;
//     addMinutes;
// }
void addMinutesToTime(int minutes){
    std::cin >> minutes;
    while (minutes < 0 || minutes > 60)
    {
        std::cout << "Wrong interval" << std::endl;
        std::cin >> minutes;
    }
    this->minutes += minutes;
}
bool biggerTime(int time1, int time2){
    return (time1 < time2);
}
Time operator+(const Time &t){
    int totalMins = (hours + t.hours) * 60 + (minutes + t.minutes);
    return Time(totalMins/60, totalMins%60);
}
};

int main() {
    Time time1(2, 30);
    Time time2(12, 45);
    Time time0 = time1 + time2;

    time0.printTime();

    return 0;
}