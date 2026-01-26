#include "employee.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// Initialize static counter
int Employee::employeeCounter = 0;

// ==================== BASE EMPLOYEE CLASS ====================

Employee::Employee() {
    employeeId = generateEmployeeId();
    firstName = "John";
    lastName = "Doe";
    email = "john.doe@company.com";
    phone = "(123) 456-7890";
    gender = "Male";
    department = "IT";
    employeeType = "full-time";
}

Employee::Employee(string fname, string lname, 
                   string email, string phone, string gender,
                   string dept, string type) {
    employeeId = generateEmployeeId();
    setFirstName(fname);
    setLastName(lname);
    setEmail(email);
    setPhone(phone);
    setGender(gender);
    setDepartment(dept);
    setEmployeeType(type);
}

// Generate auto employee ID: EMP001, EMP002, etc.
string Employee::generateEmployeeId() {
    employeeCounter++;
    ostringstream oss;
    oss << "EMP" << setw(3) << setfill('0') << employeeCounter;
    return oss.str();
}

// Setter functions
void Employee::setEmployeeId(string id) {
    if (!id.empty()) {
        employeeId = id;
    }
}

void Employee::setFirstName(string fname) {
    if (!fname.empty()) {
        firstName = fname;
    }
}

void Employee::setLastName(string lname) {
    if (!lname.empty()) {
        lastName = lname;
    }
}

void Employee::setEmail(string email) {
    if (!email.empty()) {
        this->email = email;
    }
}

void Employee::setPhone(string phone) {
    if (!phone.empty()) {
        this->phone = phone;
    }
}

void Employee::setGender(string gender) {
    if (!gender.empty()) {
        this->gender = gender;
    }
}

void Employee::setDepartment(string dept) {
    if (!dept.empty()) {
        department = dept;
    }
}

void Employee::setEmployeeType(string type) {
    if (!type.empty()) {
        employeeType = type;
    }
}

// Getter functions
string Employee::getEmployeeId() const {
    return employeeId;
}

string Employee::getFirstName() const {
    return firstName;
}

string Employee::getLastName() const {
    return lastName;
}

string Employee::getEmail() const {
    return email;
}

string Employee::getPhone() const {
    return phone;
}

string Employee::getGender() const {
    return gender;
}

string Employee::getDepartment() const {
    return department;
}

string Employee::getEmployeeType() const {
    return employeeType;
}

// Get full name
string Employee::getFullName() const {
    return firstName + " " + lastName;
}

// For sorting
string Employee::getSortingKey() const {
    return employeeId;
}

// ==================== FULL-TIME EMPLOYEE ====================

FullTimeEmployee::FullTimeEmployee() 
    : Employee("John", "Doe", "john@company.com", 
               "(123) 456-7890", "Male", "IT", "full-time") {
}

FullTimeEmployee::FullTimeEmployee(string fname, string lname,
                                   string email, string phone, string gender,
                                   string dept) 
    : Employee(fname, lname, email, phone, gender, dept, "full-time") {
}

void FullTimeEmployee::displayDetails() const {
    cout << "\n===== FULL-TIME EMPLOYEE =====\n";
    cout << "Employee ID:    " << getEmployeeId() << endl;
    cout << "Name:           " << getFullName() << endl;
    cout << "Email:          " << getEmail() << endl;
    cout << "Phone:          " << getPhone() << endl;
    cout << "Gender:         " << getGender() << endl;
    cout << "Department:     " << getDepartment() << endl;
    cout << "Employee Type:  " << getEmployeeType() << endl;
    cout << "===============================\n";
}

string FullTimeEmployee::getSortingKey() const {
    return "FT_" + getEmployeeId();
}

// ==================== PART-TIME EMPLOYEE ====================

PartTimeEmployee::PartTimeEmployee() 
    : Employee("Jane", "Smith", "jane@company.com", 
               "(234) 567-8901", "Female", "HR", "part-time") {
}

PartTimeEmployee::PartTimeEmployee(string fname, string lname,
                                   string email, string phone, string gender,
                                   string dept) 
    : Employee(fname, lname, email, phone, gender, dept, "part-time") {
}

void PartTimeEmployee::displayDetails() const {
    cout << "\n===== PART-TIME EMPLOYEE =====\n";
    cout << "Employee ID:    " << getEmployeeId() << endl;
    cout << "Name:           " << getFullName() << endl;
    cout << "Email:          " << getEmail() << endl;
    cout << "Phone:          " << getPhone() << endl;
    cout << "Gender:         " << getGender() << endl;
    cout << "Department:     " << getDepartment() << endl;
    cout << "Employee Type:  " << getEmployeeType() << endl;
    cout << "===============================\n";
}

string PartTimeEmployee::getSortingKey() const {
    return "PT_" + getEmployeeId();
}

// ==================== INTERN EMPLOYEE ====================

InternEmployee::InternEmployee() 
    : Employee("Bob", "Johnson", "bob@company.com", 
               "(345) 678-9012", "Male", "IT", "intern") {
}

InternEmployee::InternEmployee(string fname, string lname,
                               string email, string phone, string gender,
                               string dept) 
    : Employee(fname, lname, email, phone, gender, dept, "intern") {
}

void InternEmployee::displayDetails() const {
    cout << "\n===== INTERN EMPLOYEE =====\n";
    cout << "Employee ID:    " << getEmployeeId() << endl;
    cout << "Name:           " << getFullName() << endl;
    cout << "Email:          " << getEmail() << endl;
    cout << "Phone:          " << getPhone() << endl;
    cout << "Gender:         " << getGender() << endl;
    cout << "Department:     " << getDepartment() << endl;
    cout << "Employee Type:  " << getEmployeeType() << endl;
    cout << "============================\n";
}

string InternEmployee::getSortingKey() const {
    return "IN_" + getEmployeeId();
}