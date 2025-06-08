#include <iostream>
#include <functional>
#include <cassert>
#include <cstring>

class Book{
private:
    char title[101];
    char author[51];
    long long ISBN;

    Book() {
        title[0] = 0;
        author[0] = 0;
        ISBN = 0;
    }
    
public:
    Book(const char *title, const char *author, long long isbn) : ISBN(isbn) {
        strncpy(this->title, title, 100);
        strncpy(this->author, author, 50);
    }

    const char *getTitle() const {return title;}
    const char *getAuthor() const {return author;}
    long long getISBN() const {return ISBN;}

    void print(std::ostream &os) const {
        os << "Book title: " << title << ", author name: " << author << ", ISBN code: " << ISBN << "." << std::endl;
    }
    friend class Library;
};

class Library{
private:
    Book *books;
    unsigned int *copies;
    unsigned int N;
    unsigned int currentSize;
    
public:

    void clear() {
        delete[] books;
        delete[] copies;
        books = nullptr;
        copies = nullptr;
    }

    void copy(const Library &other){
        N = other.N;
        currentSize = other.currentSize;
        books = new Book[N];
        copies = new unsigned int[N];
        for (unsigned int i = 0; i < currentSize; ++i)
        {
            books[i] = other.books[i];
            copies[i] = other.copies[i];
        }
    }

    Library(unsigned int capacity) : N(capacity), currentSize(0), books(new Book[capacity]), copies(new unsigned int[capacity]) {}

    ~Library(){ clear(); }

    Library(const Library &other){
        copy(other);
    }

    Library &operator=(const Library &other){
        if(this != &other){
            clear();
            copy(other);
        }
        return *this;
    }

    Library& addBook(const Book &bookadd, unsigned int copiestoadd){
        assert(currentSize < N);
        for (unsigned int i = 0; i < currentSize; ++i)
        {
            if(bookadd.getISBN() == books[i].getISBN()){
                copies[i] += copiestoadd;
            }
        }
        books[currentSize] = bookadd;
        copies[currentSize] = copiestoadd;
        currentSize++; 
        return *this;
    }

    unsigned int countBooks() const{
        unsigned int counter = 0;
        for (unsigned int i = 0; i < currentSize; ++i)
        {
            counter += copies[i];
        }
        return counter;
    }

    Library merge(const Library &other){
        unsigned int unioncapacity = this->N + other.N;
        Library newLib(unioncapacity);
        for (unsigned int i = 0; i < currentSize; ++i)
        {
            newLib.addBook(books[i], copies[i]);
        }
        for (unsigned int i = 0; i < other.currentSize; ++i)
        {
            newLib.addBook(other.books[i], other.copies[i]);
        }
        newLib.currentSize = this->currentSize + other.currentSize;
        return newLib;
    }

    void serealize(std::ostream &os) const {
        os << "Library capacity: " << N << ", current size: " << currentSize << std::endl;
        for (unsigned int i = 0; i < currentSize; ++i)
        {
            books[i].print(os);
        }
    }
};

int main() {

    Library fmi(100), home(20);

    fmi.addBook({"ООП със C++", "Тодорова", 1111111111}, 10).addBook({"trytest", "asdfg", 9876543211}, 69);
    home.addBook({"JavaScript за начинаещи", "Smartman", 3333333333}, 1);

    fmi.merge(home).serealize(std::cout);


    return 0;
}