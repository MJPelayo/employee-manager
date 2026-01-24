-- ============================================
-- EMPLOYEE MANAGEMENT SYSTEM DATABASE SCHEMA
-- PostgreSQL Database for C++ Employee System
-- Matches the C++ class hierarchy exactly
-- ============================================

-- ============================================
-- STEP 1: CREATE DATABASE AND CONNECT
-- ============================================

-- Note: Run these commands separately or in psql
-- CREATE DATABASE employee_management;
-- \c employee_management;

-- ============================================
-- STEP 2: CREATE BASE EMPLOYEES TABLE
-- (Matches Employee base class)
-- ============================================

-- Drop existing tables if they exist (for clean setup)
DROP TABLE IF EXISTS employee_contacts CASCADE;
DROP TABLE IF EXISTS employment_history CASCADE;
DROP TABLE IF EXISTS employee_addresses CASCADE;
DROP TABLE IF EXISTS departments CASCADE;
DROP TABLE IF EXISTS intern_employees CASCADE;
DROP TABLE IF EXISTS part_time_employees CASCADE;
DROP TABLE IF EXISTS full_time_employees CASCADE;
DROP TABLE IF EXISTS base_employees CASCADE;
DROP FUNCTION IF EXISTS update_updated_at_column() CASCADE;
DROP FUNCTION IF EXISTS fn_get_employee_stats() CASCADE;
DROP VIEW IF EXISTS vw_employee_directory CASCADE;
DROP VIEW IF EXISTS vw_department_summary CASCADE;
DROP VIEW IF EXISTS vw_all_employees CASCADE;

