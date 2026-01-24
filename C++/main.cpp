#include "employee.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>  // For smart pointers
#include <iomanip>
#include <cctype>  // For toupper

using namespace std;

// Function prototypes
void displayMenu();
void addEmployee(vector<shared_ptr<Employee>>& employees);
void displayAllEmployees(const vector<shared_ptr<Employee>>& employees);
void searchEmployee(const vector<shared_ptr<Employee>>& employees);
void updateEmployee(vector<shared_ptr<Employee>>& employees);
void deleteEmployee(vector<shared_ptr<Employee>>& employees);
void sortEmployees(vector<shared_ptr<Employee>>& employees);
void filterEmployees(const vector<shared_ptr<Employee>>& employees);
void generateReport(const vector<shared_ptr<Employee>>& employees);

// Helper functions for sorting
bool compareById(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b);
bool compareByName(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b);
bool compareBySalary(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b);
bool compareByDepartment(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b);
bool compareByType(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b);

int main() {
    vector<shared_ptr<Employee>> employees;
    int choice;
    
    cout << "========================================\n";
    cout << "   ADVANCED EMPLOYEE MANAGEMENT SYSTEM   \n";
    cout << "========================================\n";
    
    // Create sample employees using inheritance
    employees.push_back(make_shared<FullTimeEmployee>("EMP001", "John", "Doe", 
                                                      "john@company.com", "123-456-7890", 
                                                      "Male", "IT", 60000.0, 5000.0, 20));
    
    employees.push_back(make_shared<PartTimeEmployee>("EMP002", "Jane", "Smith", 
                                                      "jane@company.com", "234-567-8901", 
                                                      "Female", "Marketing", 30.0, 25));
    
    employees.push_back(make_shared<Intern>("EMP003", "Bob", "Johnson", 
                                            "bob@company.com", "345-678-9012", 
                                            "Male", "Engineering", 
                                            "Tech University", "Computer Science", 6));
    
    employees.push_back(make_shared<FullTimeEmployee>("EMP004", "Alice", "Williams", 
                                                      "alice@company.com", "456-789-0123", 
                                                      "Female", "HR", 55000.0, 4000.0, 18));
    
    employees.push_back(make_shared<PartTimeEmployee>("EMP005", "Charlie", "Brown", 
                                                      "charlie@company.com", "567-890-1234", 
                                                      "Male", "Finance", 35.0, 15));
    
    cout << "Sample employees added to system.\n";
    
    do {
        displayMenu();
        cout << "Enter your choice (1-9): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        switch(choice) {
            case 1:
                addEmployee(employees);
                break;
            case 2:
                displayAllEmployees(employees);
                break;
            case 3:
                searchEmployee(employees);
                break;
            case 4:
                updateEmployee(employees);
                break;
            case 5:
                deleteEmployee(employees);
                break;
            case 6:
                sortEmployees(employees);
                break;
            case 7:
                filterEmployees(employees);
                break;
            case 8:
                generateReport(employees);
                break;
            case 9:
                cout << "\nThank you for using the Advanced Employee Management System!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
        
        cout << "\nPress Enter to continue...";
        cin.get();
        
    } while (choice != 9);
    
    return 0;
}

// Display main menu
void displayMenu() {
    cout << "\n============== MAIN MENU ==============\n";
    cout << "1. Add New Employee\n";
    cout << "2. Display All Employees\n";
    cout << "3. Search Employee\n";
    cout << "4. Update Employee\n";
    cout << "5. Delete Employee\n";
    cout << "6. Sort Employees\n";
    cout << "7. Filter Employees\n";
    cout << "8. Generate Report\n";
    cout << "9. Exit\n";
    cout << "=======================================\n";
}

