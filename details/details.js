// Protect page
if (localStorage.getItem("loggedIn") !== "true") {
    window.location.href = "../login/index.html";
}

const employees = JSON.parse(localStorage.getItem("employees")) || [];
const index = localStorage.getItem("viewIndex");

if (index === null || !employees[index]) {
    window.location.href = "../user/index.html";
}

// Display details
document.getElementById("name").textContent = employees[index].name;
document.getElementById("department").textContent = employees[index].department;

// Edit
document.getElementById("editBtn").addEventListener("click", () => {
    localStorage.setItem("editIndex", index);
    window.location.href = "../form/index.html";
});

// Delete
document.getElementById("deleteBtn").addEventListener("click", () => {
    employees.splice(index, 1);
    localStorage.setItem("employees", JSON.stringify(employees));
    localStorage.removeItem("viewIndex");
    window.location.href = "../user/index.html";
});

// Exit
document.getElementById("exitBtn").addEventListener("click", () => {
    localStorage.removeItem("viewIndex");
    window.location.href = "../user/index.html";
});
