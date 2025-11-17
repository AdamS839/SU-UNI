#include <iostream>
#include <vector>

//template <class T>
struct Node{
int data;
Node *next;

Node(int data, Node *next=nullptr) : data(data), next(next) {}
};

//template <class T>
Node *fromVector(std::vector<int> const &v){
    if(v.empty()) return nullptr;
    Node *begin = new Node(v.front()); 
    Node *list = begin;
    for(std::size_t i = 1; i< v.size(); ++i){
        list->next = new Node(v[i]);
        list = list->next;
    }
    list->next = begin; // <- circular
    return begin;
}

//template <class T>
void print(Node *l, std::ostream &os = std::cout){
    if (!l) return;
    Node const *first = l;
    do{
        std::cout << l->data << ' ';
        l = l->next;
    } while(l != first);
}

//template <class T>
bool isCycle(Node *l){
    if (!l) return false;
    Node *slow = l, *fast = l;
    while(/*slow &&*/ fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) return true;
    }
    return false;
}

Node *find_last(Node *l){
    if (!l) return nullptr;
    Node *iter = l;
    while (l != iter->next){
        iter = iter->next;
    }
    return iter;
}

void push_front(int el, Node *&front){
    if(!front){
        front = new Node(el);
        front->next = front;
        return;
    }
    Node * last = find_last(front);
    front = new Node(el, front);
    last->next = front;
}

void remove_next(Node *&l){
    if (!l) return;
    if (!l->next) return;
    if( l == l->next){
        delete l;
        l = nullptr;
        return;
    }
    Node *save = l->next->next;
    delete l->next;
    l->next = save;
}

// problem 3 - Josephus problem

int josephus(int n, int k){
    if (k<= 0 || n <= 0) return -1;
    Node *list = nullptr;
    while(n > 0){
        push_front(n--, list);
    }
    Node *prev = find_last(list);

    while(prev != prev->next){
        for(int i = 0; i< k-1; ++i){
            prev = prev->next;
        }
        remove_next(prev);
    }
    int winner = prev->data;
    delete prev;
    return winner;
}

int main() {
    // {
    //     std::vector<int> v{1,2,3,4,5};
    //     Node *l = fromVector(v);
    
    //     print(l); std::cout << std::endl;
    
    //     std::cout << isCycle(l) << std::endl;
    // }

    //Node<int> *l2 = fromVector(v);

    std::cout << josephus(4, 2) << std::endl;


    return 0;
}