// Protect page: redirect if not logged in
if (localStorage.getItem("loggedIn") !== "true") {
    window.location.href = "../login/index.html";
}

// DOM Elements
const table = document.getElementById("employeeTable");
const addBtn = document.getElementById("addBtn");
const logoutBtn = document.getElementById("logoutBtn");
const usernameElement = document.getElementById("username");

// Set username
usernameElement.textContent = localStorage.getItem("username") || "User";

// Load employees from localStorage
let employees = JSON.parse(localStorage.getItem("employees")) || [];

// Function to render table
function renderTable() {
    table.innerHTML = "";
    
    if (employees.length === 0) {
        table.innerHTML = `
            <tr>
                <td colspan="5" class="message">
                    No employees found. Click "Add Employee" to add your first employee.
                </td>
            </tr>
        `;
        return;
    }
    
    employees.forEach((emp, index) => {
        table.innerHTML += `
            <tr>
                <td>${emp.employeeId}</td>
                <td>${emp.firstName} ${emp.lastName}</td>
                <td>${emp.department}</td>
                <td>
                    <div class="actions">
                        <button onclick="viewEmployee(${index})" class="btn btn-primary btn-sm">View</button>
                        <button onclick="editEmployee(${index})" class="btn btn-sm" style="background: #ffc107; color: white;">Edit</button>
                        <button onclick="deleteEmployee(${index})" class="btn btn-danger btn-sm">Delete</button>
                    </div>
                </td>
            </tr>
        `;
    });
}

// Initial render
renderTable();

// Add new employee
addBtn.addEventListener("click", () => {
    localStorage.removeItem("editIndex");
    window.location.href = "../form/index.html";
});

// Edit existing employee
window.editEmployee = (index) => {
    localStorage.setItem("editIndex", index);
    window.location.href = "../form/index.html";
};

// Delete employee
window.deleteEmployee = (index) => {
    if (confirm("Are you sure you want to delete this employee?")) {
        employees.splice(index, 1);
        localStorage.setItem("employees", JSON.stringify(employees));
        renderTable();
    }
};

// View details
window.viewEmployee = (index) => {
    localStorage.setItem("viewIndex", index);
    window.location.href = "../details/index.html";
};

// Logout
logoutBtn.addEventListener("click", () => {
    if (confirm("Are you sure you want to logout?")) {
        localStorage.removeItem("loggedIn");
        localStorage.removeItem("username");
        window.location.href = "../login/index.html";
    }
});