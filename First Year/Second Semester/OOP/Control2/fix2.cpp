#include <iostream>
#include <vector>

template<class T>
class VectorStream{
std::vector<T> data;
std::vector<T> copy;
public:
    VectorStream(std::vector<T> _d, std::vector<T> _c) : data(_d), copy(_c) {}

    std::istream &operator>>(std::istream &is){
        if(data.empty()) return is;
        for(T &v: data){
            is >> v;
        }
        return is;
    }

    void reset(){
        copy = data;
    }

    void peek(){
        
    }
};