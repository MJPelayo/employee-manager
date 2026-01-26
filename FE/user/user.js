// Protect page: redirect if not logged in
if (localStorage.getItem("loggedIn") !== "true") {
    window.location.href = "../login/index.html";
}

// DOM Elements
const table = document.getElementById("employeeTable");
const addBtn = document.getElementById("addBtn");
const logoutBtn = document.getElementById("logoutBtn");
const usernameElement = document.getElementById("username");
const searchInput = document.getElementById("searchInput");
const departmentFilter = document.getElementById("departmentFilter");
const typeFilter = document.getElementById("typeFilter");
const clearFiltersBtn = document.getElementById("clearFilters");
const totalEmployees = document.getElementById("totalEmployees");
const fullTimeCount = document.getElementById("fullTimeCount");
const partTimeCount = document.getElementById("partTimeCount");
const internCount = document.getElementById("internCount");
const deptCount = document.getElementById("deptCount");
const showingCount = document.getElementById("showingCount");
const totalCount = document.getElementById("totalCount");

// Set username
const userEmail = localStorage.getItem("userEmail");
if (usernameElement) {
    const displayName = userEmail ? userEmail.split('@')[0] : "Admin";
    usernameElement.textContent = displayName.charAt(0).toUpperCase() + displayName.slice(1);
}

// Load employees from localStorage
let employees = JSON.parse(localStorage.getItem("employees")) || [];

// Update statistics
function updateStatistics() {
    const total = employees.length;
    const fullTime = employees.filter(emp => emp.employeeType === 'full-time').length;
    const partTime = employees.filter(emp => emp.employeeType === 'part-time').length;
    const interns = employees.filter(emp => emp.employeeType === 'intern').length;
    const departments = [...new Set(employees.map(emp => emp.department))].length;
    
    if (totalEmployees) totalEmployees.textContent = total;
    if (fullTimeCount) fullTimeCount.textContent = fullTime;
    if (partTimeCount) partTimeCount.textContent = partTime;
    if (internCount) internCount.textContent = interns;
    if (deptCount) deptCount.textContent = departments;
    if (totalCount) totalCount.textContent = total;
}

// Filter employees based on search and filters
function filterEmployees() {
    const searchTerm = searchInput ? searchInput.value.toLowerCase().trim() : '';
    const selectedDept = departmentFilter ? departmentFilter.value : '';
    const selectedType = typeFilter ? typeFilter.value : '';
    
    let filtered = employees;
    
    // Apply search filter
    if (searchTerm) {
        filtered = filtered.filter(emp => 
            emp.employeeId.toLowerCase().includes(searchTerm) ||
            emp.firstName.toLowerCase().includes(searchTerm) ||
            emp.lastName.toLowerCase().includes(searchTerm) ||
            emp.department.toLowerCase().includes(searchTerm) ||
            (emp.employeeType && emp.employeeType.toLowerCase().includes(searchTerm))
        );
    }
    
    // Apply department filter
    if (selectedDept) {
        filtered = filtered.filter(emp => emp.department === selectedDept);
    }
    
    // Apply employee type filter
    if (selectedType) {
        filtered = filtered.filter(emp => emp.employeeType === selectedType);
    }
    
    return filtered;
}

// Function to render table
function renderTable() {
    const filteredEmployees = filterEmployees();
    
    if (showingCount) showingCount.textContent = filteredEmployees.length;
    if (totalCount) totalCount.textContent = employees.length;
    
    table.innerHTML = "";
    
    if (filteredEmployees.length === 0) {
        table.innerHTML = `
            <tr>
                <td colspan="6" class="empty-state">
                    <i class="fas fa-users"></i>
                    <p>No employees found</p>
                    <p>Try adjusting your search or filters</p>
                </td>
            </tr>
        `;
        return;
    }
    
    filteredEmployees.forEach((emp, index) => {
        // Determine employee type badge class
        let typeClass = 'full-time';
        let typeText = 'Full-time';
        
        if (emp.employeeType === 'part-time') {
            typeClass = 'part-time';
            typeText = 'Part-time';
        } else if (emp.employeeType === 'intern') {
            typeClass = 'intern';
            typeText = 'Intern';
        }
        
        const originalIndex = employees.indexOf(emp);
        
        table.innerHTML += `
            <tr>
                <td>${index + 1}</td>
                <td><strong>${emp.employeeId}</strong></td>
                <td>${emp.firstName} ${emp.lastName}</td>
                <td><span class="dept-badge">${emp.department}</span></td>
                <td><span class="employee-type ${typeClass}">${typeText}</span></td>
                <td>
                    <div class="actions">
                        <button onclick="viewEmployee(${originalIndex})" class="action-btn view" title="View">
                            <i class="fas fa-eye"></i>
                        </button>
                        <button onclick="editEmployee(${originalIndex})" class="action-btn edit" title="Edit">
                            <i class="fas fa-edit"></i>
                        </button>
                        <button onclick="deleteEmployee(${originalIndex})" class="action-btn delete" title="Delete">
                            <i class="fas fa-trash"></i>
                        </button>
                    </div>
                </td>
            </tr>
        `;
    });
}

// Initialize table and stats
renderTable();
updateStatistics();

// Event listeners for filtering
if (searchInput) {
    searchInput.addEventListener('input', renderTable);
}

if (departmentFilter) {
    departmentFilter.addEventListener('change', renderTable);
}

if (typeFilter) {
    typeFilter.addEventListener('change', renderTable);
}

// Clear all filters
if (clearFiltersBtn) {
    clearFiltersBtn.addEventListener('click', () => {
        if (searchInput) searchInput.value = '';
        if (departmentFilter) departmentFilter.value = '';
        if (typeFilter) typeFilter.value = '';
        renderTable();
    });
}

// Add new employee
if (addBtn) {
    addBtn.addEventListener("click", () => {
        localStorage.removeItem("editIndex");
        window.location.href = "../form/index.html";
    });
}

// Edit existing employee
window.editEmployee = (index) => {
    localStorage.setItem("editIndex", index);
    window.location.href = "../form/index.html";
};

// Delete employee
window.deleteEmployee = (index) => {
    const employee = employees[index];
    if (confirm(`Are you sure you want to delete ${employee.firstName} ${employee.lastName}?`)) {
        employees.splice(index, 1);
        localStorage.setItem("employees", JSON.stringify(employees));
        renderTable();
        updateStatistics();
    }
};

// View details
window.viewEmployee = (index) => {
    localStorage.setItem("viewIndex", index);
    window.location.href = "../details/index.html";
};

// Logout
if (logoutBtn) {
    logoutBtn.addEventListener("click", () => {
        if (confirm("Are you sure you want to logout?")) {
            localStorage.removeItem("loggedIn");
            localStorage.removeItem("userEmail");
            window.location.href = "../login/index.html";
        }
    });
}