-- Base employees table (common attributes for all employee types)
CREATE TABLE base_employees (
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

-- Indexes for base_employees
CREATE INDEX idx_base_emp_id ON base_employees(employee_id);
CREATE INDEX idx_base_dept ON base_employees(department);
CREATE INDEX idx_base_type ON base_employees(employee_type);
CREATE INDEX idx_base_email ON base_employees(email);
CREATE INDEX idx_base_name ON base_employees(last_name, first_name);

-- ============================================
-- STEP 3: CREATE SPECIFIC EMPLOYEE TYPE TABLES
-- ============================================

-- Full-time employees table (matches FullTimeEmployee class)
CREATE TABLE full_time_employees (
    employee_id VARCHAR(20) PRIMARY KEY REFERENCES base_employees(employee_id) ON DELETE CASCADE,
    
    -- Specific fields for full-time employees
    salary DECIMAL(10,2) NOT NULL CHECK (salary > 0),
    annual_bonus DECIMAL(10,2) DEFAULT 0,
    
    -- Benefits
    health_insurance VARCHAR(100),
    retirement_plan VARCHAR(100),
    
    -- Time off
    vacation_days INTEGER DEFAULT 20 CHECK (vacation_days >= 0),
    sick_days INTEGER DEFAULT 10 CHECK (sick_days >= 0),
    
    -- Additional fields
    job_title VARCHAR(100),
    employment_status VARCHAR(20) DEFAULT 'active' CHECK (employment_status IN ('active', 'probation', 'on-leave', 'terminated')),
    
    -- Work schedule
    work_hours_per_week INTEGER DEFAULT 40 CHECK (work_hours_per_week > 0),
    overtime_eligible BOOLEAN DEFAULT TRUE,
    
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Part-time employees table (matches PartTimeEmployee class)
CREATE TABLE part_time_employees (
    employee_id VARCHAR(20) PRIMARY KEY REFERENCES base_employees(employee_id) ON DELETE CASCADE,
    
    -- Specific fields for part-time employees
    hourly_rate DECIMAL(8,2) NOT NULL CHECK (hourly_rate > 0),
    
    -- Schedule
    hours_per_week INTEGER DEFAULT 20 CHECK (hours_per_week > 0 AND hours_per_week <= 35),
    flexible_schedule BOOLEAN DEFAULT TRUE,
    
    -- Work arrangement
    work_arrangement VARCHAR(50) DEFAULT 'regular' CHECK (work_arrangement IN ('regular', 'contract', 'temporary', 'seasonal')),
    
    -- Benefits
    benefits_eligible BOOLEAN DEFAULT FALSE,
    paid_time_off_hours DECIMAL(6,2) DEFAULT 0,
    
    -- Additional fields
    max_hours_per_week INTEGER DEFAULT 30 CHECK (max_hours_per_week <= 35),
    shift_preference VARCHAR(50),
    
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Intern employees table (matches InternEmployee class)
CREATE TABLE intern_employees (
    employee_id VARCHAR(20) PRIMARY KEY REFERENCES base_employees(employee_id) ON DELETE CASCADE,
    
    -- Specific fields for interns
    internship_duration VARCHAR(50) NOT NULL,
    
    -- Education information
    university VARCHAR(100) NOT NULL,
    degree_program VARCHAR(100),
    major VARCHAR(100),
    
    -- Academic details
    expected_graduation DATE,
    current_year VARCHAR(20),
    gpa DECIMAL(3,2) CHECK (gpa >= 0 AND gpa <= 4.0),
    
    -- Compensation
    stipend DECIMAL(8,2),
    academic_credits BOOLEAN DEFAULT FALSE,
    
    -- Supervision
    supervisor_id VARCHAR(20) REFERENCES base_employees(employee_id),
    mentor_id VARCHAR(20) REFERENCES base_employees(employee_id),
    
    -- Program details
    internship_program VARCHAR(100),
    learning_objectives TEXT,
    
    -- Evaluation
    performance_rating DECIMAL(3,2),
    final_report_submitted BOOLEAN DEFAULT FALSE,
    
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- ============================================
-- STEP 4: CREATE SUPPORTING TABLES
-- ============================================

-- Departments table
CREATE TABLE departments (
    department_code VARCHAR(10) PRIMARY KEY,
    department_name VARCHAR(100) NOT NULL UNIQUE,
    manager_id VARCHAR(20) REFERENCES base_employees(employee_id),
    location VARCHAR(100),
    phone_extension VARCHAR(10),
    email VARCHAR(100),
    budget DECIMAL(15,2),
    established_date DATE DEFAULT CURRENT_DATE,
    active BOOLEAN DEFAULT TRUE
);

-- Employee addresses table
CREATE TABLE employee_addresses (
    id SERIAL PRIMARY KEY,
    employee_id VARCHAR(20) NOT NULL REFERENCES base_employees(employee_id) ON DELETE CASCADE,
    
    -- Address details
    address_type VARCHAR(20) DEFAULT 'home' CHECK (address_type IN ('home', 'work', 'mailing')),
    street_address VARCHAR(255) NOT NULL,
    apartment_unit VARCHAR(50),
    city VARCHAR(50) NOT NULL,
    state VARCHAR(50) NOT NULL,
    zip_code VARCHAR(20) NOT NULL,
    country VARCHAR(50) DEFAULT 'USA',
    
    -- Contact at address
    emergency_contact_name VARCHAR(100),
    emergency_contact_phone VARCHAR(20),
    
    is_primary BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Employment history table
CREATE TABLE employment_history (
    id SERIAL PRIMARY KEY,
    employee_id VARCHAR(20) NOT NULL REFERENCES base_employees(employee_id) ON DELETE CASCADE,
    
    -- Employment details
    position_title VARCHAR(100) NOT NULL,
    department VARCHAR(50) NOT NULL,
    employee_type VARCHAR(20) CHECK (employee_type IN ('full-time', 'part-time', 'intern')),
    
    -- Dates
    start_date DATE NOT NULL,
    end_date DATE,
    
    -- Compensation
    salary DECIMAL(10,2),
    hourly_rate DECIMAL(8,2),
    
    -- Status
    employment_status VARCHAR(20) DEFAULT 'active' CHECK (employment_status IN ('active', 'promoted', 'transferred', 'terminated', 'resigned')),
    
    -- Additional info
    supervisor_id VARCHAR(20) REFERENCES base_employees(employee_id),
    work_location VARCHAR(100),
    
    -- Record keeping
    reason_for_change TEXT,
    created_by VARCHAR(100),
    
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Employee contacts table
CREATE TABLE employee_contacts (
    id SERIAL PRIMARY KEY,
    employee_id VARCHAR(20) NOT NULL REFERENCES base_employees(employee_id) ON DELETE CASCADE,
    
    -- Contact details
    contact_type VARCHAR(20) NOT NULL CHECK (contact_type IN ('emergency', 'spouse', 'doctor', 'reference')),
    contact_name VARCHAR(100) NOT NULL,
    relationship VARCHAR(50),
    phone VARCHAR(20),
    email VARCHAR(100),
    address TEXT,
    
    priority INTEGER DEFAULT 1 CHECK (priority >= 1 AND priority <= 3),
    notes TEXT,
    
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- ============================================
-- STEP 5: CREATE INDEXES FOR PERFORMANCE
-- ============================================

-- Indexes for full_time_employees
CREATE INDEX idx_ft_salary ON full_time_employees(salary);
CREATE INDEX idx_ft_status ON full_time_employees(employment_status);
CREATE INDEX idx_ft_job_title ON full_time_employees(job_title);

-- Indexes for part_time_employees
CREATE INDEX idx_pt_rate ON part_time_employees(hourly_rate);
CREATE INDEX idx_pt_hours ON part_time_employees(hours_per_week);
CREATE INDEX idx_pt_arrangement ON part_time_employees(work_arrangement);

-- Indexes for intern_employees
CREATE INDEX idx_intern_university ON intern_employees(university);
CREATE INDEX idx_intern_graduation ON intern_employees(expected_graduation);
CREATE INDEX idx_intern_supervisor ON intern_employees(supervisor_id);
CREATE INDEX idx_intern_duration ON intern_employees(internship_duration);

-- Indexes for supporting tables
CREATE INDEX idx_address_emp ON employee_addresses(employee_id);
CREATE INDEX idx_address_primary ON employee_addresses(employee_id, is_primary);
CREATE INDEX idx_hist_employee ON employment_history(employee_id);
CREATE INDEX idx_hist_dates ON employment_history(start_date, end_date);
CREATE INDEX idx_hist_department ON employment_history(department);
CREATE INDEX idx_contacts_emp ON employee_contacts(employee_id);
CREATE INDEX idx_contacts_type ON employee_contacts(contact_type);

-- ============================================
-- STEP 6: CREATE TRIGGERS FOR AUTOMATIC UPDATES
-- ============================================

-- Function to update updated_at timestamp
CREATE OR REPLACE FUNCTION update_updated_at_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = CURRENT_TIMESTAMP;
    RETURN NEW;
END;
$$ language 'plpgsql';

-- Apply triggers to all tables
CREATE TRIGGER update_base_employees_updated_at 
    BEFORE UPDATE ON base_employees 
    FOR EACH ROW 
    EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_full_time_updated_at 
    BEFORE UPDATE ON full_time_employees 
    FOR EACH ROW 
    EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_part_time_updated_at 
    BEFORE UPDATE ON part_time_employees 
    FOR EACH ROW 
    EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_intern_updated_at 
    BEFORE UPDATE ON intern_employees 
    FOR EACH ROW 
    EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_addresses_updated_at 
    BEFORE UPDATE ON employee_addresses 
    FOR EACH ROW 
    EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_contacts_updated_at 
    BEFORE UPDATE ON employee_contacts 
    FOR EACH ROW 
    EXECUTE FUNCTION update_updated_at_column();

-- ============================================
-- STEP 7: INSERT SAMPLE DATA
-- ============================================

-- Populate departments table
INSERT INTO departments (department_code, department_name, location) VALUES
('IT', 'Information Technology', 'Building A, Floor 3'),
('HR', 'Human Resources', 'Building B, Floor 2'),
('FIN', 'Finance', 'Building C, Floor 4'),
('MKT', 'Marketing', 'Building D, Floor 1'),
('OPS', 'Operations', 'Building E, Floor 2'),
('SLS', 'Sales', 'Building F, Floor 3'),
('DSN', 'Design', 'Building G, Floor 1'),
('ENG', 'Engineering', 'Building H, Floor 4');

-- Insert base employee records (matching C++ sample data)
INSERT INTO base_employees (employee_id, first_name, last_name, email, phone, gender, department, employee_type) VALUES
('EMP001', 'John', 'Doe', 'john@employee.com', '(123) 456-7890', 'Male', 'IT', 'full-time'),
('EMP002', 'Jane', 'Smith', 'jane@employee.com', '(234) 567-8901', 'Female', 'HR', 'part-time'),
('EMP003', 'Bob', 'Johnson', 'bob@employee.com', '(345) 678-9012', 'Male', 'IT', 'intern'),
('EMP004', 'Alice', 'Williams', 'alice@employee.com', '(456) 789-0123', 'Female', 'FIN', 'full-time'),
('EMP005', 'Charlie', 'Brown', 'charlie@employee.com', '(567) 890-1234', 'Male', 'MKT', 'part-time'),
('EMP006', 'David', 'Miller', 'david@employee.com', '(678) 901-2345', 'Male', 'ENG', 'full-time'),
('EMP007', 'Eva', 'Davis', 'eva@employee.com', '(789) 012-3456', 'Female', 'DSN', 'intern');

-- Insert full-time employee details
INSERT INTO full_time_employees (employee_id, salary, annual_bonus, job_title, vacation_days) VALUES
('EMP001', 75000.00, 5000.00, 'Software Developer', 25),
('EMP004', 82000.00, 6000.00, 'Financial Analyst', 20),
('EMP006', 92000.00, 7000.00, 'Senior Engineer', 30);

-- Insert part-time employee details
INSERT INTO part_time_employees (employee_id, hourly_rate, hours_per_week, work_arrangement) VALUES
('EMP002', 25.50, 20, 'regular'),
('EMP005', 22.75, 25, 'contract');

-- Insert intern employee details
INSERT INTO intern_employees (employee_id, internship_duration, university, degree_program, expected_graduation, stipend) VALUES
('EMP003', '6 months', 'State University', 'Computer Science', '2024-05-15', 2000.00),
('EMP007', '3 months', 'Tech College', 'Graphic Design', '2023-12-10', 1800.00);

-- Insert addresses
INSERT INTO employee_addresses (employee_id, street_address, city, state, zip_code) VALUES
('EMP001', '123 Main St', 'Springfield', 'IL', '62701'),
('EMP002', '456 Oak Ave', 'Shelbyville', 'IL', '62565'),
('EMP003', '789 Pine Rd', 'Capital City', 'IL', '62702');

-- Insert employment history
INSERT INTO employment_history (employee_id, position_title, department, employee_type, start_date, salary) VALUES
('EMP001', 'Junior Developer', 'IT', 'full-time', '2022-01-15', 65000.00),
('EMP001', 'Software Developer', 'IT', 'full-time', '2023-01-15', 75000.00),
('EMP002', 'HR Assistant', 'HR', 'part-time', '2023-02-20', NULL),
('EMP003', 'IT Intern', 'IT', 'intern', '2023-03-10', NULL);

-- Insert emergency contacts
INSERT INTO employee_contacts (employee_id, contact_type, contact_name, relationship, phone) VALUES
('EMP001', 'emergency', 'Mary Doe', 'Spouse', '(123) 555-0199'),
('EMP002', 'emergency', 'Robert Smith', 'Father', '(234) 555-0288');

-- ============================================
-- STEP 8: CREATE VIEWS FOR COMMON QUERIES
-- ============================================

-- View for all employees with details
CREATE VIEW vw_all_employees AS
SELECT 
    be.employee_id,
    be.first_name,
    be.last_name,
    be.email,
    be.phone,
    be.gender,
    be.department,
    d.department_name,
    be.employee_type,
    be.created_at,
    
    -- Full-time specific
    fte.salary,
    fte.job_title,
    fte.vacation_days,
    
    -- Part-time specific
    pte.hourly_rate,
    pte.hours_per_week,
    pte.work_arrangement,
    
    -- Intern specific
    ie.internship_duration,
    ie.university,
    ie.expected_graduation,
    ie.stipend,
    
    -- Address
    ea.street_address,
    ea.city,
    ea.state,
    ea.zip_code
    
FROM base_employees be
LEFT JOIN departments d ON be.department = d.department_code
LEFT JOIN full_time_employees fte ON be.employee_id = fte.employee_id
LEFT JOIN part_time_employees pte ON be.employee_id = pte.employee_id
LEFT JOIN intern_employees ie ON be.employee_id = ie.employee_id
LEFT JOIN employee_addresses ea ON be.employee_id = ea.employee_id AND ea.is_primary = TRUE
ORDER BY be.last_name, be.first_name;

-- View for department summary
CREATE VIEW vw_department_summary AS
SELECT 
    d.department_code,
    d.department_name,
    d.location,
    d.budget,
    COUNT(DISTINCT be.employee_id) as total_employees,
    COUNT(DISTINCT CASE WHEN be.employee_type = 'full-time' THEN be.employee_id END) as full_time_count,
    COUNT(DISTINCT CASE WHEN be.employee_type = 'part-time' THEN be.employee_id END) as part_time_count,
    COUNT(DISTINCT CASE WHEN be.employee_type = 'intern' THEN be.employee_id END) as intern_count,
    COALESCE(AVG(fte.salary), 0) as avg_salary,
    COALESCE(AVG(pte.hourly_rate), 0) as avg_hourly_rate,
    COALESCE(SUM(fte.salary), 0) as total_salary_budget
FROM departments d
LEFT JOIN base_employees be ON d.department_code = be.department
LEFT JOIN full_time_employees fte ON be.employee_id = fte.employee_id
LEFT JOIN part_time_employees pte ON be.employee_id = pte.employee_id
WHERE d.active = TRUE
GROUP BY d.department_code, d.department_name, d.location, d.budget
ORDER BY d.department_name;

-- View for employee directory (simple)
CREATE VIEW vw_employee_directory AS
SELECT 
    be.employee_id,
    be.first_name || ' ' || be.last_name as full_name,
    be.department,
    d.department_name,
    be.employee_type,
    be.email,
    be.phone,
    be.created_at as hire_date,
    CASE 
        WHEN be.employee_type = 'full-time' THEN 'Full-time'
        WHEN be.employee_type = 'part-time' THEN 'Part-time'
        WHEN be.employee_type = 'intern' THEN 'Intern'
    END as employee_type_display
FROM base_employees be
LEFT JOIN departments d ON be.department = d.department_code
ORDER BY be.last_name, be.first_name;

-- ============================================
-- STEP 9: CREATE STORED PROCEDURES AND FUNCTIONS
-- ============================================

-- Procedure to add a new employee (handles all types)
CREATE OR REPLACE PROCEDURE sp_add_employee(
    p_employee_id VARCHAR,
    p_first_name VARCHAR,
    p_last_name VARCHAR,
    p_email VARCHAR,
    p_phone VARCHAR,
    p_gender VARCHAR,
    p_department VARCHAR,
    p_employee_type VARCHAR,
    
    -- Optional parameters for specific types
    p_salary DECIMAL DEFAULT NULL,
    p_hourly_rate DECIMAL DEFAULT NULL,
    p_internship_duration VARCHAR DEFAULT NULL,
    p_university VARCHAR DEFAULT NULL
)
LANGUAGE plpgsql
AS $$
BEGIN
    -- Insert into base employees
    INSERT INTO base_employees (employee_id, first_name, last_name, email, phone, gender, department, employee_type)
    VALUES (p_employee_id, p_first_name, p_last_name, p_email, p_phone, p_gender, p_department, p_employee_type);
    
    -- Insert into specific type table
    IF p_employee_type = 'full-time' AND p_salary IS NOT NULL THEN
        INSERT INTO full_time_employees (employee_id, salary)
        VALUES (p_employee_id, p_salary);
        
    ELSIF p_employee_type = 'part-time' AND p_hourly_rate IS NOT NULL THEN
        INSERT INTO part_time_employees (employee_id, hourly_rate)
        VALUES (p_employee_id, p_hourly_rate);
        
    ELSIF p_employee_type = 'intern' AND p_internship_duration IS NOT NULL AND p_university IS NOT NULL THEN
        INSERT INTO intern_employees (employee_id, internship_duration, university)
        VALUES (p_employee_id, p_internship_duration, p_university);
    END IF;
    
    -- Add to employment history
    INSERT INTO employment_history (employee_id, position_title, department, employee_type, start_date)
    VALUES (p_employee_id, 'New Hire', p_department, p_employee_type, CURRENT_DATE);
    
END;
$$;

-- Procedure to update employee information
CREATE OR REPLACE PROCEDURE sp_update_employee(
    p_employee_id VARCHAR,
    p_email VARCHAR DEFAULT NULL,
    p_phone VARCHAR DEFAULT NULL,
    p_department VARCHAR DEFAULT NULL
)
LANGUAGE plpgsql
AS $$
BEGIN
    UPDATE base_employees 
    SET 
        email = COALESCE(p_email, email),
        phone = COALESCE(p_phone, phone),
        department = COALESCE(p_department, department)
    WHERE employee_id = p_employee_id;
    
    -- Log the change if department changed
    IF p_department IS NOT NULL THEN
        INSERT INTO employment_history (employee_id, position_title, department, employee_type, start_date, reason_for_change)
        SELECT 
            p_employee_id, 
            'Department Transfer', 
            p_department, 
            employee_type, 
            CURRENT_DATE, 
            'Department change via system'
        FROM base_employees 
        WHERE employee_id = p_employee_id;
    END IF;
END;
$$;

-- Function to get employee statistics
CREATE OR REPLACE FUNCTION fn_get_employee_stats()
RETURNS TABLE(
    total_employees BIGINT,
    full_time_count BIGINT,
    part_time_count BIGINT,
    intern_count BIGINT,
    departments_with_employees BIGINT,
    avg_fulltime_salary DECIMAL,
    avg_parttime_rate DECIMAL,
    total_salary_budget DECIMAL
) 
LANGUAGE plpgsql
AS $$
BEGIN
    RETURN QUERY
    SELECT 
        COUNT(DISTINCT be.employee_id) as total_employees,
        COUNT(DISTINCT CASE WHEN be.employee_type = 'full-time' THEN be.employee_id END) as full_time_count,
        COUNT(DISTINCT CASE WHEN be.employee_type = 'part-time' THEN be.employee_id END) as part_time_count,
        COUNT(DISTINCT CASE WHEN be.employee_type = 'intern' THEN be.employee_id END) as intern_count,
        COUNT(DISTINCT be.department) as departments_with_employees,
        COALESCE(AVG(fte.salary), 0) as avg_fulltime_salary,
        COALESCE(AVG(pte.hourly_rate), 0) as avg_parttime_rate,
        COALESCE(SUM(fte.salary), 0) as total_salary_budget
    FROM base_employees be
    LEFT JOIN full_time_employees fte ON be.employee_id = fte.employee_id
    LEFT JOIN part_time_employees pte ON be.employee_id = pte.employee_id;
END;
$$;

-- Function to delete an employee
CREATE OR REPLACE PROCEDURE sp_delete_employee(
    p_employee_id VARCHAR
)
LANGUAGE plpgsql
AS $$
BEGIN
    -- This will cascade delete from all related tables due to ON DELETE CASCADE
    DELETE FROM base_employees WHERE employee_id = p_employee_id;
    
    -- Log the deletion
    INSERT INTO employment_history (employee_id, position_title, department, start_date, end_date, employment_status, reason_for_change)
    VALUES (p_employee_id, 'Terminated', 'N/A', CURRENT_DATE, CURRENT_DATE, 'terminated', 'Employee deleted from system');
END;
$$;

-- Function to search employees
CREATE OR REPLACE FUNCTION fn_search_employees(
    p_search_term VARCHAR DEFAULT NULL,
    p_department VARCHAR DEFAULT NULL,
    p_employee_type VARCHAR DEFAULT NULL
)
RETURNS TABLE(
    employee_id VARCHAR,
    full_name VARCHAR,
    department VARCHAR,
    employee_type VARCHAR,
    email VARCHAR,
    phone VARCHAR,
    hire_date TIMESTAMP
) 
LANGUAGE plpgsql
AS $$
BEGIN
    RETURN QUERY
    SELECT 
        be.employee_id,
        be.first_name || ' ' || be.last_name as full_name,
        be.department,
        be.employee_type,
        be.email,
        be.phone,
        be.created_at as hire_date
    FROM base_employees be
    WHERE 
        (p_search_term IS NULL OR 
         be.first_name ILIKE '%' || p_search_term || '%' OR 
         be.last_name ILIKE '%' || p_search_term || '%' OR
         be.employee_id ILIKE '%' || p_search_term || '%' OR
         be.email ILIKE '%' || p_search_term || '%') AND
        (p_department IS NULL OR be.department = p_department) AND
        (p_employee_type IS NULL OR be.employee_type = p_employee_type)
    ORDER BY be.last_name, be.first_name;
END;
$$;

-- ============================================
-- STEP 10: DEMONSTRATION QUERIES
-- ============================================

-- Query to show all employees with their types
COMMENT ON VIEW vw_all_employees IS 'Complete view of all employees with their specific type details';

-- Query to show department summary
COMMENT ON VIEW vw_department_summary IS 'Summary statistics for each department';

-- Query to show employee directory
COMMENT ON VIEW vw_employee_directory IS 'Simple directory of all employees';

-- ============================================
-- STEP 11: COMMENTS AND DOCUMENTATION
-- ============================================

-- Table comments
COMMENT ON TABLE base_employees IS 'Base table for all employees, matches the C++ Employee base class';
COMMENT ON TABLE full_time_employees IS 'Full-time employees table, matches FullTimeEmployee C++ class';
COMMENT ON TABLE part_time_employees IS 'Part-time employees table, matches PartTimeEmployee C++ class';
COMMENT ON TABLE intern_employees IS 'Intern employees table, matches InternEmployee C++ class';
COMMENT ON TABLE departments IS 'Department information table';
COMMENT ON TABLE employee_addresses IS 'Employee addresses table';
COMMENT ON TABLE employment_history IS 'Employment history and changes tracking';
COMMENT ON TABLE employee_contacts IS 'Emergency and additional contacts';

-- Column comments for base_employees (matching C++ class)
COMMENT ON COLUMN base_employees.employee_id IS 'Auto-generated employee ID (e.g., EMP001)';
COMMENT ON COLUMN base_employees.first_name IS 'Employee first name';
COMMENT ON COLUMN base_employees.last_name IS 'Employee last name';
COMMENT ON COLUMN base_employees.email IS 'Employee email address';
COMMENT ON COLUMN base_employees.phone IS 'Employee phone number';
COMMENT ON COLUMN base_employees.gender IS 'Employee gender';
COMMENT ON COLUMN base_employees.department IS 'Employee department (matches form selection)';
COMMENT ON COLUMN base_employees.employee_type IS 'Employee type: full-time, part-time, or intern';
COMMENT ON COLUMN base_employees.profile_picture IS 'Profile picture URL or base64 data';

-- ============================================
-- FINAL MESSAGE
-- ============================================

DO $$
BEGIN
    RAISE NOTICE '============================================';
    RAISE NOTICE 'EMPLOYEE MANAGEMENT DATABASE CREATED SUCCESSFULLY';
    RAISE NOTICE '============================================';
    RAISE NOTICE 'Tables Created:';
    RAISE NOTICE '- base_employees (matches Employee base class)';
    RAISE NOTICE '- full_time_employees (matches FullTimeEmployee class)';
    RAISE NOTICE '- part_time_employees (matches PartTimeEmployee class)';
    RAISE NOTICE '- intern_employees (matches InternEmployee class)';
    RAISE NOTICE '- departments';
    RAISE NOTICE '- employee_addresses';
    RAISE NOTICE '- employment_history';
    RAISE NOTICE '- employee_contacts';
    RAISE NOTICE '';
    RAISE NOTICE 'Views Created:';
    RAISE NOTICE '- vw_all_employees';
    RAISE NOTICE '- vw_department_summary';
    RAISE NOTICE '- vw_employee_directory';
    RAISE NOTICE '';
    RAISE NOTICE 'Procedures Created:';
    RAISE NOTICE '- sp_add_employee()';
    RAISE NOTICE '- sp_update_employee()';
    RAISE NOTICE '- sp_delete_employee()';
    RAISE NOTICE '';
    RAISE NOTICE 'Functions Created:';
    RAISE NOTICE '- fn_get_employee_stats()';
    RAISE NOTICE '- fn_search_employees()';
    RAISE NOTICE '';
    RAISE NOTICE 'Sample Data: 7 employees inserted';
    RAISE NOTICE '============================================';
END $$;

-- ============================================
-- USAGE INSTRUCTIONS
-- ============================================

-- 1. To run this script:
--    psql -U your_username -d employee_management -f employee_management_schema.sql
--
-- 2. Test queries:
--    SELECT * FROM vw_all_employees;
--    SELECT * FROM vw_department_summary;
--    CALL sp_add_employee('EMP008', 'Frank', 'Wilson', 'frank@employee.com', 
--                         '(890) 123-4567', 'Male', 'OPS', 'full-time', 68000.00);
--    SELECT * FROM fn_get_employee_stats();
--
-- 3. To backup database:
--    pg_dump -U your_username -d employee_management -f backup.sql