// Protect page
if (localStorage.getItem("loggedIn") !== "true") {
    window.location.href = "../login/index.html";
}

const table = document.getElementById("employeeTable");
let employees = JSON.parse(localStorage.getItem("employees")) || [];

// Render table
function renderTable() {
    table.innerHTML = "";
    employees.forEach((emp, index) => {
        table.innerHTML += `
            <tr>
                <td>${emp.name}</td>
                <td>${emp.department}</td>
                <td>
                    <button onclick="editEmployee(${index})">Edit</button>
                    <button onclick="deleteEmployee(${index})">Delete</button>
                </td>
            </tr>
        `;
    });
}

renderTable();

// Add
document.getElementById("addBtn").addEventListener("click", () => {
    localStorage.removeItem("editIndex");
    window.location.href = "../form/index.html";
});

// Edit
window.editEmployee = (index) => {
    localStorage.setItem("editIndex", index);
    window.location.href = "../form/index.html";
};

// Delete
window.deleteEmployee = (index) => {
    employees.splice(index, 1);
    localStorage.setItem("employees", JSON.stringify(employees));
    renderTable();
};

// Logout
document.getElementById("logoutBtn").addEventListener("click", () => {
    localStorage.removeItem("loggedIn");
    window.location.href = "../login/index.html";
});
