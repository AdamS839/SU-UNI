#ifndef __Exception_H
#define __Exception_H
#include <iostream>

class Exception{
public:
    virtual char const* what() const noexcept = 0;
};

class RuntimeError : public Exception{
public:
    RuntimeError(const char *s) : s(s) {}
    virtual char const* what() const noexcept{
        return s;
    }
private:
const char* s;
};

class OutOfRange : public Exception{
private:
const char* m;
public:
    OutOfRange(const char *_m) : m(_m) {}
    virtual char const* what() const noexcept{
        return m;
    }
};

class BadCast : public Exception{

};

// problem 2
/*
template<class T>
class Optional{
T data
bool hasData
public:
}
*/

void foo(){
    throw 1;
}

#endif