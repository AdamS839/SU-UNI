#include <iostream>
#include <vector>
#include <queue>
#include <list>

// https://github.com/triffon/sdp-2024-25-midterm-2/blob/main/G_3_F.cpp

struct Node{
    int code;
    Node *prev, *next;

    Node(int code, Node *prev=nullptr, Node *next=nullptr) : code(code), prev(prev), next(next) {}
};

Node *fromVector(std::vector<int> const &v){
    if (v.empty()) return nullptr;

    Node dummy(0);
    Node *dptr = &dummy;

    for (int val : v){
        dptr->next = new Node(val, dptr);
        dptr = dptr->next;
    }

    dummy.prev->next = nullptr;
    return dummy.next;
}

Node *moveLeft(Node *start, int n){
    if (!start) return nullptr;
    while (start && n < 0){
        start = start->prev;
        n++;
    }
    return start;
}

Node *moveRight(Node *start, int n){
    if (!start) return nullptr;
    while (start && n > 0){
        start = start->next;
        n--;
    }
    return start;
}

void deleteNode(Node *curr){
    if (!curr) return;
    Node *previous = curr->prev;
    Node *next = curr->next;
    delete curr;

    if (previous) previous->next = next;
    if (next) next->prev = previous;
}

void free(Node *list){
    Node *temp;
    while (list){
        temp = list->next;
        delete list;
        list = temp;
    }
}

int steps(Node *start, int n){
    int step = 0;
    int counter = 0;
    while (start && start->code != 0){
        step++;
        counter++;
        if (step == n){
            Node *temp = start;
            if (start->code > 0) start = start->next;
            if (start->code < 0) start = start->prev;

            deleteNode(temp);
            continue;
        }
        if (start->code > 0) start = moveRight(start, start->code);
        if (start->code < 0) start = moveLeft(start, start->code);
    }
    if (!start) return -1;
    return counter + 1;
}

void free(Node *list){
    Node *temp;
    while(list){
        temp = list->next;
        delete list;
        list = temp;
    }
}

int main() {

  Node *list = fromVector({-1,2,1,3,-2,0,4});

  std::cout << steps(list->next->next, 2) << '\n';

  free(list);

  return 0;
}