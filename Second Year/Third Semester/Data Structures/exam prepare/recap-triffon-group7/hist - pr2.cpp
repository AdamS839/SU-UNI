#include <iostream>
#include <list>
#include <vector>
#include <set>

template<typename T>
int count(T &a, std::list<T> const &list){
    int count = 0;
    auto it = list.begin();
    while(it != list.end()){
        if (*it == a) count++;
        ++it; 
    }
    return count;
}

template<typename T>
void remove(T const &a, std::list<T> &list){
    auto it = list.begin();
    while (it != list.end()){
        if (*it == a) it = list.erase(it);
        else ++it;
    }
}

template<typename T>
std::pair<T, int> getPairs(T &valSearch, std::list<T> &list){
    int counter = count(valSearch, list);
    return {valSearch, counter};
}

template<typename T>
std::vector<std::pair<T, int>> hist(std::list<T> &list){
    std::vector<std::pair<T,int>> result;
    std::vector<T> container;
    auto it = list.begin();
    while (it != list.end()){
        bool inside = false;
        for(T const &x : container){
            if (*it == x){
                inside = true;
                break;
            }
        }
        if(!inside){
            container.push_back(*it);
            result.push_back(getPairs(*it, list));
        }

        ++it;
    }

    return result;
}

int main() {

    std::list<int> l = {1,4,7,2,8,0,3,6,3,7,8,3,1,3};
    int val = 3;
    // std::cout << count(val, l) << '\n';

    // remove(val, l);
    // for(int const &val : l){
    //     std::cout << val << ' ';
    // }
    // std::cout << '\n';

    std::vector<std::pair<int, int>> histo = hist(l);

    for (std::pair<int,int> const &pair : histo){
        std::cout << pair.first << '/' << pair.second << ", ";
    }
    std::cout << '\n';

    return 0;
}