const loginForm = document.getElementById("loginForm");
const errorMessage = document.getElementById("errorMessage");

loginForm.addEventListener("submit", function (event) {
    event.preventDefault(); // Stop form from refreshing page

    const username = document.getElementById("username").value.trim();
    const password = document.getElementById("password").value.trim();

    // Validation
    if (username === "" || password === "") {
        errorMessage.textContent = "Please enter both username and password.";
        return;
    }

    // Clear error if valid
    errorMessage.textContent = "";

    // Temporary success behavior
    alert("Login successful!");

    // Later you can redirect:
    // window.location.href = "../user/index.html";
});
