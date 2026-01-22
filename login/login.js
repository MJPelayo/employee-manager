const form = document.getElementById("loginForm");
const error = document.getElementById("error");
const password = document.getElementById("password");
const showPassword = document.getElementById("showPassword");

// Show / Hide Password
showPassword.addEventListener("change", () => {
    password.type = showPassword.checked ? "text" : "password";
});

// Login logic
form.addEventListener("submit", (e) => {
    e.preventDefault();

    const username = document.getElementById("username").value.trim();
    const pwd = password.value.trim();

    if (username === "" || pwd === "") {
        error.textContent = "All fields are required.";
        return;
    }

    localStorage.setItem("loggedIn", "true");
    window.location.href = "../user/index.html";
});
