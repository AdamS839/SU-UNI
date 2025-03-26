#include <iostream>
#include "BookTracker.hpp"

void BookTracker::addBookForFuture(Book const& b){
    b.future = true;
}
bool BookTracker::isBookRead(Book const&) const{

}
void BookTracker::addBookForNow(Book const&){

}
void BookTracker::printBooksFromCat() const{

}
void BookTracker::giveReview(Book const&){

}