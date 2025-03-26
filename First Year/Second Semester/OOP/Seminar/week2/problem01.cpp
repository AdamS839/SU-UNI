#include <iostream>
#include <cstring>

const int nameLength = 50;
const int gradeMax = 10;

class Student{
    private:

        char fullName[nameLength];
        int Age;
        int Grades[gradeMax];

    public:

    void setGrades(){
        int grade[gradeMax];
        for (int i = 0; i < gradeMax; i++)
        {
            std::cin >> grade[i];
        }
        
        for (int i = 0; i < gradeMax; i++){
            if(grade[i] >= 2 && grade[i] <= 6) Grades[i] = grade[i];
            else Grades[i] = 0;
        }
    }
    float calcAvg(){
        float avg = 0;
        for (int i = 0; i < gradeMax; i++){
            if(Grades[i] == 0) return -1;
            avg += Grades[i];
        }
        return avg/gradeMax;
    }
    void print_Grades() {
        std::cout << "Grades: ";
        for (int i = 0; i < gradeMax; i++) {
            std::cout << Grades[i] << " ";
        }
        std::cout << std::endl;
    }
    void setAge(int age){
        while (age > 100 || age < 16)
        {
            std::cout << "Wrong age interval! Try again!" << std::endl;
            std::cin >> age;
        }      
        this->Age = age;
    }
    void setName(const char name[nameLength]){
        std::strncpy(fullName, name, nameLength - 1);
        fullName[nameLength - 1] = '\0';
    }

    int get_Age(){
        return Age;
    }
    void print_Name(){
        std::cout << "Student name is: "<< fullName << std::endl;
    }
    int get_Grades(){
        return Grades[gradeMax];
    }
};

int main() {
    Student student1;
    student1.setName("Aleksandar");
    student1.setAge(-5);
    // int grades[gradeMax];
    // std::cout << "Enter grades from 1 to 10" << std::endl;
    // for (int i = 0; i < gradeMax; i++)
    // {
    //     std::cin >> grades[i];
    // }
    // student1.setGrades(grades);
    
    student1.setGrades();
     

    // std::cout << "Student 1 name is: " << student1.print_Name() << std::endl;
    student1.print_Name();
    std::cout << "Student 1 age is: " << student1.get_Age() << std::endl;
    std::cout << "Student 1 average grade is: " << student1.calcAvg() << std::endl;

    return 0;
}