// Add a new employee with type selection
void addEmployee(vector<shared_ptr<Employee>>& employees) {
    int empType;
    string id, fname, lname, email, phone, gender, dept;
    
    cout << "\n=== ADD NEW EMPLOYEE ===\n";
    cout << "Select Employee Type:\n";
    cout << "1. Full-Time Employee\n";
    cout << "2. Part-Time Employee\n";
    cout << "3. Intern\n";
    cout << "Enter choice (1-3): ";
    cin >> empType;
    cin.ignore();
    
    cout << "Enter Employee ID (e.g., EMP001): ";
    getline(cin, id);
    
    cout << "Enter First Name: ";
    getline(cin, fname);
    
    cout << "Enter Last Name: ";
    getline(cin, lname);
    
    cout << "Enter Email: ";
    getline(cin, email);
    
    cout << "Enter Phone: ";
    getline(cin, phone);
    
    cout << "Enter Gender: ";
    getline(cin, gender);
    
    cout << "Enter Department: ";
    getline(cin, dept);
    
    shared_ptr<Employee> newEmp;
    
    switch(empType) {
        case 1: { // Full-Time
            double salary, bonus;
            int vacation;
            cout << "Enter Base Salary: ";
            cin >> salary;
            cout << "Enter Annual Bonus: ";
            cin >> bonus;
            cout << "Enter Vacation Days: ";
            cin >> vacation;
            cin.ignore();
            
            newEmp = make_shared<FullTimeEmployee>(id, fname, lname, email, 
                                                    phone, gender, dept, 
                                                    salary, bonus, vacation);
            break;
        }
        case 2: { // Part-Time
            double hourlyRate;
            int hours;
            cout << "Enter Hourly Rate: ";
            cin >> hourlyRate;
            cout << "Enter Hours Per Week: ";
            cin >> hours;
            cin.ignore();
            
            newEmp = make_shared<PartTimeEmployee>(id, fname, lname, email,
                                                    phone, gender, dept,
                                                    hourlyRate, hours);
            break;
        }
        case 3: { // Intern
            string university, major;
            int duration;
            cout << "Enter University: ";
            getline(cin, university);
            cout << "Enter Major: ";
            getline(cin, major);
            cout << "Enter Internship Duration (months): ";
            cin >> duration;
            cin.ignore();
            
            newEmp = make_shared<Intern>(id, fname, lname, email,
                                         phone, gender, dept,
                                         university, major, duration);
            break;
        }
        default:
            cout << "Invalid employee type!\n";
            return;
    }
    
    employees.push_back(newEmp);
    cout << "\nEmployee added successfully!\n";
    cout << "Total employees: " << employees.size() << endl;
}

// Display all employees in a formatted table
void displayAllEmployees(const vector<shared_ptr<Employee>>& employees) {
    cout << fixed << setprecision(2);
    cout << "\n=== ALL EMPLOYEES ===\n";
    cout << "Total Employees: " << employees.size() << endl;
    
    if (employees.empty()) {
        cout << "No employees found!\n";
        return;
    }
    
    // Table header
    cout << "\n" << string(100, '-') << endl;
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(15) << "Type"
         << setw(15) << "Department"
         << setw(15) << "Salary/Month"
         << setw(25) << "Details" << endl;
    cout << string(100, '-') << endl;
    
    // Table rows
    for (size_t i = 0; i < employees.size(); i++) {
        cout << left << setw(10) << employees[i]->getEmployeeId()
             << setw(20) << employees[i]->getFullName()
             << setw(15) << employees[i]->getEmployeeType()
             << setw(15) << employees[i]->getDepartment()
             << setw(15) << employees[i]->calculateSalary();
        
        // Display specific details based on type
        if (auto fullTime = dynamic_pointer_cast<FullTimeEmployee>(employees[i])) {
            cout << "Bonus: $" << fullTime->getAnnualBonus();
        } else if (auto partTime = dynamic_pointer_cast<PartTimeEmployee>(employees[i])) {
            cout << "Rate: $" << partTime->getHourlyRate() << "/hr";
        } else if (auto intern = dynamic_pointer_cast<Intern>(employees[i])) {
            cout << "Intern, " << intern->getUniversity();
        }
        cout << endl;
    }
    cout << string(100, '-') << endl;
}

// Search for an employee with advanced options
void searchEmployee(const vector<shared_ptr<Employee>>& employees) {
    int searchOption;
    string searchTerm;
    
    cout << "\n=== SEARCH EMPLOYEE ===\n";
    cout << "Search by:\n";
    cout << "1. Employee ID\n";
    cout << "2. Name\n";
    cout << "3. Department\n";
    cout << "4. Employee Type\n";
    cout << "Enter choice (1-4): ";
    cin >> searchOption;
    cin.ignore();
    
    cout << "Enter search term: ";
    getline(cin, searchTerm);
    
    bool found = false;
    
    for (const auto& emp : employees) {
        bool match = false;
        
        switch(searchOption) {
            case 1: // Search by ID
                match = (emp->getEmployeeId() == searchTerm);
                break;
            case 2: // Search by Name
                match = (emp->getFullName().find(searchTerm) != string::npos);
                break;
            case 3: // Search by Department
                match = (emp->getDepartment().find(searchTerm) != string::npos);
                break;
            case 4: // Search by Type
                match = (emp->getEmployeeType().find(searchTerm) != string::npos);
                break;
        }
        
        if (match) {
            emp->displayEmployee();
            found = true;
        }
    }
    
    if (!found) {
        cout << "No employees found matching your search!\n";
    }
}

