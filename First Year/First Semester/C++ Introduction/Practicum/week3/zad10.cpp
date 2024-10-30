#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    
    std::cout << "1. Waffle        0.80 lv\n"
              << "2. Chocolatebar  1.20 lv\n"
              << "3. Water         0.90 lv\n"
              << "4. Breadsticks   1.80 lv\n"
              << "5. Lemonade      1.35 lv\n";

    int productChoice;

    do
    {
        std::cin >> productChoice;
    } while (productChoice > 5 || productChoice < 1);

    /* ;(
    double wafflePrice = 0.80;
    double chocobarPrice = 1.20;
    double waterPrice = 0.90;
    double breadstPrice = 1.80;
    double lemonadePrice = 1.35;
    */

    int wafflePrice = 80;
    int chocobarPrice = 120;
    int waterPrice = 90;
    int breadstPrice = 180;
    int lemonadePrice = 135;

    int totalPrice = 0;

    switch (productChoice)
    {
    case 1:
        totalPrice = wafflePrice;
        break;
    case 2:
        totalPrice = chocobarPrice;
        break;
    case 3:
        totalPrice = waterPrice;
        break;
    case 4:
        totalPrice = breadstPrice;
        break;
    case 5:
        totalPrice = lemonadePrice;
        break;
    default:
        return 0;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Please put "<< totalPrice/100.0 << " lv." << std::endl;

    double inputMoney;
    do
    {
        std::cin >> inputMoney;
    } while (inputMoney < 0);
    
    double changeCoins = inputMoney*100 - totalPrice;
    
    while (changeCoins < 0)
    {
        std::cout << "Insufficient funds." << std::endl;
        return 0;
    }
    

    std::cout << "Your change is: " <<std::endl;
    while (changeCoins >= 5)
    {
        if (changeCoins >= 200){
            changeCoins -= 200;
            std::cout << "2.00 lv." << std::endl;
        }
        else if (changeCoins >= 100){
            changeCoins -= 100;
            std::cout << "1.00 lv." << std::endl;
        }
        else if (changeCoins >= 50){
            changeCoins -= 50;
            std::cout << "0.50 lv." << std::endl;
        }
        else if (changeCoins >= 20){
            changeCoins -= 20;
            std::cout << "0.20 lv." << std::endl;
        }
        else if (changeCoins >= 10){
            changeCoins -= 10;
            std::cout << "0.10 lv." << std::endl;
        }
        else if (changeCoins >= 5){
            changeCoins -= 5;
            std::cout << "0.05 lv." << std::endl;
            }
    }   
}