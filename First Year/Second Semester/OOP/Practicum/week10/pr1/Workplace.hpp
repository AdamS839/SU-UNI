#ifndef __Workplace_HPP
#define __Workplace_HPP
#pragma once
#include <iostream>
#include <cstring>
#include <cmath>

class Employee{
char *name;
int id;
double salary;
char *specialty;

static int nextId;
public:
    Employee() : id(nextId++) {}

    Employee(const char *_name, double _salary,const char *_spec) : id(nextId++), name(new char[std::strlen(_name) + 1]), specialty(new char[std::strlen(_spec) + 1]), salary(std::abs(_salary)) {
        std::strcpy(name, _name);
        std::strcpy(specialty, _spec);
    }

    ~Employee() {
        delete[] name;
        delete[] specialty;
    }

    Employee(const Employee &other) : id(other.id), name(new char[std::strlen(other.name) + 1]), specialty(new char[std::strlen(other.name) + 1]), salary(other.salary) {
        std::strcpy(name, other.name);
        std::strcpy(specialty, other.specialty);
    } 

    Employee &operator=(const Employee &other){
        if(this != &other){
            delete[] name;
            delete[] specialty;

            name = new char[std::strlen(other.name) + 1];
            std::strcpy(name, other.name);

            specialty = new char[std::strlen(other.specialty) + 1];
            std::strcpy(specialty, other.specialty);

            salary = other.salary;
            id = other.id;
        }
        return *this;
    }

    int getId() const{
        return id;
    }

    const char *getName() const{
        return name;
    }

    const char *getSpec() const{
        return specialty;
    }

    double getSalary() const{
        return salary;
    }

    void setName(const char *newname){
        delete[] name;
        name = new char[std::strlen(newname) + 1];
        std::strcpy(name, newname);
    }

    void setSpec(const char *newspec){
        delete[] specialty;
        specialty = new char[std::strlen(newspec) + 1];
        std::strcpy(specialty, newspec);
    }

    void setSalary(double newsal){
        salary = std::abs(newsal);
    }

    friend std::ostream &operator<<(std::ostream &os, const Employee &em){
        os << "ID: " << em.id << "\n";
        os << "Name: " << em.getName() << "\n";
        os << "Job: " << em.getSpec() << "\n";
        os << "Salary: " << em.getSalary() << "\n";
        return os;
    }

    friend class EmployeeTeam;
};

int Employee::nextId = 1;

class EmployeeTeam{
Employee** team;
std::size_t size;
std::size_t capacity;

void resize(){
    if (size == capacity){
        std::size_t newCap = capacity + 1;
        Employee** temp = new Employee*[newCap];
        for (std::size_t i = 0; i < size; ++i)
        {
            temp[i] = new Employee(*this->team[i]);
        }
        for (std::size_t i = 0; i < size; ++i)
        {
            delete team[i];
        }
        delete[] team;

        this->team = temp;
        capacity = newCap;
    }
}

public:

class Iterator{
Employee** ptr;
public:
    Iterator(Employee **start) : ptr(start) {}
    
    Employee &operator*(){
        return **ptr;
    }

    Employee &operator*() const{
        return **ptr;
    }

    Iterator &operator++(){
        ++ptr;
        return *this;
    }

    Iterator operator++(int){
        Iterator it = *this;
        ++(*this);
        return it;
    }

    Iterator operator--(){
        --ptr;
        return *this;
    }

    bool operator==(const Iterator &other) const{
        return ptr == other.ptr;
    }

    bool operator!=(const Iterator &other) const{
        return !(*this == other);
    }
};

class Reverse_Iterator{
Employee** r_ptr;
public:
    Reverse_Iterator(Employee **rstart) : r_ptr(rstart) {}

    Employee &operator*(){
        return **r_ptr;
    }

    Employee &operator*() const{
        return **r_ptr;
    }

    Reverse_Iterator operator++(){
        --r_ptr;
        return *this;
    }

    Reverse_Iterator operator++(int){
        Reverse_Iterator it = *this;
        ++(*this);
        return it;
    }

    Reverse_Iterator operator--(){
        ++r_ptr;
        return *this;
    }

    bool operator==(const Reverse_Iterator &other) const{
        return r_ptr == other.r_ptr;
    }

    bool operator!=(const Reverse_Iterator &other) const{
        return !(*this == other);
    }
};

using r_iterator = Reverse_Iterator;
using iterator = Iterator;

// r_iterator rbegin() {return (team + size - 1); }
// r_iterator rend() {return nullptr; } // return team -

// iterator begin() {return team; }
// iterator end() {return nullptr; } // return team + size;

r_iterator rbegin() const { return r_iterator(team + size - 1); }
r_iterator rend() const { return r_iterator(team - 1); }

iterator begin() const { return iterator(team); }
iterator end() const { return iterator(team + size); }

EmployeeTeam(int _capacity) : team(new Employee*[_capacity]), size(0), capacity(_capacity) {}

EmployeeTeam() : team(new Employee*[0]), size(0), capacity(0) {}

~EmployeeTeam(){
    for (std::size_t i = 0;i < size;++i)
    {
        delete team[i];
    }
    delete[] team;
}

EmployeeTeam(const EmployeeTeam &other) : size(other.size), capacity(other.capacity), team(new Employee*[other.capacity]) {
    for (std::size_t i = 0; i < other.size; ++i)
    {
        this->team[i] = new Employee(*other.team[i]);
    }
}

EmployeeTeam &operator=(const EmployeeTeam &other){
    if(this != &other){
        for (std::size_t i = 0; i < size; ++i)
        {
            delete team[i];
        }
        delete[] team;
        size = other.size;
        capacity = other.capacity;
        team = new Employee*[capacity];
        for (std::size_t i = 0; i < size; ++i){
            team[i] = new Employee(*other.team[i]);
        }
    }
    return *this;
}

void push_back(const Employee &em){
    if(size == capacity){
        resize();
    }
    team[size++] = new Employee(em);
}

void print(std::ostream &os, const EmployeeTeam &team){
    for (const Employee &em : team){
        os << em;
        os << "\n";
    }
}


};


#endif