// Update an employee
void updateEmployee(vector<shared_ptr<Employee>>& employees) {
    string id;
    bool found = false;
    
    cout << "\n=== UPDATE EMPLOYEE ===\n";
    cout << "Enter Employee ID to update: ";
    getline(cin, id);
    
    for (auto& emp : employees) {
        if (emp->getEmployeeId() == id) {
            found = true;
            emp->displayEmployee();
            
            // Use dynamic casting to access derived class methods
            if (auto fullTime = dynamic_pointer_cast<FullTimeEmployee>(emp)) {
                double newBonus;
                cout << "Enter new annual bonus: ";
                cin >> newBonus;
                fullTime->setAnnualBonus(newBonus);
            } else if (auto partTime = dynamic_pointer_cast<PartTimeEmployee>(emp)) {
                double newRate;
                cout << "Enter new hourly rate: ";
                cin >> newRate;
                partTime->setHourlyRate(newRate);
            }
            
            cout << "\nEmployee updated successfully!\n";
            break;
        }
    }
    
    if (!found) {
        cout << "Employee ID not found!\n";
    }
}

// Delete an employee
void deleteEmployee(vector<shared_ptr<Employee>>& employees) {
    string id;
    char confirm;
    
    cout << "\n=== DELETE EMPLOYEE ===\n";
    cout << "Enter Employee ID to delete: ";
    getline(cin, id);
    
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getEmployeeId() == id) {
            cout << "\nEmployee found: " << (*it)->getFullName() << endl;
            cout << "Are you sure you want to delete? (y/n): ";
            cin >> confirm;
            cin.ignore();
            
            if (confirm == 'y' || confirm == 'Y') {
                employees.erase(it);
                cout << "Employee deleted successfully!\n";
            } else {
                cout << "Deletion cancelled.\n";
            }
            return;
        }
    }
    
    cout << "Employee ID not found!\n";
}

// Sort employees using different criteria
void sortEmployees(vector<shared_ptr<Employee>>& employees) {
    int sortChoice;
    
    cout << "\n=== SORT EMPLOYEES ===\n";
    cout << "Sort by:\n";
    cout << "1. Employee ID\n";
    cout << "2. Name (A-Z)\n";
    cout << "3. Salary (High to Low)\n";
    cout << "4. Department\n";
    cout << "5. Employee Type\n";
    cout << "Enter choice (1-5): ";
    cin >> sortChoice;
    cin.ignore();
    
    switch(sortChoice) {
        case 1:
            sort(employees.begin(), employees.end(), compareById);
            cout << "Employees sorted by ID!\n";
            break;
        case 2:
            sort(employees.begin(), employees.end(), compareByName);
            cout << "Employees sorted by Name!\n";
            break;
        case 3:
            sort(employees.begin(), employees.end(), compareBySalary);
            cout << "Employees sorted by Salary!\n";
            break;
        case 4:
            sort(employees.begin(), employees.end(), compareByDepartment);
            cout << "Employees sorted by Department!\n";
            break;
        case 5:
            sort(employees.begin(), employees.end(), compareByType);
            cout << "Employees sorted by Employee Type!\n";
            break;
        default:
            cout << "Invalid choice!\n";
            return;
    }
    
    // Display sorted list
    displayAllEmployees(employees);
}

// Filter employees based on criteria
void filterEmployees(const vector<shared_ptr<Employee>>& employees) {
    int filterChoice;
    
    cout << "\n=== FILTER EMPLOYEES ===\n";
    cout << "Filter by:\n";
    cout << "1. Department\n";
    cout << "2. Employee Type\n";
    cout << "3. Salary Range\n";
    cout << "Enter choice (1-3): ";
    cin >> filterChoice;
    cin.ignore();
    
    vector<shared_ptr<Employee>> filteredList;
    
    switch(filterChoice) {
        case 1: { // Filter by Department
            string dept;
            cout << "Enter department to filter: ";
            getline(cin, dept);
            
            for (const auto& emp : employees) {
                if (emp->getDepartment() == dept) {
                    filteredList.push_back(emp);
                }
            }
            cout << "\nFound " << filteredList.size() << " employees in " << dept << " department:\n";
            break;
        }
        case 2: { // Filter by Type
            string type;
            cout << "Enter employee type to filter (Full-Time/Part-Time/Intern): ";
            getline(cin, type);
            
            for (const auto& emp : employees) {
                if (emp->getEmployeeType() == type) {
                    filteredList.push_back(emp);
                }
            }
            cout << "\nFound " << filteredList.size() << " " << type << " employees:\n";
            break;
        }
        case 3: { // Filter by Salary Range
            double minSalary, maxSalary;
            cout << "Enter minimum salary: ";
            cin >> minSalary;
            cout << "Enter maximum salary: ";
            cin >> maxSalary;
            cin.ignore();
            
            for (const auto& emp : employees) {
                double salary = emp->calculateSalary();
                if (salary >= minSalary && salary <= maxSalary) {
                    filteredList.push_back(emp);
                }
            }
            cout << "\nFound " << filteredList.size() << " employees with salary between $" 
                 << minSalary << " and $" << maxSalary << ":\n";
            break;
        }
        default:
            cout << "Invalid choice!\n";
            return;
    }
    
    if (filteredList.empty()) {
        cout << "No employees match the filter criteria.\n";
    } else {
        // Display filtered results
        for (const auto& emp : filteredList) {
            cout << left << setw(10) << emp->getEmployeeId()
                 << setw(20) << emp->getFullName()
                 << setw(15) << emp->getEmployeeType()
                 << setw(15) << emp->getDepartment()
                 << "$" << emp->calculateSalary() << endl;
        }
    }
}

