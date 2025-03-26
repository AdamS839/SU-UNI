#include "Nodes.hpp"
#include <iostream>

int main() {
    LinkedList<int> l1;
    l1.push_forward(4);
    l1.push_forward(3);
    //l1.addElementByIndex(7,0);
    l1.push_back(8);
    l1.removeFirst();
    l1.print();
    return 0;
}