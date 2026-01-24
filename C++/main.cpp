#include "employee.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <iomanip>

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

// Helper functions for sorting
bool compareById(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b);
bool compareByName(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b);
bool compareByDepartment(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b);
bool compareByType(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b);

int main() {
    vector<shared_ptr<Employee>> employees;
    int choice;
    
    // Reset counter at start
    Employee::resetCounter();
    
    cout << "================================\n";
    cout << "   EMPLOYEE MANAGEMENT SYSTEM   \n";
    cout << "================================\n";
    
    // Create sample employees matching your form
    // IDs will be auto-generated: EMP001, EMP002, etc.
    employees.push_back(make_shared<FullTimeEmployee>("John", "Doe", 
                                                      "john@employee.com", "(123) 456-7890", 
                                                      "Male", "IT"));
    
    employees.push_back(make_shared<PartTimeEmployee>("Jane", "Smith", 
                                                      "jane@employee.com", "(234) 567-8901", 
                                                      "Female", "HR"));
    
    employees.push_back(make_shared<InternEmployee>("Bob", "Johnson", 
                                                    "bob@employee.com", "(345) 678-9012", 
                                                    "Male", "IT"));
    
    cout << "Sample employees added to system.\n";
    cout << "Auto-generated IDs: EMP001, EMP002, EMP003\n";
    
    do {
        displayMenu();
        cout << "Enter your choice (1-8): ";
        cin >> choice;
        cin.ignore();
        
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
                cout << "\nThank you for using the Employee Management System!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
        
        cout << "\nPress Enter to continue...";
        cin.get();
        
    } while (choice != 8);
    
    return 0;
}

void displayMenu() {
    cout << "\n============== MAIN MENU ==============\n";
    cout << "1. Add New Employee (ID Auto-generated)\n";
    cout << "2. Display All Employees\n";
    cout << "3. Search Employee\n";
    cout << "4. Update Employee\n";
    cout << "5. Delete Employee\n";
    cout << "6. Sort Employees\n";
    cout << "7. Filter Employees\n";
    cout << "8. Exit\n";
    cout << "=======================================\n";
}

void addEmployee(vector<shared_ptr<Employee>>& employees) {
    int empType;
    string fname, lname, email, phone, gender, dept;
    
    cout << "\n=== ADD NEW EMPLOYEE ===\n";
    cout << "Employee ID will be auto-generated\n\n";
    
    cout << "Select Employee Type:\n";
    cout << "1. Full-Time Employee\n";
    cout << "2. Part-Time Employee\n";
    cout << "3. Intern\n";
    cout << "Enter choice (1-3): ";
    cin >> empType;
    cin.ignore();
    
    cout << "Enter First Name: ";
    getline(cin, fname);
    
    cout << "Enter Last Name: ";
    getline(cin, lname);
    
    cout << "Enter Email: ";
    getline(cin, email);
    
    cout << "Enter Phone (e.g., (123) 456-7890): ";
    getline(cin, phone);
    
    cout << "Enter Gender (Male/Female/Other): ";
    getline(cin, gender);
    
    cout << "Select Department:\n";
    cout << "1. Human Resources (HR)\n";
    cout << "2. Information Technology (IT)\n";
    cout << "3. Finance\n";
    cout << "4. Marketing\n";
    cout << "5. Operations\n";
    cout << "6. Sales\n";
    cout << "7. Design\n";
    cout << "8. Engineering\n";
    cout << "Enter choice (1-8): ";
    int deptChoice;
    cin >> deptChoice;
    cin.ignore();
    
    // Map department choice to department name
    switch(deptChoice) {
        case 1: dept = "HR"; break;
        case 2: dept = "IT"; break;
        case 3: dept = "Finance"; break;
        case 4: dept = "Marketing"; break;
        case 5: dept = "Operations"; break;
        case 6: dept = "Sales"; break;
        case 7: dept = "Design"; break;
        case 8: dept = "Engineering"; break;
        default: dept = "General"; break;
    }
    
    shared_ptr<Employee> newEmp;
    
    switch(empType) {
        case 1:
            newEmp = make_shared<FullTimeEmployee>(fname, lname, email, 
                                                   phone, gender, dept);
            break;
        case 2:
            newEmp = make_shared<PartTimeEmployee>(fname, lname, email, 
                                                   phone, gender, dept);
            break;
        case 3:
            newEmp = make_shared<InternEmployee>(fname, lname, email, 
                                                 phone, gender, dept);
            break;
        default:
            cout << "Invalid employee type!\n";
            return;
    }
    
    employees.push_back(newEmp);
    cout << "\nEmployee added successfully!\n";
    cout << "Auto-generated ID: " << newEmp->getEmployeeId() << endl;
    cout << "Total employees: " << employees.size() << endl;
}

void displayAllEmployees(const vector<shared_ptr<Employee>>& employees) {
    cout << "\n=== ALL EMPLOYEES ===\n";
    cout << "Total Employees: " << employees.size() << endl;
    
    if (employees.empty()) {
        cout << "No employees found!\n";
        return;
    }
    
    cout << "\n" << string(80, '-') << endl;
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(15) << "Type"
         << setw(15) << "Department"
         << setw(20) << "Email" << endl;
    cout << string(80, '-') << endl;
    
    for (const auto& emp : employees) {
        cout << left << setw(10) << emp->getEmployeeId()
             << setw(20) << emp->getFullName()
             << setw(15) << emp->getEmployeeType()
             << setw(15) << emp->getDepartment()
             << setw(20) << emp->getEmail() << endl;
    }
    cout << string(80, '-') << endl;
}

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
            case 1:
                match = (emp->getEmployeeId() == searchTerm);
                break;
            case 2:
                match = (emp->getFullName().find(searchTerm) != string::npos);
                break;
            case 3:
                match = (emp->getDepartment().find(searchTerm) != string::npos);
                break;
            case 4:
                match = (emp->getEmployeeType().find(searchTerm) != string::npos);
                break;
        }
        
        if (match) {
            emp->displayDetails();
            found = true;
        }
    }
    
    if (!found) {
        cout << "No employees found matching your search!\n";
    }
}

