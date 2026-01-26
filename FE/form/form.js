
// Check if user is logged in
if (localStorage.getItem("loggedIn") !== "true") {
    window.location.href = "../login/index.html";
}

// DOM Elements
const employeeIdInput = document.getElementById("employeeId");
const firstNameInput = document.getElementById("firstName");
const lastNameInput = document.getElementById("lastName");
const emailInput = document.getElementById("email");
const phoneInput = document.getElementById("phone");
const genderSelect = document.getElementById("gender");
const departmentSelect = document.getElementById("department");
const employeeTypeSelect = document.getElementById("employeeType");
const profilePictureInput = document.getElementById("profilePicture");
const profilePreview = document.getElementById("profilePreview");
const profilePictureContainer = document.getElementById("profilePictureContainer");
const errorElement = document.getElementById("error");
const saveBtn = document.getElementById("saveBtn");
const cancelBtn = document.getElementById("cancelBtn");
const backBtn = document.getElementById("backBtn");
const formTitle = document.getElementById("formTitle");
const formSubtitle = document.getElementById("formSubtitle");

// Load employees from localStorage
let employees = JSON.parse(localStorage.getItem("employees")) || [];
const editIndex = localStorage.getItem("editIndex");

// Update form header based on edit mode
if (editIndex !== null) {
    formTitle.innerHTML = '<i class="fas fa-user-edit"></i> Edit Employee';
    formSubtitle.textContent = 'Update employee information';
} else {
    formTitle.innerHTML = '<i class="fas fa-user-plus"></i> Add New Employee';
    formSubtitle.textContent = 'Add new employee to the system';
}

// Load data if editing
if (editIndex !== null && employees[editIndex]) {
    const employee = employees[editIndex];
    
    // Set form values
    employeeIdInput.value = employee.employeeId || '';
    firstNameInput.value = employee.firstName || '';
    lastNameInput.value = employee.lastName || '';
    emailInput.value = employee.email || '';
    phoneInput.value = employee.phone || '';
    genderSelect.value = employee.gender || '';
    departmentSelect.value = employee.department || '';
    employeeTypeSelect.value = employee.employeeType || '';
    
    // Profile Picture
    if (employee.profilePicture) {
        profilePreview.src = employee.profilePicture;
        profilePictureContainer.classList.add('has-image');
    }
    
    // Disable employee ID field when editing
    employeeIdInput.disabled = true;
    employeeIdInput.style.backgroundColor = '#f8f9fa';
    employeeIdInput.style.color = '#666';
}

// Profile Picture Upload
profilePictureContainer.addEventListener('click', () => {
    profilePictureInput.click();
});

profilePictureInput.addEventListener('change', function(e) {
    const file = e.target.files[0];
    if (file) {
        // Check file size (max 2MB)
        if (file.size > 2 * 1024 * 1024) {
            errorElement.textContent = "Image size must be less than 2MB";
            return;
        }
        
        // Check file type
        if (!file.type.match('image.*')) {
            errorElement.textContent = "Please select an image file (JPG, PNG)";
            return;
        }
        
        const reader = new FileReader();
        reader.onload = function(e) {
            profilePreview.src = e.target.result;
            profilePictureContainer.classList.add('has-image');
            errorElement.textContent = "";
        };
        reader.readAsDataURL(file);
    }
});

// Back button
backBtn.addEventListener('click', () => {
    cancelForm();
});

// Cancel button
cancelBtn.addEventListener('click', () => {
    cancelForm();
});

function cancelForm() {
    if (confirm("Are you sure you want to cancel? Any unsaved changes will be lost.")) {
        localStorage.removeItem("editIndex");
        window.location.href = "../user/index.html";
    }
}

