-- ============================================================================
-- SQL DATA MANIPULATION QUERIES - GROUP 36
-- ============================================================================
-- This file contains SELECT, INSERT, UPDATE, and DELETE queries for each table:
-- Roles, Locations, Customers, Employees, Guitars, Sales, Lessons
-- ============================================================================

-- ============================================================================
-- ROLES TABLE
-- ============================================================================

SELECT
    Roles.role_ID,
    Roles.job_title,
    Roles.pay_rate
FROM Roles
ORDER BY Roles.pay_rate DESC, Roles.job_title;

INSERT INTO Roles (pay_rate, job_title)
VALUES (@pay_rate_input, @job_title_input);

UPDATE Roles
SET pay_rate = @pay_rate_input,
    job_title = @job_title_input
WHERE role_ID = @rid_input;

DELETE FROM Roles
WHERE role_ID = @rid_input;

-- ============================================================================
-- LOCATIONS TABLE
-- ============================================================================

SELECT
    Locations.location_ID,
    Locations.l_address,
    Locations.phone_number
FROM Locations
ORDER BY Locations.l_address;

INSERT INTO Locations (l_address, phone_number)
VALUES (@address_input, @phone_number_input);

UPDATE Locations
SET l_address = @address_input,
    phone_number = @phone_number_input
WHERE location_ID = @lid_input;

DELETE FROM Locations
WHERE location_ID = @lid_input;

-- ============================================================================
-- CUSTOMERS TABLE
-- ============================================================================

SELECT
    Customers.customer_ID,
    Customers.c_name,
    Customers.phone_number,
    Customers.email
FROM Customers
ORDER BY Customers.c_name;

INSERT INTO Customers (c_name, phone_number, email)
VALUES (@cname_input, @phone_number_input, @email_input);

UPDATE Customers
SET c_name = @cname_input,
    phone_number = @phone_number_input,
    email = @email_input
WHERE customer_ID = @cid_input;

DELETE FROM Customers
WHERE customer_ID = @cid_input;

-- ============================================================================
-- EMPLOYEES TABLE
-- ============================================================================

SELECT
    Employees.employee_ID,
    Employees.e_name,
    Roles.job_title,
    Roles.pay_rate,
    Locations.l_address,
    Employees.phone_number,
    Employees.email,
    Employees.is_Teacher,
    Employees.instrument,
    Employees.role_ID,
    Employees.location_ID
FROM Employees
INNER JOIN Roles ON Employees.role_ID = Roles.role_ID
INNER JOIN Locations ON Employees.location_ID = Locations.location_ID
ORDER BY Employees.e_name, Locations.l_address;

INSERT INTO Employees (e_name, role_ID, location_ID, phone_number, email, is_Teacher, instrument)
VALUES (@ename_input, @rid_input, @lid_input, @phone_number_input, @email_input, @is_teacher_input, @instrument_input);

UPDATE Employees
SET e_name = @ename_input,
    role_ID = @rid_input,
    location_ID = @lid_input,
    phone_number = @phone_number_input,
    email = @email_input,
    is_Teacher = @is_teacher_input,
    instrument = @instrument_input
WHERE employee_ID = @eid_input;

DELETE FROM Employees
WHERE employee_ID = @eid_input;

-- ============================================================================
-- GUITARS TABLE
-- ============================================================================

SELECT
    Guitars.product_ID,
    Guitars.brand,
    Guitars.model,
    Guitars.g_year,
    Guitars.amount,
    Guitars.g_condition,
    Guitars.serial_num
FROM Guitars
ORDER BY Guitars.brand, Guitars.model, Guitars.g_year DESC;

INSERT INTO Guitars (g_year, amount, brand, model, g_condition, serial_num)
VALUES (@year_input, @amount_input, @brand_input, @model_input, @condition_input, @snum_input);

UPDATE Guitars
SET g_year = @year_input,
    amount = @amount_input,
    brand = @brand_input,
    model = @model_input,
    g_condition = @condition_input,
    serial_num = @snum_input
WHERE product_ID = @pid_input;

DELETE FROM Guitars
WHERE product_ID = @pid_input;

-- ============================================================================
-- SALES TABLE
-- ============================================================================

SELECT
    Sales.transaction_ID,
    CONCAT(Customers.c_name) AS customerName,
    CONCAT(Employees.e_name) AS employeeName,
    CONCAT(Guitars.brand, ' ', Guitars.model) AS guitarModel,
    Locations.l_address,
    Sales.s_date,
    Sales.amount,
    Sales.customer_ID,
    Sales.employee_ID,
    Sales.product_ID,
    Sales.location_ID
FROM Sales
INNER JOIN Customers ON Sales.customer_ID = Customers.customer_ID
INNER JOIN Employees ON Sales.employee_ID = Employees.employee_ID
INNER JOIN Guitars ON Sales.product_ID = Guitars.product_ID
INNER JOIN Locations ON Sales.location_ID = Locations.location_ID
ORDER BY Sales.s_date DESC, Customers.c_name;

INSERT INTO Sales (customer_ID, employee_ID, product_ID, location_ID, s_date, amount)
VALUES (@cid_input, @eid_input, @pid_input, @lid_input, @sdate_input, @amount_input);

UPDATE Sales
SET customer_ID = @cid_input,
    employee_ID = @eid_input,
    product_ID = @pid_input,
    location_ID = @lid_input,
    s_date = @sdate_input,
    amount = @amount_input
WHERE transaction_ID = @tid_input;

DELETE FROM Sales
WHERE transaction_ID = @tid_input;

-- ============================================================================
-- LESSONS TABLE
-- ============================================================================

SELECT
    Lessons.customer_ID,
    CONCAT(Customers.c_name) AS customerName,
    Lessons.employee_ID,
    CONCAT(Employees.e_name) AS employeeName,
    Locations.l_address,
    Lessons.instrument,
    Lessons.rate,
    Lessons.location_ID
FROM Lessons
INNER JOIN Customers ON Lessons.customer_ID = Customers.customer_ID
INNER JOIN Employees ON Lessons.employee_ID = Employees.employee_ID
INNER JOIN Locations ON Lessons.location_ID = Locations.location_ID
ORDER BY Customers.c_name, Employees.e_name;

INSERT INTO Lessons (customer_ID, employee_ID, location_ID, rate, instrument)
VALUES (@cid_input, @eid_input, @lid_input, @rate_input, @instrument_input);

UPDATE Lessons
SET customer_ID = @cid_input,
    employee_ID = @eid_input,
    location_ID = @lid_input,
    rate = @rate_input,
    instrument = @instrument_input
WHERE customer_ID = @cid_input AND employee_ID = @eid_input;

DELETE FROM Lessons
WHERE customer_ID = @cid_input AND employee_ID = @eid_input;