#include <iostream>
#include <vector>

struct node{
    int data;
    node *next;

    node(int val, node *next=nullptr) : data(val), next(next) {}
};

node *fromVector(std::vector<int> &vec){
    if (vec.empty()) return nullptr;

    node *begin = new node(vec.front());
    node *list = begin;
    for (std::size_t i = 0; i < vec.size(); ++i){
        list->next = new node(vec[i]);
        list = list->next;
    }
    list->next = begin;
    return begin;
}

void print(node *l, std::ostream &os=std::cout){
    if (!l) return;

    node const *first = l;
    do{
        std::cout << l->data << ' ';
        l = l->next;
    } while (l != first);

    std::cout << std::endl;
}

bool hasCycle(node *l){
    node *slow = l, *fast = l;
    while (fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) return true;
    }

    return false;
}

node *find_last(node *l){
    node *iter = l;
    while (iter && iter->next != l){
        iter = iter->next;
    }
    return iter;
}

void push_front(int el, node *&front){
    if (!front){
        front = new node(el);
        front->next = front;
        return;
    }

    node *last = find_last(front);
    front = new node(el, front);
    last->next = front;
}

void remove_next(node *&l){
    if (!l || !l->next) return;

    if (l == l->next){
        delete l;
        l = nullptr;
        return;
    }
    node *save = l->next->next;
    delete l->next;
    l->next = save;
}

int josephus(int n, int k){
    if (k <= 0 || n <= 0) return -1;
    node *list = nullptr;
    while (n> 0){
        push_front(n--, list);
    }
    node *prev = find_last(list);

    while(prev != prev->next){
        for (int i = 0; i < k-1; ++i){
            prev = prev->next;
        }
        remove_next(prev);
    }
    int winner = prev->data;
    delete prev;
    return winner;
}


int main() {

    return 0;
}