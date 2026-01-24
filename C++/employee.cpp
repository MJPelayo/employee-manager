#include "employee.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// ==================== BASE EMPLOYEE CLASS ====================

// Default constructor
Employee::Employee() {
    employeeId = "EMP000";
    firstName = "Unknown";
    lastName = "Unknown";
    email = "unknown@company.com";
    phone = "000-000-0000";
    gender = "Unknown";
    department = "General";
    employeeType = "Employee";
    baseSalary = 30000.0;
}

// Parameterized constructor
Employee::Employee(string id, string fname, string lname, 
                   string email, string phone, string gender,
                   string dept, string type, double baseSalary) {
    setEmployeeId(id);
    setFirstName(fname);
    setLastName(lname);
    setEmail(email);
    setPhone(phone);
    setGender(gender);
    setDepartment(dept);
    setEmployeeType(type);
    setBaseSalary(baseSalary);
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
    if (!email.empty() && email.find('@') != string::npos) {
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

void Employee::setBaseSalary(double salary) {
    if (salary > 0) {
        baseSalary = salary;
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

double Employee::getBaseSalary() const {
    return baseSalary;
}

// Display function
void Employee::displayEmployee() const {
    cout << fixed << setprecision(2);
    cout << "\n====== EMPLOYEE DETAILS ======\n";
    cout << "Employee ID:    " << employeeId << endl;
    cout << "Name:           " << firstName << " " << lastName << endl;
    cout << "Email:          " << email << endl;
    cout << "Phone:          " << phone << endl;
    cout << "Gender:         " << gender << endl;
    cout << "Department:     " << department << endl;
    cout << "Employee Type:  " << employeeType << endl;
    cout << "Base Salary:    $" << baseSalary << endl;
    cout << "Calculated Salary: $" << calculateSalary() << endl;
    cout << "================================\n";
}

// Get full name
string Employee::getFullName() const {
    return firstName + " " + lastName;
}

// For sorting purposes
string Employee::getDetailsForSorting() const {
    return employeeId + "|" + getFullName() + "|" + department + "|" + employeeType;
}

// ==================== FULL-TIME EMPLOYEE ====================

FullTimeEmployee::FullTimeEmployee() : Employee() {
    annualBonus = 5000.0;
    vacationDays = 20;
    setEmployeeType("Full-Time");
}

FullTimeEmployee::FullTimeEmployee(string id, string fname, string lname,
                                   string email, string phone, string gender,
                                   string dept, double baseSalary,
                                   double bonus, int vacation) 
    : Employee(id, fname, lname, email, phone, gender, dept, "Full-Time", baseSalary) {
    setAnnualBonus(bonus);
    setVacationDays(vacation);
}

double FullTimeEmployee::calculateSalary() const {
    return getBaseSalary() + annualBonus;  // Annual salary with bonus
}

void FullTimeEmployee::displayEmployee() const {
    Employee::displayEmployee();  // Call base class display
    cout << "Annual Bonus:   $" << annualBonus << endl;
    cout << "Vacation Days:  " << vacationDays << " days" << endl;
    cout << "Total Salary:   $" << calculateSalary() << " per year" << endl;
    cout << "================================\n";
}

void FullTimeEmployee::setAnnualBonus(double bonus) {
    if (bonus >= 0) {
        annualBonus = bonus;
    }
}

void FullTimeEmployee::setVacationDays(int days) {
    if (days >= 0) {
        vacationDays = days;
    }
}

double FullTimeEmployee::getAnnualBonus() const {
    return annualBonus;
}

int FullTimeEmployee::getVacationDays() const {
    return vacationDays;
}

string FullTimeEmployee::getDetailsForSorting() const {
    return Employee::getDetailsForSorting() + "|FT|" + to_string((int)calculateSalary());
}

// ==================== PART-TIME EMPLOYEE ====================

PartTimeEmployee::PartTimeEmployee() : Employee() {
    hoursPerWeek = 20;
    hourlyRate = 25.0;
    setEmployeeType("Part-Time");
    setBaseSalary(0);  // Part-time uses hourly rate
}

PartTimeEmployee::PartTimeEmployee(string id, string fname, string lname,
                                   string email, string phone, string gender,
                                   string dept, double hourlyRate,
                                   int hours) 
    : Employee(id, fname, lname, email, phone, gender, dept, "Part-Time", 0) {
    setHourlyRate(hourlyRate);
    setHoursPerWeek(hours);
}

double PartTimeEmployee::calculateSalary() const {
    // Calculate monthly salary: hours/week * 4 weeks * hourly rate
    return hoursPerWeek * 4 * hourlyRate;
}

void PartTimeEmployee::displayEmployee() const {
    Employee::displayEmployee();
    cout << "Hourly Rate:    $" << hourlyRate << endl;
    cout << "Hours/Week:     " << hoursPerWeek << endl;
    cout << "Monthly Salary: $" << calculateSalary() << endl;
    cout << "Yearly Salary:  $" << calculateSalary() * 12 << endl;
    cout << "================================\n";
}

void PartTimeEmployee::setHoursPerWeek(int hours) {
    if (hours > 0 && hours <= 40) {
        hoursPerWeek = hours;
    }
}

void PartTimeEmployee::setHourlyRate(double rate) {
    if (rate > 0) {
        hourlyRate = rate;
    }
}

int PartTimeEmployee::getHoursPerWeek() const {
    return hoursPerWeek;
}

double PartTimeEmployee::getHourlyRate() const {
    return hourlyRate;
}

string PartTimeEmployee::getDetailsForSorting() const {
    return Employee::getDetailsForSorting() + "|PT|" + to_string((int)calculateSalary());
}

// ==================== INTERN ====================

Intern::Intern() : Employee() {
    university = "Unknown University";
    major = "Computer Science";
    internshipDuration = 6;
    setEmployeeType("Intern");
    setBaseSalary(0);
}

Intern::Intern(string id, string fname, string lname,
               string email, string phone, string gender,
               string dept, string university,
               string major, int duration) 
    : Employee(id, fname, lname, email, phone, gender, dept, "Intern", 0) {
    setUniversity(university);
    setMajor(major);
    setInternshipDuration(duration);
}

double Intern::calculateSalary() const {
    // Interns get a monthly stipend
    return 1500.0;  // Fixed monthly stipend
}

void Intern::displayEmployee() const {
    Employee::displayEmployee();
    cout << "University:     " << university << endl;
    cout << "Major:          " << major << endl;
    cout << "Duration:       " << internshipDuration << " months" << endl;
    cout << "Monthly Stipend:$" << calculateSalary() << endl;
    cout << "================================\n";
}

void Intern::setUniversity(string uni) {
    if (!uni.empty()) {
        university = uni;
    }
}

void Intern::setMajor(string major) {
    if (!major.empty()) {
        this->major = major;
    }
}

void Intern::setInternshipDuration(int duration) {
    if (duration > 0) {
        internshipDuration = duration;
    }
}

string Intern::getUniversity() const {
    return university;
}

string Intern::getMajor() const {
    return major;
}

int Intern::getInternshipDuration() const {
    return internshipDuration;
}

string Intern::getDetailsForSorting() const {
    return Employee::getDetailsForSorting() + "|IN|" + to_string((int)calculateSalary());
}