#ifndef __Vehicle_HPP
#define __Vehicle_HPP
#include <iostream>
#include "Registration.h"

class Vehicle{
public:
    Registration regnum;
    char* description;
public:
    void copy(const Vehicle &other){
        description = new char[std::strlen(other.description) + 1];
        std::strcpy(description, other.description);
    }

    void clear(){
        delete[] description;
    }

    Vehicle(const char* _regnum, const char* _description) : regnum(_regnum), description(new char[std::strlen(_description) + 1]){
        std::strcpy(description, _description);
    }
    ~Vehicle(){
        clear();
    }

    Vehicle(const Vehicle &other): regnum(other.regnum){
        copy(other);
    }

    Vehicle& operator=(const Vehicle &other){
        if(this != &other){
            regnum = other.regnum;
            clear();
            copy(other);
        }
        return *this;
    }

    const Registration& getRegnum() const { return regnum; }

    const char* getDescription() const { return description; }
};

#endif