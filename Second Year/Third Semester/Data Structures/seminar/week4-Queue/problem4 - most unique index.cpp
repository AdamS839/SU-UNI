#include <iostream>
#include <queue>

int most_unique(std::string const &str){
    int occurances[256] {};
    std::queue<int> q;

    for (int i = 0; i < str.size(); ++i){
        q.push(i);
        occurances[str[i]]++;
    }

    while(!q.empty()){
        int index = q.front();
        if(occurances[str[index]] == 1){
            return index;
        }
        else q.pop();
    }
    return -1;
}

int main() {

    std::cout << most_unique("abcd bac") << std::endl;
    return 0;
}