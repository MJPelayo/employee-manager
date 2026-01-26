document.addEventListener('DOMContentLoaded', function() {
    const form = document.getElementById("loginForm");
    const passwordInput = document.getElementById("password");
    const showPasswordCheckbox = document.getElementById("showPassword");
    const emailInput = document.getElementById("email");
    const loginBtn = document.querySelector('.login-btn');

    // Show/Hide Password
    showPasswordCheckbox.addEventListener("change", () => {
        passwordInput.type = showPasswordCheckbox.checked ? "text" : "password";
    });

    // Form validation
    function validateEmail(email) {
        const re = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        return re.test(email);
    }

    // Form submission
    form.addEventListener("submit", (e) => {
        e.preventDefault();

        const email = emailInput.value.trim();
        const password = passwordInput.value.trim();

        // Validation
        if (email === "" || password === "") {
            alert("All fields are required.");
            return;
        }

        if (!validateEmail(email)) {
            alert("Please enter a valid email address.");
            return;
        }

        if (password.length < 6) {
            alert("Password must be at least 6 characters.");
            return;
        }

        // Show loading state
        const originalText = loginBtn.innerHTML;
        loginBtn.innerHTML = '<i class="fas fa-spinner fa-spin"></i> LOGGING IN...';
        loginBtn.disabled = true;

        // Simulate API call
        setTimeout(() => {
            // Demo login credentials
            if ((email === "admin@employee.com" || email === "admin") && password === "admin123") {
                // Login successful
                localStorage.setItem("loggedIn", "true");
                localStorage.setItem("userEmail", email);
                
                // Success state
                loginBtn.innerHTML = '<i class="fas fa-check"></i> SUCCESS!';
                loginBtn.style.background = "linear-gradient(135deg, #28a745 0%, #1e7e34 100%)";
                
                // Redirect
                setTimeout(() => {
                    window.location.href = "../user/index.html";
                }, 1000);
            } else {
                // Login failed
                alert("Invalid email or password. Try: admin@employee.com / admin123");
                loginBtn.innerHTML = originalText;
                loginBtn.disabled = false;
            }
        }, 1500);
    });

    // Real-time validation indicators
    emailInput.addEventListener('input', function() {
        if (this.value && !validateEmail(this.value)) {
            this.style.borderColor = '#dc3545';
        } else if (this.value) {
            this.style.borderColor = '#28a745';
        } else {
            this.style.borderColor = '#e0e0e0';
        }
    });

    passwordInput.addEventListener('input', function() {
        if (this.value && this.value.length < 6) {
            this.style.borderColor = '#dc3545';
        } else if (this.value) {
            this.style.borderColor = '#28a745';
        } else {
            this.style.borderColor = '#e0e0e0';
        }
    });

    // Pre-fill demo credentials for testing
    const urlParams = new URLSearchParams(window.location.search);
    if (urlParams.get('demo') === 'true') {
        emailInput.value = 'admin@employee.com';
        passwordInput.value = 'admin123';
    }
});