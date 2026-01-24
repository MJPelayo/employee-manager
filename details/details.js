// [file name]: details.js
// Protect page: redirect if not logged in
if (localStorage.getItem("loggedIn") !== "true") {
    window.location.href = "../login/index.html";
}

// DOM Elements
const backToListBtn = document.getElementById("backToListBtn");
const editBtn = document.getElementById("editBtn");
const deleteBtn = document.getElementById("deleteBtn");
const profilePicture = document.getElementById("profilePicture");
const profileImage = document.getElementById("profileImage");
const pageTitle = document.getElementById("pageTitle");
const pageSubtitle = document.getElementById("pageSubtitle");

// Employee data elements
const employeeName = document.getElementById("employeeName");
const employeeIdDisplay = document.getElementById("employeeIdDisplay");
const employeeIdValue = document.getElementById("employeeIdValue");
const employeeTypeBadge = document.getElementById("employeeTypeBadge");
const departmentBadge = document.getElementById("departmentBadge");
const joinDate = document.getElementById("joinDate");
const fullName = document.getElementById("fullName");
const gender = document.getElementById("gender");
const email = document.getElementById("email");
const phone = document.getElementById("phone");
const employmentType = document.getElementById("employmentType");
const employmentDept = document.getElementById("employmentDept");
const systemEmployeeId = document.getElementById("systemEmployeeId");
const createdAt = document.getElementById("createdAt");
const updatedAt = document.getElementById("updatedAt");

// Load employees from localStorage
let employees = JSON.parse(localStorage.getItem("employees")) || [];
const viewIndex = localStorage.getItem("viewIndex");

// Check if employee exists
if (viewIndex === null || !employees[viewIndex]) {
    window.location.href = "../user/index.html";
}

// Get employee data
const employee = employees[viewIndex];

// Format date function
function formatDate(dateString) {
    const date = new Date(dateString);
    return date.toLocaleDateString('en-US', {
        year: 'numeric',
        month: 'long',
        day: 'numeric'
    });
}

// Format phone number
function formatPhone(phoneNumber) {
    // Remove all non-digits
    const cleaned = phoneNumber.replace(/\D/g, '');
    
    // Check if the number is 10 digits
    if (cleaned.length === 10) {
        return `(${cleaned.substring(0, 3)}) ${cleaned.substring(3, 6)}-${cleaned.substring(6)}`;
    }
    
    // Return original if not 10 digits
    return phoneNumber;
}

// Set badge class based on employee type
function getEmployeeTypeBadgeClass(type) {
    switch(type) {
        case 'full-time':
            return 'badge-full-time';
        case 'part-time':
            return 'badge-part-time';
        case 'intern':
            return 'badge-intern';
        default:
            return 'badge-department';
    }
}

// Get department display name
function getDepartmentDisplayName(deptCode) {
    const departments = {
        'HR': 'Human Resources',
        'IT': 'Information Technology',
        'Finance': 'Finance',
        'Marketing': 'Marketing',
        'Operations': 'Operations',
        'Sales': 'Sales',
        'Design': 'Design',
        'Engineering': 'Engineering'
    };
    return departments[deptCode] || deptCode;
}

// Display employee data
function displayEmployeeData() {
    // Set page title and subtitle
    pageTitle.innerHTML = `<i class="fas fa-user-circle"></i> ${employee.firstName} ${employee.lastName}`;
    pageSubtitle.textContent = `${employee.department} Department`;
    
    // Profile section
    employeeName.textContent = `${employee.firstName} ${employee.lastName}`;
    employeeIdDisplay.textContent = `ID: ${employee.employeeId}`;
    employeeIdValue.textContent = employee.employeeId;
    
    // Profile picture
    if (employee.profilePicture) {
        profileImage.src = employee.profilePicture;
        profilePicture.classList.add('has-image');
    }
    
    // Quick info
    employeeTypeBadge.textContent = employee.employeeType === 'full-time' ? 'Full-time' : 
                                   employee.employeeType === 'part-time' ? 'Part-time' : 'Intern';
    employeeTypeBadge.className = `detail-badge ${getEmployeeTypeBadgeClass(employee.employeeType)}`;
    
    departmentBadge.textContent = employee.department;
    joinDate.textContent = formatDate(employee.createdAt);
    
    // Personal information
    fullName.textContent = `${employee.firstName} ${employee.lastName}`;
    gender.textContent = employee.gender.charAt(0).toUpperCase() + employee.gender.slice(1);
    
    // Contact information
    email.textContent = employee.email;
    phone.textContent = formatPhone(employee.phone);
    
    // Employment details
    employmentType.textContent = employee.employeeType === 'full-time' ? 'Full-time' : 
                                employee.employeeType === 'part-time' ? 'Part-time' : 'Intern';
    employmentType.className = `detail-badge ${getEmployeeTypeBadgeClass(employee.employeeType)}`;
    
    employmentDept.textContent = getDepartmentDisplayName(employee.department);
    
    // System information
    systemEmployeeId.textContent = employee.employeeId;
    
    // Timeline
    createdAt.textContent = formatDate(employee.createdAt);
    updatedAt.textContent = formatDate(employee.updatedAt);
}

// Initialize the page
displayEmployeeData();

// Event Listeners
backToListBtn.addEventListener('click', () => {
    localStorage.removeItem("viewIndex");
    window.location.href = "../user/index.html";
});

editBtn.addEventListener('click', () => {
    localStorage.setItem("editIndex", viewIndex);
    window.location.href = "../form/index.html";
});

deleteBtn.addEventListener('click', () => {
    if (confirm(`Are you sure you want to delete ${employee.firstName} ${employee.lastName}? This action cannot be undone.`)) {
        employees.splice(viewIndex, 1);
        localStorage.setItem("employees", JSON.stringify(employees));
        localStorage.removeItem("viewIndex");
        
        // Show success message
        alert('Employee deleted successfully!');
        window.location.href = "../user/index.html";
    }
});

// Allow Escape key to go back
document.addEventListener('keydown', function(e) {
    if (e.key === 'Escape') {
        window.history.back();
    }
});