#include "Workplace.hpp"

int main() {
    // Test 1: Create Employees

    Employee emp1("John Doe", 50000, "Engineer");
    Employee emp2("Jane Smith", 60000, "Manager");



    std::cout << "Employee 1: " << std::endl;
    std::cout << emp1 << std::endl;

    std::cout << "Employee 2: " << std::endl;
    std::cout << emp2 << std::endl;

    // Test 2: Create EmployeeTeam with capacity of 2
    EmployeeTeam team(2);

    // Test 3: Add Employees to EmployeeTeam
    team.push_back(emp1);
    team.push_back(emp2);

    std::cout << "Employee Team: " << std::endl;
    team.print(std::cout, team);

    // Test 4: Copy constructor and assignment operator
    EmployeeTeam teamCopy = team;  // Test copy constructor
    std::cout << "Copied Team: " << std::endl;
    teamCopy.print(std::cout, teamCopy);

    EmployeeTeam teamAssigned(2);
    teamAssigned = team;  // Test assignment operator
    std::cout << "Assigned Team: " << std::endl;
    teamAssigned.print(std::cout, teamAssigned);

    // Test 5: Iteration over the team using normal iterator (forward iteration)
    std::cout << "Forward iteration (begin to end):" << std::endl;
    for (auto it = team.begin(); it != team.end(); ++it) {
        std::cout << *it << std::endl;
    }

    // Test 6: Iteration over the team using reverse iterator (reverse iteration)
    std::cout << "Reverse iteration (end to begin):" << std::endl;
    for (auto it = team.rbegin(); it != team.rend(); ++it) {
        std::cout << *it << std::endl;
    }

    // Test 7: Check empty team scenario
    EmployeeTeam team1111;
    std::cout << "Empty Team:\n";
    team1111.print(std::cout, team1111);

    return 0;
}
