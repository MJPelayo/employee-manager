#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>

// Base Employee class
class Employee {
protected:  // Changed from private to allow inheritance
    std::string employeeId;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;
    std::string gender;
    std::string department;
    std::string employeeType;
    double baseSalary;  // Added for inheritance demo
    
public:
    // Constructors
    Employee();
    Employee(std::string id, std::string fname, std::string lname, 
             std::string email, std::string phone, std::string gender,
             std::string dept, std::string type, double baseSalary = 30000.0);
    
    // Virtual destructor for polymorphism
    virtual ~Employee() {}
    
    // Pure virtual function - makes Employee an abstract base class
    virtual double calculateSalary() const = 0;
    
    // Virtual function for display - can be overridden
    virtual void displayEmployee() const;
    
    // Setter functions
    void setEmployeeId(std::string id);
    void setFirstName(std::string fname);
    void setLastName(std::string lname);
    void setEmail(std::string email);
    void setPhone(std::string phone);
    void setGender(std::string gender);
    void setDepartment(std::string dept);
    void setEmployeeType(std::string type);
    void setBaseSalary(double salary);
    
    // Getter functions
    std::string getEmployeeId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getGender() const;
    std::string getDepartment() const;
    std::string getEmployeeType() const;
    double getBaseSalary() const;
    
    // Utility functions
    std::string getFullName() const;
    
    // New function for filtering/sorting
    virtual std::string getDetailsForSorting() const;
};

// Derived Class 1: FullTimeEmployee
class FullTimeEmployee : public Employee {
private:
    double annualBonus;
    int vacationDays;
    
public:
    FullTimeEmployee();
    FullTimeEmployee(std::string id, std::string fname, std::string lname,
                     std::string email, std::string phone, std::string gender,
                     std::string dept, double baseSalary = 50000.0,
                     double bonus = 5000.0, int vacation = 20);
    
    // Override virtual functions
    double calculateSalary() const override;
    void displayEmployee() const override;
    
    // Specific getters/setters
    void setAnnualBonus(double bonus);
    void setVacationDays(int days);
    double getAnnualBonus() const;
    int getVacationDays() const;
    
    std::string getDetailsForSorting() const override;
};

// Derived Class 2: PartTimeEmployee
class PartTimeEmployee : public Employee {
private:
    int hoursPerWeek;
    double hourlyRate;
    
public:
    PartTimeEmployee();
    PartTimeEmployee(std::string id, std::string fname, std::string lname,
                     std::string email, std::string phone, std::string gender,
                     std::string dept, double hourlyRate = 25.0,
                     int hours = 20);
    
    // Override virtual functions
    double calculateSalary() const override;
    void displayEmployee() const override;
    
    // Specific getters/setters
    void setHoursPerWeek(int hours);
    void setHourlyRate(double rate);
    int getHoursPerWeek() const;
    double getHourlyRate() const;
    
    std::string getDetailsForSorting() const override;
};

// Derived Class 3: Intern
class Intern : public Employee {
private:
    std::string university;
    std::string major;
    int internshipDuration; // in months
    
public:
    Intern();
    Intern(std::string id, std::string fname, std::string lname,
           std::string email, std::string phone, std::string gender,
           std::string dept, std::string university = "Unknown",
           std::string major = "Computer Science", int duration = 6);
    
    // Override virtual functions
    double calculateSalary() const override;
    void displayEmployee() const override;
    
    // Specific getters/setters
    void setUniversity(std::string uni);
    void setMajor(std::string major);
    void setInternshipDuration(int duration);
    std::string getUniversity() const;
    std::string getMajor() const;
    int getInternshipDuration() const;
    
    std::string getDetailsForSorting() const override;
};

#endif // EMPLOYEE_H