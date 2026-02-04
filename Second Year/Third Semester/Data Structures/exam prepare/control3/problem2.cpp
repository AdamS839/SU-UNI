#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <vector>
#include <queue>
#include <list>

// template<typename T>
// using graph = std::unordered_map<T, std::vector<T>>;

// template<typename T>
// int indexOf(std::vector<T> const &v, T const &el){ // 1 4 5 0 2 3 -= {}
//     for (int i = 0; i< v.size(); ++i){
//         if (v[i] == el){
//             return i;
//         }
//     }
//     return -1;
// }

// template<typename T>
// bool hasCycleLengthK(T const &vertex, unsigned k, graph<T> const &g, std::vector<T> &path){
//     int index = indexOf(path, vertex);

//     if(index > 0) return path.size() - index == k;

//     path.push_back(vertex); //1 4 5 0 2 3 - {}

//     bool cyclic = false;
//     for (T const &child : g.at(vertex)){
//         cyclic = cyclic || hasCycleLengthK(child, k, g, path);
//     }

//     path.pop_back();

//     return cyclic;
// }

// template<typename T>
// bool hasCycleLengthK(T const &vertex, unsigned k, graph<T> const &g){
//     std::vector<T> path;
//     return hasCycleLengthK(vertex, k, g, path);
// }

int getIndex(int const &val, std::vector<int> const &vec){
    for (int i = 0; i < vec.size(); ++i){
        if (vec[i] == val){
            return i;
        }
    }
    return -1;
}

bool hasCycleLengthK(int const &vertex, unsigned k, std::vector<std::list<int>> const &g, std::vector<int> &path){
    int index = getIndex(vertex, path);

    if (index > 0) return path.size() - index == k;

    path.push_back(vertex);

    bool cyclic = false;
    for (int const &child : g[vertex]){
        cyclic = cyclic || hasCycleLengthK(child, k, g, path);
    }
    path.pop_back();
    return cyclic;
}

bool hasCycleLengthK(int const &vertex, unsigned k, std::vector<std::list<int>> g){
    std::vector<int> path;
    return hasCycleLengthK(vertex, k, g, path);
}

int main () {

   std::vector<std::list<int>> g = {
        {4, 2},
        {4},
        {4,3},
        {},
        {5},
        {0}
    };


    std::cout << std::boolalpha;  
    std::cout << hasCycleLengthK(1, 5, g) << '\n';    

    return 0;
}



