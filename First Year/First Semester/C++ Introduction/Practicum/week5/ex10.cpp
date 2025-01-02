#include <iostream>

void sectionArr(int arr1[], int arr2[], int length1, int length2){
    //temp length value
    int cutArr[length1];
    int length3 = 0;
    
    for (int i = 0; i < length1; i++){
        for (int j = 0; j < length2; j++){
            if (arr1[i] == arr2[j]){
                bool AlreadyIn = false;
                int n = 0;
                while(n < length3){ // checking for duplicates
                    if(cutArr[n] == arr1[i]){
                        AlreadyIn = true;
                    }
                    ++n;
                }
                if (!AlreadyIn){
                    cutArr[length3] = arr1[i];
                    length3++;
                }
            }
        }
    }
    
    if (length3 == 0){
        std::cout << "Ø" << std::endl;    
    }
    else{
        for (int i = 0; i < length3; i++) {
            std::cout << "Section array: " << cutArr[i] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int arr1[50];
    int arr2[50];
    int lengthFirst, lengthSecond;
    
    std::cout << "Length of first array: ";
    std::cin >> lengthFirst;

    std::cout << "Length of second array: ";
    std::cin >> lengthSecond;

    for (int i = 0; i < lengthFirst; i++)
    {
        std::cin >> arr1[i];
    }
    for (int i = 0; i < lengthSecond; i++)
    {
        std::cin >> arr2[i];
    }

    sectionArr(arr1, arr2, lengthFirst, lengthSecond);
    
    
}