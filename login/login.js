const form = document.getElementById("loginForm");
const error = document.getElementById("error");
const password = document.getElementById("password");
const showPassword = document.getElementById("showPassword");

// Show / Hide Password
showPassword.addEventListener("change", () => {
    password.type = showPassword.checked ? "text" : "password";
});

// Simple login validation
form.addEventListener("submit", (e) => {
    e.preventDefault();

    const username = document.getElementById("username").value.trim();
    const pwd = password.value.trim();

    if (username === "" || pwd === "") {
        error.textContent = "All fields are required.";
        return;
    }

    // Basic validation (in real app, this would be server-side)
    if (username === "admin" && pwd === "admin123") {
        localStorage.setItem("loggedIn", "true");
        localStorage.setItem("username", username);
        error.textContent = "";
        window.location.href = "../user/index.html";
    } else {
        error.textContent = "Invalid username or password.";
    }
});

// Clear error when user starts typing
document.getElementById("username").addEventListener("input", () => {
    error.textContent = "";
});

password.addEventListener("input", () => {
    error.textContent = "";
});