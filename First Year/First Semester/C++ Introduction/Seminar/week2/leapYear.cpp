#include <iostream>

int main() {
    int year;

    std:: cin >> year;
    int checkYear; 

    int YearBeforeLeap; // Години преди, които е имало високосна година 
    
    checkYear = (year % 100); //Взимаме последните 2 цифри и те образуват число, което трябва да се дели на 4, за да е високосна годината
    if (checkYear % 4 == 0) //Проверка дали въведената година е високосна
    {
        year += 4;
    }
    else {
        YearBeforeLeap = checkYear % 4; // Намираме преди колко години е била високосната
        year -= YearBeforeLeap; // Премахваме от въведената година миналите години и ни дава предишната високосна
        year += 4; // Добавяме 4 към предишната висоскосна и намираме следващата вискосна
    }
    
    std:: cout << year;
    
}