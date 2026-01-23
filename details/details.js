// Protect page
if (localStorage.getItem("loggedIn") !== "true") {
    window.location.href = "../login/index.html";
}

const employees = JSON.parse(localStorage.getItem("employees")) || [];
const index = localStorage.getItem("viewIndex");

if (index === null || !employees[index]) {
    window.location.href = "user.html";
}

// Get employee data
const employee = employees[index];

// Display details
document.getElementById("employeeId").textContent = employee.employeeId;
document.getElementById("firstName").textContent = employee.firstName;
document.getElementById("lastName").textContent = employee.lastName;
document.getElementById("department").textContent = employee.department;
document.getElementById("fullName").textContent = `${employee.firstName} ${employee.lastName}`;

// Edit button
document.getElementById("editBtn").addEventListener("click", () => {
    localStorage.setItem("editIndex", index);
    window.location.href = "form.html";
});

// Delete button
document.getElementById("deleteBtn").addEventListener("click", () => {
    if (confirm(`Are you sure you want to delete ${employee.firstName} ${employee.lastName}?`)) {
        employees.splice(index, 1);
        localStorage.setItem("employees", JSON.stringify(employees));
        localStorage.removeItem("viewIndex");
        window.location.href = "user.html";
    }
});

// Back button
document.getElementById("backBtn").addEventListener("click", () => {
    localStorage.removeItem("viewIndex");
    window.location.href = "user.html";
});