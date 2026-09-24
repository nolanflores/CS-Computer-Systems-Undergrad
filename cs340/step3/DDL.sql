-- Group 36: Thomas Munro, Nolan Flores --
-- Seasick Steve's Guitar Emporium Sales Management --

SET FOREIGN_KEY_CHECKS = 0;
SET AUTOCOMMIT = 0;

/* Create tables, drop them if they already exist */

DROP TABLE IF EXISTS Sales;
CREATE TABLE Sales (
    transaction_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
    customer_ID INT NOT NULL,
    employee_ID INT NOT NULL,
    product_ID INT NOT NULL,
    location_ID INT NOT NULL,
    s_date DATE NOT NULL,
    amount FLOAT NOT NULL,
    PRIMARY KEY (transaction_ID),
    FOREIGN KEY (customer_ID) REFERENCES Customers(customer_ID)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (employee_ID) REFERENCES Employees(employee_ID)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (product_ID) REFERENCES Guitars(product_ID)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (location_ID) REFERENCES Locations(location_ID)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

DROP TABLE IF EXISTS Locations;
CREATE TABLE Locations (
    location_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
    l_address varchar(45) NOT NULL,
    phone_number varchar(45) NOT NULL,
    PRIMARY KEY (location_ID)
);

DROP TABLE IF EXISTS Employees;
CREATE TABLE Employees (
    employee_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
    e_name varchar(45) NOT NULL,
    role_ID INT NOT NULL,
    location_ID INT NOT NULL,
    phone_number varchar(45) NOT NULL,
    email varchar(45) NOT NULL,
    is_Teacher bit(1) NOT NULL,
    instrument varchar(45),
    PRIMARY KEY (employee_ID),
    FOREIGN KEY (role_ID) REFERENCES Roles(role_ID)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (location_ID) REFERENCES Locations(location_ID)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

DROP TABLE IF EXISTS Roles;
CREATE TABLE Roles (
    role_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
    pay_rate FLOAT NOT NULL,
    job_title varchar(45),
    PRIMARY KEY (role_ID)
);

DROP TABLE IF EXISTS Customers;
CREATE TABLE Customers (
    customer_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
    c_name varchar(45) NOT NULL,
    phone_number varchar(45) NOT NULL,
    email varchar(45) NOT NULL,
    PRIMARY KEY (customer_ID)
);

DROP TABLE IF EXISTS Guitars;
CREATE TABLE Guitars (
    product_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
    g_year INT NOT NULL,
    amount FLOAT NOT NULL,
    brand varchar(45) NOT NULL,
    model varchar(45) NOT NULL,
    g_condition varchar(45) NOT NULL,
    serial_num varchar(45) NOT NULL,
    PRIMARY KEY (product_ID)
);

DROP TABLE IF EXISTS Lessons;
CREATE TABLE Lessons (
    customer_ID INT NOT NULL,
    employee_ID INT NOT NULL,
    location_ID INT NOT NULL,
    rate FLOAT NOT NULL,
    instrument varchar(45) NOT NULL,
    PRIMARY KEY (customer_ID, employee_ID),
    FOREIGN KEY (customer_ID) REFERENCES Customers(customer_ID)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (employee_ID) REFERENCES Employees(employee_ID)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (location_ID) REFERENCES Locations(location_ID)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

/* Insert Sample Data */

INSERT INTO Sales (customer_ID, employee_ID, product_ID, location_ID, s_date, amount) VALUES
(1, 2, 3, 1, 3/12/2024, 3000),
(2, 2, 4, 2, 4/9/2024, 900),
(3, 4, 5, 2, 6/13/2024, 5000);

INSERT INTO Locations (l_address, phone_number) VALUES
('Newport, OR', '971-336-7241'),
('Astoria, OR', '971-352-7852');

INSERT INTO Employees (e_name, role_ID, location_ID, phone_number, email, is_Teacher, instrument) VALUES
('James Jamerson', 1, 2, '971-329-2104', 'email1@gmail.com', 0, NULL),
('Jim Johnman', 1, 1, '971-329-2105', 'email2@gmail.com', 0, NULL),
('John Jimman', 2, 2, '971-329-2165', 'email3@gmail.com', 1, 'Guitar/Bass'),
('Man Jimjohn', 1, 1, '971-329-2175', 'email@gmail.com', 0, NULL),
('Steve Screeb', 3, 2, '971-339-2175','mail@gmail.com', 0, NULL),
('Carol Crumb', 3, 1, '971-349-2175','mail2@gmail.com', 0, NULL);

INSERT INTO Customers (c_name, phone_number, email) VALUES
('John Smith', '971-340-2165', 'cmail@gmail.com'),
('Smith John', '972-348-7283', 'blackmail@gmail.com'),
('Cruella Deville', '971-328-2104', 'ihatedogs@gmail.com');

INSERT INTO Guitars (g_year, amount, brand, model, g_condition, serial_num) VALUES
(1973, 3000, 'Fender', 'Precision Bass', 'Good', '1001231'),
(2009, 900, 'Epiphone', 'Riviera', 'Great', '2001352'),
(1962, 5000, 'Fender', 'Telecaster', 'Good', '3333333'),
(2022, 600, 'Fender', 'Player Jazz Bass', 'Good', '6666666'),
(2013, 3000, 'Gibson', 'Les Paul', 'Mint', '4242424');

INSERT INTO Roles (pay_rate, job_title) VALUES
(16.00, 'Sales'),
(25.00, 'Teacher'),
(30.00, 'Manager');

INSERT INTO Lessons (customer_ID, employee_ID, rate, instrument, location_ID) VALUES
(1, 3, 25.00, 'Guitar', 2),
(2, 3, 25.00, 'Guitar', 2),
(3, 3, 25.00, 'Bass', 2);