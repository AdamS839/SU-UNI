#include <iostream>
#include <queue>
#include <vector>
#include <string>

std::vector<std::string> binary(int n){
    std::vector<std::string> result;
    std::queue<std::string> queue;
    queue.push("1");
    for (int i = 0; i < n; ++i){
        std::string front = queue.front();
        queue.pop();
        queue.push(front + "0");
        queue.push(front + "1");
        result.push_back(std::move(front));
    }
    return result;
}

int main(){

    std::vector<std::string> result = binary(7);

    for (std::string const &s : result) std::cout << s << " ";
    std::cout << std::endl;
    
    return 0;
}