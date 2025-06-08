#include <iostream>
#include <cstring>
#include <cassert>
#include <ostream>

class Word{

    std::size_t size;
    std::size_t capacity;
    char *content;
public:

    Word() : capacity(4), size(0), content(new char[4]){}

    Word(const char *content) : capacity(std::strlen(content)), size(capacity), content(new char[capacity]) {
		for (std::size_t i = 0; i < size; ++i) {
			this->content[i] = content[i];
		}
	}


    ~Word(){ delete[] content;}

    Word(const Word &other){
        copy(other);
    }

    Word &operator=(const Word &other){
        if(this != &other){
            delete[] content;
            copy(other);
        }
        return *this;
    }

    Word operator~(){
        Word rev(*this);
        for (std::size_t i = 0; i < size / 2; ++i){
            std::swap(rev.content[i], rev.content[size - 1 - i]);
        }
        return rev;
    }

    Word &operator+=(const Word &other){
        if(size + other.size > capacity){
            std::size_t newCap = capacity;
            while (size + other.size > newCap)
				newCap *= 2;
			resize(newCap);
        }
        for (std::size_t i = 0; i < other.size; ++i){
            content[size++] = other.content[i];
        }
        return *this;
    }

    
    Word operator+(const Word &other){
        Word add(*this);
        add += other;
        return add;
    }

    Word operator<<(int n){
        assert(n >= 0);
        Word res(*this);
        for (int i = 0; i < n; ++i)
        {
            res.shiftLeft();
        }
        return res;
    }

private:
    void resize(std::size_t newCap){
        assert(newCap > size);
        char *newChar = new char[newCap];
        for (std::size_t i = 0; i < size; ++i){
            newChar[i] = content[i];
        }
        delete[] content;
        content = newChar;
        capacity = newCap;
    }

    void copy(const Word &other){
        content = new char[other.capacity];
        for (std::size_t i = 0; i < other.size; ++i){
            content[i] = other.content[i];
        }
        capacity = other.capacity;
        size = other.size;
    }

    void shiftLeft(){
        char first = content[0];
        for (std::size_t i = 0; i < size - 1; ++i){
            content[i] = content[i + 1];
        }
        content[size - 1] = first;
    }

    friend std::ostream &operator<<(std::ostream &out, const Word &w);

};


std::ostream &operator<<(std::ostream &out, const Word &w) {
	for (std::size_t i = 0; i < w.size; ++i) {
		out << w.content[i];
	}
	return out;
}

int main() {
    
    // Word w("hello");
    // std::cout << w << std::endl;

    // Word w2 = ~w;
    // std::cout << w2 << std::endl;

    // Word w3 = w;
    // std::cout << w3 << std::endl;

    // Word w4;
    // w4 = w;
    // std::cout << w4 << std::endl;

    // Word w5 = w2;
    // std::cout << w5 << std::endl;

    Word hello("Hello");
	Word world("World");

	Word HelloWorld = hello + world;
	std::cout << HelloWorld << std::endl;

	Word traicho("Traicho");
	std::cout << (traicho << 2) << std::endl;
	std::cout << (~traicho) << std::endl;

}