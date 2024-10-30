#include <iostream>

void LongestUnderArray(int n){
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    
    int maxlength = 1;
    int startFrom = 0;
    int currentLength = 1;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] >= arr[i - 1])
        {
            currentLength++;
        }
        else {
            if (currentLength > maxlength) 
            {
                maxlength = currentLength;
                startFrom = i - currentLength;
            }
            currentLength = 1;
        }
    }
    if (currentLength > maxlength)
    {
        maxlength = currentLength;
        startFrom = n - currentLength;
    }
    
    for (int i = startFrom; i < startFrom + maxlength; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
 
}

int main() {
    int n;
    std::cin >> n;
    LongestUnderArray(n);
}