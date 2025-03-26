#ifndef __BookTracker_HPP
#define __BookTracker_HPP

struct Book
{
    char name[50];
    bool future;
    bool present;
    bool isRead;
    int review;
};


class BookTracker{
public:
void addBookForFuture(Book const&);
bool isBookRead(Book const&) const;
void addBookForNow(Book const&);
void printBooksFromCat() const;
void giveReview(Book const&);
private:
Book b;
};

#endif