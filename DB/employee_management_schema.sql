
-- ============================================
-- STEP 1: CREATE DATABASE AND CONNECT
-- ============================================



-- ============================================
-- STEP 2: CREATE EMPLOYEES TABLE
-- ============================================

DROP TABLE IF EXISTS employees CASCADE;

-- Simple employees table matching your web form
CREATE TABLE employees (
    id SERIAL PRIMARY KEY,
    employee_id VARCHAR(20) UNIQUE NOT NULL,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone VARCHAR(20),
    gender VARCHAR(10),
    department VARCHAR(50) NOT NULL,
    employee_type VARCHAR(20) NOT NULL CHECK (employee_type IN ('full-time', 'part-time', 'intern')),
    profile_picture TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- ============================================
-- STEP 3: CREATE INDEXES FOR PERFORMANCE
-- ============================================

CREATE INDEX idx_employee_id ON employees(employee_id);
CREATE INDEX idx_employee_department ON employees(department);
CREATE INDEX idx_employee_type ON employees(employee_type);
CREATE INDEX idx_employee_email ON employees(email);
CREATE INDEX idx_employee_name ON employees(last_name, first_name);

-- ============================================
-- STEP 4: CREATE TRIGGER FOR UPDATED AT
-- ============================================

CREATE OR REPLACE FUNCTION update_updated_at_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = CURRENT_TIMESTAMP;
    RETURN NEW;
END;
$$ language 'plpgsql';

CREATE TRIGGER update_employees_updated_at 
    BEFORE UPDATE ON employees 
    FOR EACH ROW 
    EXECUTE FUNCTION update_updated_at_column();

-- ============================================
-- STEP 5: INSERT SAMPLE DATA
-- (Matching your demo credentials and web app)
-- ============================================

-- Sample employees matching your web application's demo data
INSERT INTO employees (employee_id, first_name, last_name, email, phone, gender, department, employee_type) VALUES
('EMP001', 'Admin', 'User', 'admin@employee.com', '(123) 456-7890', 'Male', 'IT', 'full-time'),
('EMP002', 'John', 'Doe', 'john@employee.com', '(234) 567-8901', 'Male', 'IT', 'full-time'),
('EMP003', 'Jane', 'Smith', 'jane@employee.com', '(345) 678-9012', 'Female', 'HR', 'part-time'),
('EMP004', 'Bob', 'Johnson', 'bob@employee.com', '(456) 789-0123', 'Male', 'IT', 'intern'),
('EMP005', 'Alice', 'Williams', 'alice@employee.com', '(567) 890-1234', 'Female', 'FIN', 'full-time'),
('EMP006', 'Charlie', 'Brown', 'charlie@employee.com', '(678) 901-2345', 'Male', 'MKT', 'part-time'),
('EMP007', 'David', 'Miller', 'david@employee.com', '(789) 012-3456', 'Male', 'ENG', 'full-time');

-- ============================================
-- STEP 6: CREATE VIEWS FOR WEB APPLICATION
-- ============================================

-- View for employee listing (matches your user.html table)
CREATE VIEW vw_employee_list AS
SELECT 
    id,
    employee_id,
    first_name,
    last_name,
    department,
    employee_type,
    email,
    phone,
    gender,
    profile_picture,
    created_at,
    updated_at
FROM employees
ORDER BY last_name, first_name;

-- View for department statistics (matches your stats cards)
CREATE VIEW vw_department_stats AS
SELECT 
    department,
    COUNT(*) as total_employees,
    COUNT(CASE WHEN employee_type = 'full-time' THEN 1 END) as full_time_count,
    COUNT(CASE WHEN employee_type = 'part-time' THEN 1 END) as part_time_count,
    COUNT(CASE WHEN employee_type = 'intern' THEN 1 END) as intern_count
FROM employees
GROUP BY department
ORDER BY department;

-- ============================================
-- STEP 7: STORED PROCEDURES FOR WEB OPERATIONS
-- ============================================

-- Add new employee (matches your form.js)
CREATE OR REPLACE PROCEDURE sp_add_employee(
    p_employee_id VARCHAR,
    p_first_name VARCHAR,
    p_last_name VARCHAR,
    p_email VARCHAR,
    p_phone VARCHAR,
    p_gender VARCHAR,
    p_department VARCHAR,
    p_employee_type VARCHAR,
    p_profile_picture TEXT DEFAULT NULL
)
LANGUAGE plpgsql
AS $$
BEGIN
    INSERT INTO employees (
        employee_id, 
        first_name, 
        last_name, 
        email, 
        phone, 
        gender, 
        department, 
        employee_type,
        profile_picture
    ) VALUES (
        p_employee_id,
        p_first_name,
        p_last_name,
        p_email,
        p_phone,
        p_gender,
        p_department,
        p_employee_type,
        p_profile_picture
    );
END;
$$;

-- Update employee (matches your form.js edit functionality)
CREATE OR REPLACE PROCEDURE sp_update_employee(
    p_employee_id VARCHAR,
    p_first_name VARCHAR,
    p_last_name VARCHAR,
    p_email VARCHAR,
    p_phone VARCHAR,
    p_gender VARCHAR,
    p_department VARCHAR,
    p_employee_type VARCHAR,
    p_profile_picture TEXT DEFAULT NULL
)
LANGUAGE plpgsql
AS $$
BEGIN
    UPDATE employees 
    SET 
        first_name = p_first_name,
        last_name = p_last_name,
        email = p_email,
        phone = p_phone,
        gender = p_gender,
        department = p_department,
        employee_type = p_employee_type,
        profile_picture = COALESCE(p_profile_picture, profile_picture)
    WHERE employee_id = p_employee_id;
END;
$$;

-- Delete employee (matches your delete functionality)
CREATE OR REPLACE PROCEDURE sp_delete_employee(
    p_employee_id VARCHAR
)
LANGUAGE plpgsql
AS $$
BEGIN
    DELETE FROM employees WHERE employee_id = p_employee_id;
END;
$$;

-- Search employees (matches your filter functionality)
CREATE OR REPLACE FUNCTION fn_search_employees(
    p_search_term VARCHAR DEFAULT NULL,
    p_department VARCHAR DEFAULT NULL,
    p_employee_type VARCHAR DEFAULT NULL
)
RETURNS TABLE(
    id INTEGER,
    employee_id VARCHAR,
    first_name VARCHAR,
    last_name VARCHAR,
    department VARCHAR,
    employee_type VARCHAR,
    email VARCHAR,
    phone VARCHAR,
    gender VARCHAR
) 
LANGUAGE plpgsql
AS $$
BEGIN
    RETURN QUERY
    SELECT 
        e.id,
        e.employee_id,
        e.first_name,
        e.last_name,
        e.department,
        e.employee_type,
        e.email,
        e.phone,
        e.gender
    FROM employees e
    WHERE 
        (p_search_term IS NULL OR 
         e.first_name ILIKE '%' || p_search_term || '%' OR 
         e.last_name ILIKE '%' || p_search_term || '%' OR
         e.employee_id ILIKE '%' || p_search_term || '%' OR
         e.email ILIKE '%' || p_search_term || '%' OR
         e.department ILIKE '%' || p_search_term || '%') AND
        (p_department IS NULL OR e.department = p_department) AND
        (p_employee_type IS NULL OR e.employee_type = p_employee_type)
    ORDER BY e.last_name, e.first_name;
END;
$$;

-- Get employee by ID (matches your view functionality)
CREATE OR REPLACE FUNCTION fn_get_employee_by_id(
    p_employee_id VARCHAR
)
RETURNS TABLE(
    id INTEGER,
    employee_id VARCHAR,
    first_name VARCHAR,
    last_name VARCHAR,
    email VARCHAR,
    phone VARCHAR,
    gender VARCHAR,
    department VARCHAR,
    employee_type VARCHAR,
    profile_picture TEXT,
    created_at TIMESTAMP,
    updated_at TIMESTAMP
) 
LANGUAGE plpgsql
AS $$
BEGIN
    RETURN QUERY
    SELECT 
        e.id,
        e.employee_id,
        e.first_name,
        e.last_name,
        e.email,
        e.phone,
        e.gender,
        e.department,
        e.employee_type,
        e.profile_picture,
        e.created_at,
        e.updated_at
    FROM employees e
    WHERE e.employee_id = p_employee_id;
END;
$$;

-- Get statistics (matches your dashboard stats)
CREATE OR REPLACE FUNCTION fn_get_statistics()
RETURNS TABLE(
    total_employees BIGINT,
    full_time_count BIGINT,
    part_time_count BIGINT,
    intern_count BIGINT,
    department_count BIGINT
) 
LANGUAGE plpgsql
AS $$
BEGIN
    RETURN QUERY
    SELECT 
        COUNT(*) as total_employees,
        COUNT(CASE WHEN employee_type = 'full-time' THEN 1 END) as full_time_count,
        COUNT(CASE WHEN employee_type = 'part-time' THEN 1 END) as part_time_count,
        COUNT(CASE WHEN employee_type = 'intern' THEN 1 END) as intern_count,
        COUNT(DISTINCT department) as department_count
    FROM employees;
END;
$$;

-- ============================================
-- STEP 8: DEMONSTRATION QUERIES
-- ============================================

-- Query 1: Get all employees (like your main table)
-- SELECT * FROM vw_employee_list;

-- Query 2: Get employee by ID (for details page)
-- SELECT * FROM fn_get_employee_by_id('EMP001');

-- Query 3: Search employees (for your filter functionality)
-- SELECT * FROM fn_search_employees('John', 'IT', 'full-time');

-- Query 4: Get statistics (for your dashboard)
-- SELECT * FROM fn_get_statistics();

-- Query 5: Get department stats (for your stats cards)
-- SELECT * FROM vw_department_stats;

-- ============================================
-- STEP 9: TABLE COMMENTS
-- ============================================

COMMENT ON TABLE employees IS 'Employees table matching web application form data';
COMMENT ON COLUMN employees.employee_id IS 'Employee ID (matches form field)';
COMMENT ON COLUMN employees.first_name IS 'First name (matches form field)';
COMMENT ON COLUMN employees.last_name IS 'Last name (matches form field)';
COMMENT ON COLUMN employees.email IS 'Email (matches form field)';
COMMENT ON COLUMN employees.phone IS 'Phone number (matches form field)';
COMMENT ON COLUMN employees.gender IS 'Gender (matches form select)';
COMMENT ON COLUMN employees.department IS 'Department (matches form select: IT, HR, FIN, MKT, OPS, SLS, DSN, ENG)';
COMMENT ON COLUMN employees.employee_type IS 'Employee type (matches form select: full-time, part-time, intern)';
COMMENT ON COLUMN employees.profile_picture IS 'Profile picture URL/base64 (matches form upload)';

-- ============================================
-- FINAL MESSAGE
-- ============================================

DO $$
BEGIN
    RAISE NOTICE '============================================';
    RAISE NOTICE 'EMPLOYEE MANAGEMENT DATABASE CREATED SUCCESSFULLY';
    RAISE NOTICE '============================================';
    RAISE NOTICE '';
    RAISE NOTICE 'Database designed to match your web application exactly:';
    RAISE NOTICE '';
    RAISE NOTICE '1. Table: employees';
    RAISE NOTICE '   - Matches all form fields from your HTML forms');
    RAISE NOTICE '   - Includes profile picture support');
    RAISE NOTICE '';
    RAISE NOTICE '2. Views:';
    RAISE NOTICE '   - vw_employee_list: For your main employee table');
    RAISE NOTICE '   - vw_department_stats: For your statistics cards');
    RAISE NOTICE '';
    RAISE NOTICE '3. Procedures & Functions:';
    RAISE NOTICE '   - sp_add_employee(): Add new employee (form.js)');
    RAISE NOTICE '   - sp_update_employee(): Edit employee (form.js)');
    RAISE NOTICE '   - sp_delete_employee(): Delete employee (user.js)');
    RAISE NOTICE '   - fn_search_employees(): Filter/search (user.js)');
    RAISE NOTICE '   - fn_get_employee_by_id(): View details (details.js)');
    RAISE NOTICE '   - fn_get_statistics(): Dashboard stats (user.js)');
    RAISE NOTICE '';
    RAISE NOTICE '4. Sample Data: 7 employees inserted';
    RAISE NOTICE '   - Admin user: admin@employee.com');
    RAISE NOTICE '   - Various departments and employee types');
    RAISE NOTICE '';
    RAISE NOTICE '============================================';
END $$;

-- ============================================
-- USAGE INSTRUCTIONS
-- ============================================

-- 1. To create the database:
--    CREATE DATABASE employee_management;
--
-- 2. To run this script:
--    psql -U your_username -d employee_management -f employee_management_simple.sql
--
-- 3. Test queries:
--    SELECT * FROM vw_employee_list;
--    SELECT * FROM fn_get_statistics();
--    CALL sp_add_employee('EMP008', 'Sarah', 'Jones', 'sarah@employee.com',
--                         '(901) 234-5678', 'Female', 'HR', 'full-time');
--    SELECT * FROM fn_search_employees('Sarah');
--
-- 4. To backup:
--    pg_dump -U your_username -d employee_management -f backup.sql