#include "Exception.h"

int main() {
    try
    {
        foo();
    }
    catch(int x)
    {
        std::cout << x;
    }
    catch(RuntimeError const &re){
        std::cout << re.what();
    }
}