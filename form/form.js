
// Check if user is logged in
if (localStorage.getItem("loggedIn") !== "true") {
    window.location.href = "../login/index.html";
}

// DOM Elements
const employeeIdInput = document.getElementById("employeeId");
const firstNameInput = document.getElementById("firstName");
const lastNameInput = document.getElementById("lastName");
const departmentSelect = document.getElementById("department");
const employeeTypeSelect = document.getElementById("employeeType");
const errorElement = document.getElementById("error");
const saveBtn = document.getElementById("saveBtn");
const cancelBtn = document.getElementById("cancelBtn");

// Load employees from localStorage
let employees = JSON.parse(localStorage.getItem("employees")) || [];
const editIndex = localStorage.getItem("editIndex");

// Update form header based on edit mode
const formHeader = document.querySelector('.form-header h2');
const formSubHeader = document.querySelector('.form-header p');
if (editIndex !== null) {
    formHeader.innerHTML = '<i class="fas fa-user-edit"></i> Edit Employee';
    formSubHeader.textContent = 'Update employee information';
} else {
    formHeader.innerHTML = '<i class="fas fa-user-plus"></i> Add Employee';
    formSubHeader.textContent = 'Add new employee to the system';
}

// Load data if editing
if (editIndex !== null && employees[editIndex]) {
    const employee = employees[editIndex];
    employeeIdInput.value = employee.employeeId || '';
    firstNameInput.value = employee.firstName || '';
    lastNameInput.value = employee.lastName || '';
    departmentSelect.value = employee.department || '';
    employeeTypeSelect.value = employee.employeeType || '';
    
    // Disable employee ID field when editing
    employeeIdInput.disabled = true;
    employeeIdInput.style.backgroundColor = '#f5f5f5';
    employeeIdInput.style.color = '#666';
}

// Validation function
function validateForm() {
    const employeeId = employeeIdInput.value.trim();
    const firstName = firstNameInput.value.trim();
    const lastName = lastNameInput.value.trim();
    const department = departmentSelect.value;
    const employeeType = employeeTypeSelect.value;

    // Reset error
    errorElement.textContent = "";

    // Check for empty fields
    if (!employeeId || !firstName || !lastName || !department || !employeeType) {
        errorElement.textContent = "All fields are required.";
        return false;
    }

    // Check employee ID format (optional: alphanumeric with length 3-10)
    const idRegex = /^[A-Za-z0-9]{3,10}$/;
    if (!idRegex.test(employeeId)) {
        errorElement.textContent = "Employee ID must be 3-10 alphanumeric characters.";
        return false;
    }

    // Check name format (letters and spaces only)
    const nameRegex = /^[A-Za-z\s]{2,50}$/;
    if (!nameRegex.test(firstName) || !nameRegex.test(lastName)) {
        errorElement.textContent = "Names must contain only letters and spaces (2-50 characters).";
        return false;
    }

    // Check if employee ID already exists (only for new employees)
    if (editIndex === null) {
        const existingEmployee = employees.find(emp => 
            emp.employeeId.toLowerCase() === employeeId.toLowerCase()
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
        employeeId: employeeIdInput.value.trim().toUpperCase(),
        firstName: firstNameInput.value.trim(),
        lastName: lastNameInput.value.trim(),
        department: departmentSelect.value,
        employeeType: employeeTypeSelect.value
    };

    // Show loading state
    const originalText = saveBtn.innerHTML;
    saveBtn.innerHTML = '<i class="fas fa-spinner fa-spin"></i> SAVING...';
    saveBtn.disabled = true;

    setTimeout(() => {
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
        
        // Success animation
        saveBtn.innerHTML = '<i class="fas fa-check"></i> SAVED!';
        saveBtn.style.background = "linear-gradient(135deg, #28a745 0%, #1e7e34 100%)";
        
        // Redirect to employee list after delay
        setTimeout(() => {
            window.location.href = "../user/index.html";
        }, 1000);
    }, 800);
});

// Cancel button
cancelBtn.addEventListener("click", () => {
    localStorage.removeItem("editIndex");
    window.location.href = "../user/index.html";
});

// Real-time validation indicators
function setInputState(input, isValid) {
    if (input.value.trim()) {
        input.style.borderColor = isValid ? '#28a745' : '#dc3545';
    } else {
        input.style.borderColor = '#e0e0e0';
    }
}

employeeIdInput.addEventListener('input', function() {
    const value = this.value.trim();
    const isValid = /^[A-Za-z0-9]{3,10}$/.test(value);
    const isDuplicate = editIndex === null && employees.some(emp => 
        emp.employeeId.toLowerCase() === value.toLowerCase()
    );
    setInputState(this, isValid && !isDuplicate);
});

firstNameInput.addEventListener('input', function() {
    const isValid = /^[A-Za-z\s]{2,50}$/.test(this.value.trim());
    setInputState(this, isValid);
});

lastNameInput.addEventListener('input', function() {
    const isValid = /^[A-Za-z\s]{2,50}$/.test(this.value.trim());
    setInputState(this, isValid);
});

// Clear error when user starts typing
[employeeIdInput, firstNameInput, lastNameInput, departmentSelect, employeeTypeSelect].forEach(element => {
    element.addEventListener('input', () => errorElement.textContent = "");
    element.addEventListener('change', () => errorElement.textContent = "");
});

// Allow Enter key to submit form
document.addEventListener('keypress', function(e) {
    if (e.key === 'Enter' && !e.target.matches('button, select')) {
        e.preventDefault();
        saveBtn.click();
    }
});