void updateEmployee(vector<shared_ptr<Employee>>& employees) {
    string id;
    bool found = false;
    
    cout << "\n=== UPDATE EMPLOYEE ===\n";
    cout << "Enter Employee ID to update: ";
    getline(cin, id);
    
    for (auto& emp : employees) {
        if (emp->getEmployeeId() == id) {
            found = true;
            emp->displayDetails();
            
            int updateChoice;
            cout << "\nWhat would you like to update?\n";
            cout << "1. Email\n";
            cout << "2. Phone\n";
            cout << "3. Department\n";
            cout << "Enter choice (1-3): ";
            cin >> updateChoice;
            cin.ignore();
            
            if (updateChoice == 1) {
                string newEmail;
                cout << "Enter new email: ";
                getline(cin, newEmail);
                emp->setEmail(newEmail);
            } else if (updateChoice == 2) {
                string newPhone;
                cout << "Enter new phone: ";
                getline(cin, newPhone);
                emp->setPhone(newPhone);
            } else if (updateChoice == 3) {
                string newDept;
                cout << "Enter new department: ";
                getline(cin, newDept);
                emp->setDepartment(newDept);
            } else {
                cout << "Invalid choice!\n";
                return;
            }
            
            cout << "\nEmployee updated successfully!\n";
            emp->displayDetails();
            break;
        }
    }
    
    if (!found) {
        cout << "Employee ID not found!\n";
    }
}

void deleteEmployee(vector<shared_ptr<Employee>>& employees) {
    string id;
    char confirm;
    
    cout << "\n=== DELETE EMPLOYEE ===\n";
    cout << "Enter Employee ID to delete: ";
    getline(cin, id);
    
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getEmployeeId() == id) {
            cout << "\nEmployee found: " << (*it)->getFullName() 
                 << " (ID: " << (*it)->getEmployeeId() << ")" << endl;
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

void sortEmployees(vector<shared_ptr<Employee>>& employees) {
    int sortChoice;
    
    cout << "\n=== SORT EMPLOYEES ===\n";
    cout << "Sort by:\n";
    cout << "1. Employee ID\n";
    cout << "2. Name (A-Z)\n";
    cout << "3. Department\n";
    cout << "4. Employee Type\n";
    cout << "Enter choice (1-4): ";
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
            sort(employees.begin(), employees.end(), compareByDepartment);
            cout << "Employees sorted by Department!\n";
            break;
        case 4:
            sort(employees.begin(), employees.end(), compareByType);
            cout << "Employees sorted by Employee Type!\n";
            break;
        default:
            cout << "Invalid choice!\n";
            return;
    }
    
    displayAllEmployees(employees);
}

void filterEmployees(const vector<shared_ptr<Employee>>& employees) {
    int filterChoice;
    
    cout << "\n=== FILTER EMPLOYEES ===\n";
    cout << "Filter by:\n";
    cout << "1. Department\n";
    cout << "2. Employee Type\n";
    cout << "Enter choice (1-2): ";
    cin >> filterChoice;
    cin.ignore();
    
    vector<shared_ptr<Employee>> filteredList;
    
    if (filterChoice == 1) {
        string dept;
        cout << "Enter department to filter (HR/IT/Finance/Marketing/Operations/Sales/Design/Engineering): ";
        getline(cin, dept);
        
        for (const auto& emp : employees) {
            if (emp->getDepartment() == dept) {
                filteredList.push_back(emp);
            }
        }
        cout << "\nFound " << filteredList.size() << " employees in " << dept << " department:\n";
    } else if (filterChoice == 2) {
        string type;
        cout << "Enter employee type to filter (full-time/part-time/intern): ";
        getline(cin, type);
        
        for (const auto& emp : employees) {
            if (emp->getEmployeeType() == type) {
                filteredList.push_back(emp);
            }
        }
        cout << "\nFound " << filteredList.size() << " " << type << " employees:\n";
    } else {
        cout << "Invalid choice!\n";
        return;
    }
    
    if (filteredList.empty()) {
        cout << "No employees match the filter criteria.\n";
    } else {
        cout << "\n" << string(80, '-') << endl;
        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(15) << "Type"
             << setw(15) << "Department"
             << setw(20) << "Email" << endl;
        cout << string(80, '-') << endl;
        
        for (const auto& emp : filteredList) {
            cout << left << setw(10) << emp->getEmployeeId()
                 << setw(20) << emp->getFullName()
                 << setw(15) << emp->getEmployeeType()
                 << setw(15) << emp->getDepartment()
                 << setw(20) << emp->getEmail() << endl;
        }
        cout << string(80, '-') << endl;
    }
}

// Comparison functions for sorting
bool compareById(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
    return a->getEmployeeId() < b->getEmployeeId();
}

bool compareByName(const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
    return a->getFullName() < b->getFullName();
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