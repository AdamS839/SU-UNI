#include <iostream>
#include <cstring>

class String{
private:
    char *str;
    std::size_t capacity_;
    std::size_t size_;
public:
    String(){
        capacity_ = 0;
        size_ = 0;
    };

    ~String(){
        delete[] str;
    }

    bool empty() const{
        return this->size_ == 0;
    };
    
    void push_back(char c){
        str[size_] = c;
        ++size_;
        str[size_+1] = '\0';
    }

    bool pop_back(){
        if(size_ > 0){
            --size_;
            str[size_] = '\0';
            return true;
        }
        return false;
    }

    std::size_t size() const{
        return this->size_;
    }

    std::size_t capacity() const{
        return this->capacity_;
    }

    std::size_t find(char c) const{
        for (std::size_t i = 0; i < this->size_; ++i)
        {
            if(str[i] == c){
                return i;
            }
        }
        return -1;
    }

    std::size_t find(String const& substr) const{
        char *retval = std::strstr(str, substr.str);
        if(retval){
            return std::size_t(retval - str);
        }
        else return -1;
    }

    String slice(std::size_t left, std::size_t right){
        if(right < left){
            return String();
        }

        std::size_t length = right - left;
        char *substr = new char[length + 1];
        std::strncmp(substr, str+left, length);
        substr[length] = '\0';

        String res = substr;
        delete[] substr;
        return res;
    }

    void clear(){

    }

    void copy(String const& other){

    }

    void reverse(){

    }

    void reserve(std::size_t capacity){
        
    }

    void erase(std::size_t index, std::size_t length=1){

    }

    void swap(String& other){

    }

    char const& c_str() const{

    }

    char* data(){

    }

    String& replace(char const& oldS, char const& newS){

    }

    String& replace(String const& oldS, String const& newS){

    }
};

int main() {

    return 0;
}