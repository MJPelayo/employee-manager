// Protect page: redirect if not logged in
if (localStorage.getItem("loggedIn") !== "true") {
    window.location.href = "../login/index.html";
}

const table = document.getElementById("employeeTable");

// Load employees from localStorage or empty array
let employees = JSON.parse(localStorage.getItem("employees")) || [];

// Function to render table
function renderTable() {
    table.innerHTML = "";
    employees.forEach((emp, index) => {
        table.innerHTML += `
            <tr>
                <td>${emp.name}</td>
                <td>${emp.department}</td>
                <td>
                    <button onclick="viewEmployee(${index})">View</button>
                    <button onclick="editEmployee(${index})">Edit</button>
                    <button onclick="deleteEmployee(${index})">Delete</button>
                </td>
            </tr>
        `;
    });
}

renderTable();

// Add new employee
document.getElementById("addBtn").addEventListener("click", () => {
    localStorage.removeItem("editIndex"); // Clear edit index for new employee
    window.location.href = "../form/index.html";
});

// Edit existing employee
window.editEmployee = (index) => {
    localStorage.setItem("editIndex", index);
    window.location.href = "../form/index.html";
};

// Delete employee
window.deleteEmployee = (index) => {
    employees.splice(index, 1); // Remove from array
    localStorage.setItem("employees", JSON.stringify(employees)); // Save updated list
    renderTable();
};

// View details
window.viewEmployee = (index) => {
    localStorage.setItem("viewIndex", index);
    window.location.href = "../details/index.html";
};

// Logout
document.getElementById("logoutBtn").addEventListener("click", () => {
    localStorage.removeItem("loggedIn");
    window.location.href = "../login/index.html";
});
