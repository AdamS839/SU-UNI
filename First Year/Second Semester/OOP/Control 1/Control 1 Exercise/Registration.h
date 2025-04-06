#ifndef __Registration_HPP
#define __Registration_HPP
#include <iostream>
#include <cstring>

class Registration{
private:
    char rnumber[9];
    bool isValid(const char* str){
        std::size_t len = std::strlen(str);
        if(len != 8 && len != 7) return false;
        int i = 0;

        // WORK ONLY FOR this format (d - digit, l - letter) : llddddll

        // while (i < len){
        //     if((i < 2 || i >= 6) && !std::isalpha(str[i])) return false;
        //     if(i >= 2 && i < 6 && !std::isdigit(str[i])) return false;
        //     ++i;
        // }

        while (i < len) {
            if ((i == 0 || (len == 8 && i == 1) || i >= len - 2) && !std::isalpha(str[i])) return false; 
            if ((i >= (len == 8 ? 2 : 1) && i < len - 2) && !std::isdigit(str[i])) return false;
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

#endif