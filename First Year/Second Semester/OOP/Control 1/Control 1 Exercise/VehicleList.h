#include "Vehicle.h"

class VehicleList{
private:
    // **
    Vehicle** vehicles;
    std::size_t currentsize;
    std::size_t maxcapacity;
public:

    void copy(const VehicleList &other){
        vehicles = new Vehicle*[maxcapacity];
        for (std::size_t i = 0; i < currentsize; ++i){
            vehicles[i] = new Vehicle(*other.vehicles[i]);
        }
    }

    void clear(){
        for (std::size_t i = 0; i < currentsize; ++i){
            delete vehicles[i];
        }
        delete[] vehicles;
    }

    VehicleList(std::size_t _capacity) : maxcapacity(_capacity), currentsize(0){
        vehicles = new Vehicle*[_capacity]();
    }

    ~VehicleList(){
        clear();
    }

    VehicleList(const VehicleList &other) : maxcapacity(other.maxcapacity), currentsize(other.currentsize){
        copy(other);
    }

    VehicleList& operator=(const VehicleList &other){
        if(this != &other){
            clear();
            copy(other);
        }
        return *this;
    }

    void insert(const char* regnum, const char* description){
        if(currentsize >= maxcapacity) throw std::invalid_argument("Size bigger than capacity");
        for (std::size_t i = 0; i < currentsize; ++i){
            if(vehicles[i]->getRegnum() == regnum){
                throw std::invalid_argument("Duplicate regnum");
            }
        }
        vehicles[currentsize] = new Vehicle(regnum, description);
        ++currentsize;
    }

    const Vehicle& at(size_t index) const{
        if(index >= currentsize) throw std::invalid_argument("Invalid index");
        return *vehicles[index];
    }

    const Vehicle& operator[](size_t pos) const{
        return *vehicles[pos];
    }

    bool empty() const{
        return currentsize == 0;
    }

    std::size_t capacity() const{
        return maxcapacity;
    }

    std::size_t size() const{
        return currentsize;
    }

    const Vehicle* find(const Registration& regnum) const{
        for (std::size_t i = 0; i < currentsize; ++i){
            if(vehicles[i]->getRegnum() == regnum) return vehicles[i];
        }
        return nullptr;
    }
};