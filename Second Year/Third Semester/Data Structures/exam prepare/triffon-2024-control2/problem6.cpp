#include <iostream>
#include <vector>
#include <list>

// https://github.com/triffon/sdp-2024-25-midterm-2/blob/main/G_6_F.cpp

struct Node{
    int dir, page;
    Node *prev, *next;

    Node(int dir, int page, Node *p=nullptr, Node *n=nullptr) : dir(dir), page(page), prev(p), next(n) {}
};

Node *moveByDir(Node *start, int dir){
    if (!start) return nullptr;
    if (dir > 0) start = start->next;
    else start = start->prev;
    return start;
}

void deleteNode(Node *start){
    if (!start) return;
    Node *prev = start->prev;
    Node *next = start->next;
    delete start;
    if (prev) prev->next = next;
    if (next) next->prev = prev;
}

Node *findNext(Node *start, int nextpage, int dir, int &counter){
    while(start && start->page != nextpage){
        counter++;
        start = moveByDir(start, dir);
        if (start && start->page < 0){
            Node *temp = start;
            start = (dir > 0) ? start->prev : start->next; // -> 13 ||  start = (dir > 0) ? start->next : start->prev; -> 10
            deleteNode(temp);
            continue;
        }
    }
    return start;
}

int pages(Node *start){
    int counter = 0;

    if (!start || start->page != 1){
        return -1;
    }

    while(start && start->dir != 0){
        start = findNext(start, start->page + 1, start->dir, counter);
    }

    if (!start) return -1;
    return counter;
}

Node *fromVector(std::vector<std::pair<int,int>> const &pages){
    if (pages.empty()) return nullptr;

    Node *head = new Node(pages[0].second, pages[0].first);
    Node *prev = head;

    for (std::size_t i = 1; i < pages.size(); ++i){
        Node *curr = new Node(pages[i].second, pages[i].first);
        curr->prev = prev;
        prev->next = curr;
        prev = curr;
    }
    return head;
}

int main() {
    std::vector<std::pair<int,int>> example = {
        {5, 0},   // 5↓ крайна
        {3, 1},   // 3→
        {-2, 1},  // -2→ чернова
        {1, 1},   // 1→
        {-1, -1}, // -1← чернова
        {2, -1},  // 2←
        {-3, 1},  // -3→ чернова
        {4, -1}   // 4←
    };

    Node* list = fromVector(example);
    std::cout << pages(list->next->next->next) << '\n';
    return 0;
}