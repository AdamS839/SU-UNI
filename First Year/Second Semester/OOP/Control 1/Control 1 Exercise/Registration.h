#include <iostream>
#include <cstring>

class Registration{
private:
    char rnumber[9];
    bool isValid(const char* str){
        std::size_t len = std::strlen(str);
        if(len != 8) return false;
        int i = 0;
        while (i < 8){
            if((i < 2 || i >= 6) && !std::isalpha(str[i])) return false;
            if(i >= 2 && i < 6 && !std::isdigit(str[i])) return false;
            ++i;
        }
        return true;
    }
public:

    Registration(const char* str){
        if(!isValid(str)) throw std::invalid_argument("Not valid number");
        std::strcpy(rnumber, str);
    };

    Registration &operator=(const char* other){
        if(!isValid(other)) throw std::invalid_argument("Not valid number");
        if(std::strcmp(rnumber, other) == 0) return *this;
        std::strcpy(rnumber, other);
        return *this;
    }
    
    bool operator==(const Registration &rhs) const{
        return std::strcmp(rnumber, rhs.rnumber) == 0;
    }

    const char* toString() const{
        return rnumber;
    }
};