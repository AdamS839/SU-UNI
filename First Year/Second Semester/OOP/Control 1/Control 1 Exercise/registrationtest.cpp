#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "VehicleList.h"


//  Generated tests

TEST_CASE("Registration class tests") {
    // Testing constructor with valid and invalid registration numbers
    CHECK_NOTHROW(Registration("C1234AB"));  
    CHECK_NOTHROW(Registration("XY1111YX")); 
    
    CHECK_THROWS(Registration("111145"));   
    CHECK_THROWS(Registration("ABC34DEF")); 
    CHECK_THROWS(Registration("ABCDEF"));    
    CHECK_THROWS(Registration("C11D"));    
    
    // Testing the toString() method
    Registration reg1("C1234AB");
    CHECK(std::strcmp(reg1.toString(), "C1234AB") == 0);
    
    // Testing the equality operator (operator==)
    Registration reg2("XY1111YX");
    Registration reg3("XY1111YX");
    Registration reg4("C1234AB");
    
    CHECK(reg2 == reg3); 
    CHECK_FALSE(reg2 == reg4); 
}


TEST_CASE("Vehicle class tests") {
    // Create a Vehicle object and check if the description and registration number are correct
    Vehicle v("C1234AB", "Car");
    
    // Check description
    CHECK(std::strcmp(v.getDescription(), "Car") == 0);
    
    // Check registration number
    CHECK(v.getRegnum() == Registration("C1234AB"));
    
    // Create another Vehicle object
    Vehicle v2("XY1111YX", "Truck");
    
    // Check description of second vehicle
    CHECK(std::strcmp(v2.getDescription(), "Truck") == 0);
    
    // Check if the registration number is correct
    CHECK(v2.getRegnum() == Registration("XY1111YX"));
}


TEST_CASE("VehicleList additional tests") {
    VehicleList list(3);
    
    CHECK(list.capacity() == 3);
    CHECK(list.size() == 0);
    CHECK(list.empty());

    // Insert vehicles
    list.insert("A1234BC", "Sedan");
    list.insert("XY5678ZZ", "Truck");

    CHECK(list.size() == 2);
    CHECK_FALSE(list.empty());

    // Attempt to insert a duplicate
    CHECK_THROWS(list.insert("A1234BC", "Duplicate"));

    // Fill to capacity
    list.insert("B8765CD", "Motorcycle");
    CHECK(list.size() == 3);
    CHECK_THROWS(list.insert("Z9999ZZ", "Over capacity"));

    // Test at() method
    CHECK_NOTHROW(list.at(0));
    CHECK_NOTHROW(list.at(1));
    CHECK_NOTHROW(list.at(2));
    CHECK_THROWS(list.at(3));

    // Test operator[]
    CHECK(list[0].getRegnum() == Registration("A1234BC"));
    CHECK(list[1].getRegnum() == Registration("XY5678ZZ"));
    CHECK(list[2].getRegnum() == Registration("B8765CD"));

    // Test find()
    CHECK(list.find(Registration("A1234BC")) != nullptr);
    CHECK(list.find(Registration("XY5678ZZ")) != nullptr);
    CHECK(list.find(Registration("B8765CD")) != nullptr);
    CHECK(list.find(Registration("Z9999ZZ")) == nullptr);
}


int main() {

    std::size_t vehicleNumber;
    std::cin >> vehicleNumber;

    char* description;

    VehicleList list(vehicleNumber);

    for (std::size_t i = 0; i < vehicleNumber; ++i)
    {
        char regnum[9];
        std::cin.getline(regnum, 9, '\n');
        std::cin.getline(description, std::strlen(description)+1, '\n');
        
    }
    


    return 0;
}