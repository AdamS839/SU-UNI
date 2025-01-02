#include <iostream>

int binarySearch(int *begin, int *end, int el){
    int *origin = begin;
    while (begin <= end)
    {
        int* mid = begin + (end - begin)/2;
        if(*mid == el) return mid - origin;
        else if(*mid > el) end = mid - 1;
        else if(*mid < el) begin = mid + 1;
    }
    return -1;
}

int main() {
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    std::cout << binarySearch(arr, arr+9, 7) << std::endl;
    std::cout << binarySearch(arr, arr+9, 100) << std::endl;
    return 0;
}