#include <iostream>
#include <random>

int main() {
    int n;

    //https://cplusplus.com/reference/random/

    std::default_random_engine generate;
    generate.seed(std::random_device{}());

    std::uniform_int_distribution<int> distribution(1, 20);

    int randomNum = distribution(generate);

    while (std::cin >> n && n != randomNum)
    {
        std::cout << "Wrong number" << std::endl;
    }

    std::cout << "You guessed correctly" << std::endl;
    
    
    
}