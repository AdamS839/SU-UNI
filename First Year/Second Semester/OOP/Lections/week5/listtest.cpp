#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "lists1.cpp"

TEST_CASE("TESTING PUSH AND BACKPUSH"){
    List<int> l1;
    List<int> l2;
    
    //l2.push(20);

    l1.push(3); 
    l1.push(5);
    l1.push(8);
    l1.push(10);
    l1.push_back(11);
    
    l2.append(l1);

    l1.print();
    l2.print();

    CHECK(l1 == l2);
}
