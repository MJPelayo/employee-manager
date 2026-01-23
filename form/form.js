// Check if user is logged in
if (localStorage.getItem("loggedIn") !== "true") {
    window.location.href = "../login/index.html";
}

// DOM Elements
const employeeIdInput = document.getElementById("employeeId");
const firstNameInput = document.getElementById("firstName");
const lastNameInput = document.getElementById("lastName");
const departmentSelect = document.getElementById("department");
const errorElement = document.getElementById("error");
const saveBtn = document.getElementById("saveBtn");
const cancelBtn = document.getElementById("cancelBtn");

// Load employees from localStorage
let employees = JSON.parse(localStorage.getItem("employees")) || [];
const editIndex = localStorage.getItem("editIndex");

// Load data if editing
if (editIndex !== null && employees[editIndex]) {
    const employee = employees[editIndex];
    employeeIdInput.value = employee.employeeId;
    firstNameInput.value = employee.firstName;
    lastNameInput.value = employee.lastName;
    departmentSelect.value = employee.department;
}

// Validation function
function validateForm() {
    const employeeId = employeeIdInput.value.trim();
    const firstName = firstNameInput.value.trim();
    const lastName = lastNameInput.value.trim();
    const department = departmentSelect.value;

    // Reset error
    errorElement.textContent = "";

    // Check for empty fields
    if (!employeeId || !firstName || !lastName || !department) {
        errorElement.textContent = "All fields are required.";
        return false;
    }

    // Check if employee ID already exists (only for new employees)
    if (editIndex === null) {
        const existingEmployee = employees.find(emp => 
            emp.employeeId === employeeId
        );
        if (existingEmployee) {
            errorElement.textContent = "Employee ID already exists.";
            return false;
        }
    }

    return true;
}

// Save employee
saveBtn.addEventListener("click", () => {
    if (!validateForm()) {
        return;
    }

    const employee = {
        employeeId: employeeIdInput.value.trim(),
        firstName: firstNameInput.value.trim(),
        lastName: lastNameInput.value.trim(),
        department: departmentSelect.value
    };

    if (editIndex !== null) {
        // Update existing employee
        employees[editIndex] = employee;
        localStorage.removeItem("editIndex");
    } else {
        // Add new employee
        employees.push(employee);
    }

    // Save to localStorage
    localStorage.setItem("employees", JSON.stringify(employees));
    
    // Redirect to employee list
    window.location.href = "../user/index.html";
});

// Cancel button
cancelBtn.addEventListener("click", () => {
    localStorage.removeItem("editIndex");
    window.location.href = "../user/index.html";
});

// Clear error when user starts typing
employeeIdInput.addEventListener("input", () => errorElement.textContent = "");
firstNameInput.addEventListener("input", () => errorElement.textContent = "");
lastNameInput.addEventListener("input", () => errorElement.textContent = "");
departmentSelect.addEventListener("change", () => errorElement.textContent = "");