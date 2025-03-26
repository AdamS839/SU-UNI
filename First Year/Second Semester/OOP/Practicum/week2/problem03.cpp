#include <iostream>

template<class T>
void bubbleSort(T arr[], size_t size){
    for (size_t i = 0; i < size-1; i++){
        //bool swap = false;
        for (size_t j = 0; j < size - i - 1; j++){
            if(arr[j] > arr[j+1]){
                std::swap(arr[j], arr[j+1]);
                //swap = true;
            }
        }
        //if(!swap) return;
    }
}

int main() {
    int arri[]{3,7,1,9};
    bubbleSort(arri,sizeof(arri)/sizeof(int));  
    //~> [1,3,7,9]
    for (size_t i = 0; i < 4; i++)
    {
        std::cout << arri[i] << ' ';
    }
    std::cout << std::endl;

    char arrc[] = "a string is also an array!";
    bubbleSort(arrc,sizeof(arrc)-1);
    //~> "     !aaaaagiilnnorrrsssty"
    std::cout << arrc << std::endl;
    return 0;
}