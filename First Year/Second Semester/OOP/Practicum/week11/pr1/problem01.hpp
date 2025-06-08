#ifndef __Pointers_HPP
#define __Pointers_HPP
#include <iostream>

class SharePointer{
int *ptr;
int *refCount;

public:

    SharePointer() : ptr(nullptr), refCount(new int(0)) {}

    SharePointer(int *p) : ptr(p), refCount(new int(1)) {
        if(!ptr){
            *refCount = 0;
        }
    }

    SharePointer(const WeakPointer &wptr) : ptr(wptr.ptr), refCount(wptr.refCount) {
        if (isValid()) {
                ++(*refCount);
            }
        }

    SharePointer(const SharePointer &other) : ptr(other.ptr), refCount(other.refCount){
        ++(*refCount);
    }

    ~SharePointer(){
        if(--(*refCount) == 0){
            delete ptr;
            delete refCount;
        }
    }

    SharePointer& operator=(const SharePointer& other) {
        if (this != &other) {
            if (--(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            ptr = other.ptr;
            refCount = other.refCount;
            ++(*refCount);
        }
        return *this;
    }
    

    bool isValid() const{
        return ptr != nullptr;
    }

    int& operator*(){
        return *ptr;
    }

    const int &operator*() const{
        return *ptr;
    }

    int *getRawPtr(){
        return ptr;
    }

    const int *getRawPtr() const{
        return ptr;
    }

    void swap(SharePointer &other){
        std::swap(ptr, other.ptr);
        std::swap(refCount, other.refCount);
    }

    // Check for nullptr ?
    bool equivalance(const SharePointer &other) const{
        return *ptr == *other.ptr;
    }

    bool equal(const SharePointer &other) const{
        return ptr == other.ptr;
    }
    
    void reset(){
        if(refCount){
            --(*refCount);
            if(--(*refCount) == 0){
                delete ptr;
                delete refCount;
            }
        }
        ptr = nullptr;
        refCount = nullptr;
    }

    // bool operator==(const SharePointer &other) const{
    //     return ptr == other.ptr;
    // }

    // bool operator!=(const SharePointer &other) const{
    //     return !(*this == other);
    // }

    friend std::ostream &operator<<(std::ostream &os, const SharePointer &sptr){
        if(sptr.ptr){
            os << *sptr.ptr;
        }
        else{
            os << "null";
        }
        return os;
    }

    friend class WeakPointer;
};

class WeakPointer{
int *ptr;
int *refCount;
int *weakCount;
public:
    WeakPointer() : ptr(nullptr), refCount(nullptr), weakCount(nullptr) {}

    WeakPointer(SharePointer &sptr) : ptr(sptr.getRawPtr()), refCount(sptr.refCount), weakCount(new int(1)) {}
    
    WeakPointer(const WeakPointer &other) : ptr(other.ptr), refCount(other.refCount), weakCount(other.weakCount) {
        if(weakCount){
            ++(*weakCount);
        }
    }

    ~WeakPointer(){
        if(weakCount){
            --(*weakCount);
            if(*weakCount == 0){
                delete weakCount;
            }
        }
    }

    WeakPointer &operator=(const WeakPointer &other){
        if(this != &other){
            if(weakCount && --(*weakCount) == 0){
                delete weakCount;
            }
            ptr = other.ptr;
            refCount = other.refCount;
            weakCount = other.weakCount;

            if(weakCount){
                ++(*weakCount);
            }
        }
        return *this;
    }

    bool isValid() const{
        return refCount && *refCount > 0;
    }

    bool isExpired() const{
        return !isValid();
    }

    SharePointer lock() const{
        if(isValid()){
            return SharePointer(*this);
        }
        return SharePointer();
    }

    int &operator*() {
        if(isValid()){
            return *ptr;
        }
        throw std::invalid_argument("Invalid weak ptr access");
    }

    int &operator*() const{
        if(isValid()){
            return *ptr;
        }
        throw std::invalid_argument("Invalid weak ptr accesss");
    }

    int *getRawPtr(){
        return ptr;
    }

    int *getRawPtr() const{
        return ptr;
    }

    void swap(WeakPointer &other){
        std::swap(ptr, other.ptr);
        std::swap(refCount, other.refCount);
        std::swap(weakCount, other.weakCount);
    }


    // Check for nullptr ?
    bool equivalance(const WeakPointer &other) const{
        return *ptr == *other.ptr;
    }

    bool equal(const WeakPointer &other) const{
        return ptr == other.ptr;
    }

    // bool operator==(const WeakPointer &other) const{
    //     return ptr == other.ptr;
    // }

    // bool operator!=(const WeakPointer &other) const{
    //     return !(*this == other);
    // }

    friend std::ostream &operator<<(std::ostream &os, const WeakPointer &wptr){
        if(wptr.isValid()){
            os << *wptr.ptr;
        }
        else {
            os << "null";
        }
        return os;
    }

    friend class SharePointer;
};

#endif