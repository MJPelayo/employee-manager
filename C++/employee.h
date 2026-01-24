#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>

// Base Employee class with only fields from your forms
class Employee {
protected:
    std::string employeeId;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;
    std::string gender;
    std::string department;
    std::string employeeType; // "full-time", "part-time", "intern"
    
public:
    // Constructors
    Employee();
    Employee(std::string id, std::string fname, std::string lname, 
             std::string email, std::string phone, std::string gender,
             std::string dept, std::string type);
    
    // Virtual destructor
    virtual ~Employee() {}
    
    // Pure virtual function
    virtual void displayDetails() const = 0;
    
    // Setter functions (exactly matching form fields)
    void setEmployeeId(std::string id);
    void setFirstName(std::string fname);
    void setLastName(std::string lname);
    void setEmail(std::string email);
    void setPhone(std::string phone);
    void setGender(std::string gender);
    void setDepartment(std::string dept);
    void setEmployeeType(std::string type);
    
    // Getter functions
    std::string getEmployeeId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getGender() const;
    std::string getDepartment() const;
    std::string getEmployeeType() const;
    
    // Utility functions
    std::string getFullName() const;
    
    // For sorting purposes
    virtual std::string getSortingKey() const;
};

// Derived classes based on employee type from your form
class FullTimeEmployee : public Employee {
public:
    FullTimeEmployee();
    FullTimeEmployee(std::string id, std::string fname, std::string lname,
                     std::string email, std::string phone, std::string gender,
                     std::string dept);
    
    void displayDetails() const override;
    std::string getSortingKey() const override;
};

class PartTimeEmployee : public Employee {
public:
    PartTimeEmployee();
    PartTimeEmployee(std::string id, std::string fname, std::string lname,
                     std::string email, std::string phone, std::string gender,
                     std::string dept);
    
    void displayDetails() const override;
    std::string getSortingKey() const override;
};

class InternEmployee : public Employee {
public:
    InternEmployee();
    InternEmployee(std::string id, std::string fname, std::string lname,
                   std::string email, std::string phone, std::string gender,
                   std::string dept);
    
    void displayDetails() const override;
    std::string getSortingKey() const override;
};

#endif // EMPLOYEE_H