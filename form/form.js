const nameInput = document.getElementById("name");
const deptInput = document.getElementById("department");
const error = document.getElementById("error");

let employees = JSON.parse(localStorage.getItem("employees")) || [];
const editIndex = localStorage.getItem("editIndex");

// Load data if editing
if (editIndex !== null) {
    nameInput.value = employees[editIndex].name;
    deptInput.value = employees[editIndex].department;
}

// Save
document.getElementById("saveBtn").addEventListener("click", () => {
    const name = nameInput.value.trim();
    const department = deptInput.value.trim();

    if (name === "" || department === "") {
        error.textContent = "All fields are required.";
        return;
    }

    if (editIndex !== null) {
        employees[editIndex] = { name, department };
        localStorage.removeItem("editIndex");
    } else {
        employees.push({ name, department });
    }

    localStorage.setItem("employees", JSON.stringify(employees));
    window.location.href = "../user/index.html";
});

// Cancel
document.getElementById("cancelBtn").addEventListener("click", () => {
    window.location.href = "../user/index.html";
});