// Validation function
function validateForm() {
    const requiredFields = [
        { element: employeeIdInput, name: "Employee ID" },
        { element: firstNameInput, name: "First Name" },
        { element: lastNameInput, name: "Last Name" },
        { element: emailInput, name: "Email Address" },
        { element: phoneInput, name: "Phone Number" },
        { element: genderSelect, name: "Gender" },
        { element: departmentSelect, name: "Department" },
        { element: employeeTypeSelect, name: "Employee Type" }
    ];

    // Reset error
    errorElement.textContent = "";

    // Check for empty required fields
    for (const field of requiredFields) {
        if (!field.element.value.trim()) {
            errorElement.textContent = `${field.name} is required.`;
            field.element.focus();
            return false;
        }
    }

    // Employee ID validation
    const employeeId = employeeIdInput.value.trim();
    const idRegex = /^[A-Za-z0-9-]{3,20}$/;
    if (!idRegex.test(employeeId)) {
        errorElement.textContent = "Employee ID must be 3-20 alphanumeric characters.";
        employeeIdInput.focus();
        return false;
    }

    // Check if employee ID already exists (only for new employees)
    if (editIndex === null) {
        const existingEmployee = employees.find(emp => 
            emp.employeeId.toLowerCase() === employeeId.toLowerCase()
        );
        if (existingEmployee) {
            errorElement.textContent = "Employee ID already exists.";
            employeeIdInput.focus();
            return false;
        }
    }

    // Name validation
    const nameRegex = /^[A-Za-z\s.'-]{2,50}$/;
    if (!nameRegex.test(firstNameInput.value.trim())) {
        errorElement.textContent = "First name must be 2-50 letters only.";
        firstNameInput.focus();
        return false;
    }
    if (!nameRegex.test(lastNameInput.value.trim())) {
        errorElement.textContent = "Last name must be 2-50 letters only.";
        lastNameInput.focus();
        return false;
    }

    // Email validation
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!emailRegex.test(emailInput.value.trim())) {
        errorElement.textContent = "Please enter a valid email address.";
        emailInput.focus();
        return false;
    }

    // Phone validation
    const phoneRegex = /^[\d\s\-\+\(\)]{10,20}$/;
    if (!phoneRegex.test(phoneInput.value.trim())) {
        errorElement.textContent = "Please enter a valid phone number (10-20 digits).";
        phoneInput.focus();
        return false;
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
        fullName: `${firstNameInput.value.trim()} ${lastNameInput.value.trim()}`,
        email: emailInput.value.trim(),
        phone: phoneInput.value.trim(),
        gender: genderSelect.value,
        department: departmentSelect.value,
        employeeType: employeeTypeSelect.value,
        profilePicture: profilePreview.src || null,
        createdAt: editIndex !== null ? employees[editIndex].createdAt : new Date().toISOString(),
        updatedAt: new Date().toISOString()
    };

    // Show loading state
    const originalText = saveBtn.innerHTML;
    const originalBg = saveBtn.style.background;
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

// Format phone numbers
function formatPhoneNumber(input) {
    let value = input.value.replace(/\D/g, '');
    if (value.length > 10) {
        value = value.substring(0, 10);
    }
    if (value.length >= 6) {
        input.value = `(${value.substring(0, 3)}) ${value.substring(3, 6)}-${value.substring(6)}`;
    } else if (value.length >= 3) {
        input.value = `(${value.substring(0, 3)}) ${value.substring(3)}`;
    } else {
        input.value = value;
    }
}

phoneInput.addEventListener('input', () => formatPhoneNumber(phoneInput));

// Real-time validation indicators
function setInputState(input, isValid) {
    if (input.value.trim()) {
        input.style.borderColor = isValid ? '#28a745' : '#dc3545';
    } else {
        input.style.borderColor = '#e0e0e0';
    }
}

// Add input listeners for real-time validation
const allInputs = document.querySelectorAll('input, select');
allInputs.forEach(input => {
    input.addEventListener('input', () => errorElement.textContent = "");
    input.addEventListener('change', () => errorElement.textContent = "");
});

// Auto-generate employee ID for new entries
if (editIndex === null) {
    const nextId = employees.length + 1;
    employeeIdInput.value = `EMP${nextId.toString().padStart(3, '0')}`;
}

// Allow Enter key to submit form
document.addEventListener('keypress', function(e) {
    if (e.key === 'Enter' && !e.target.matches('button, select')) {
        e.preventDefault();
        saveBtn.click();
    }
});