// Generate a comprehensive report
void generateReport(const vector<shared_ptr<Employee>>& employees) {
    cout << fixed << setprecision(2);
    cout << "\n=== EMPLOYEE MANAGEMENT SYSTEM REPORT ===\n";
    cout << "Generated on: [Current Date/Time]\n\n";
    
    if (employees.empty()) {
        cout << "No employees in the system.\n";
        return;
    }
    
    // Summary Statistics
    int fullTimeCount = 0, partTimeCount = 0, internCount = 0;
    double totalSalary = 0, highestSalary = 0, lowestSalary = 1e9;
    shared_ptr<Employee> highestPaid, lowestPaid;
    
    for (const auto& emp : employees) {
        double salary = emp->calculateSalary();
        totalSalary += salary;
        
        if (salary > highestSalary) {
            highestSalary = salary;
            highestPaid = emp;
        }
        if (salary < lowestSalary) {
            lowestSalary = salary;
            lowestPaid = emp;
        }
        
        // Count by type
        if (emp->getEmployeeType() == "Full-Time") fullTimeCount++;
        else if (emp->getEmployeeType() == "Part-Time") partTimeCount++;
        else if (emp->getEmployeeType() == "Intern") internCount++;
    }
    
    double avgSalary = employees.empty() ? 0 : totalSalary / employees.size();
    
    cout << "SUMMARY STATISTICS:\n";
    cout << string(40, '-') << endl;
    cout << "Total Employees:      " << employees.size() << endl;
    cout << "Full-Time Employees:  " << fullTimeCount << endl;
    cout << "Part-Time Employees:  " << partTimeCount << endl;
    cout << "Interns:              " << internCount << endl;
    cout << "Total Monthly Salary: $" << totalSalary << endl;
    cout << "Average Salary:       $" << avgSalary << endl;
    cout << "Highest Salary:       $" << highestSalary 
         << " (" << highestPaid->getFullName() << ")" << endl;
    cout << "Lowest Salary:        $" << lowestSalary 
         << " (" << lowestPaid->getFullName() << ")" << endl;
    
    // Department Breakdown
    cout << "\nDEPARTMENT BREAKDOWN:\n";
    cout << string(40, '-') << endl;
    
    // Count employees by department
    for (const auto& emp : employees) {
        bool deptFound = false;
        // You could use a map here for better efficiency
        // For simplicity, we'll just list them
        cout << emp->getDepartment() << ": " << emp->getFullName() 
             << " (" << emp->getEmployeeType() << ")" << endl;
    }
    
    // Recent Additions (last 5)
    cout << "\nRECENT EMPLOYEE ADDITIONS:\n";
    cout << string(40, '-') << endl;
    int count = min(5, (int)employees.size());
    for (int i = 0; i < count; i++) {
        cout << employees[i]->getEmployeeId() << " - " 
             << employees[i]->getFullName() << " - " 
             << employees[i]->getEmployeeType() << endl;
    }
}

// Comparison functions for sorting
bool compareById(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
    return a->getEmployeeId() < b->getEmployeeId();
}

bool compareByName(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
    return a->getFullName() < b->getFullName();
}

bool compareBySalary(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
    return a->calculateSalary() > b->calculateSalary(); // Descending order
}

bool compareByDepartment(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
    if (a->getDepartment() == b->getDepartment()) {
        return compareByName(a, b);
    }
    return a->getDepartment() < b->getDepartment();
}

bool compareByType(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
    if (a->getEmployeeType() == b->getEmployeeType()) {
        return compareByName(a, b);
    }
    return a->getEmployeeType() < b->getEmployeeType();
}