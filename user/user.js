// Protect page
if (localStorage.getItem("loggedIn") !== "true") {
    window.location.href = "../login/index.html";
}

// Logout
document.getElementById("logoutBtn").addEventListener("click", () => {
    localStorage.removeItem("loggedIn");
    window.location.href = "../login/index.html";
});
