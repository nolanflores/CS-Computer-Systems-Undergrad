DELIMITER //
CREATE OR REPLACE PROCEDURE sp_load_sstevedb()
BEGIN
    SET FOREIGN_KEY_CHECKS = 0;

    DROP TABLE IF EXISTS Roles;
    CREATE TABLE Roles (
        role_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
        pay_rate FLOAT NOT NULL,
        job_title varchar(45),
        PRIMARY KEY (role_ID)
    );

    INSERT INTO Roles (pay_rate, job_title) VALUES
    (16.00, 'Sales'),
    (25.00, 'Teacher'),
    (30.00, 'Manager');

    DROP TABLE IF EXISTS Locations;
    CREATE TABLE Locations (
        location_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
        l_address varchar(45) NOT NULL,
        phone_number varchar(45) NOT NULL,
        PRIMARY KEY (location_ID)
    );

    INSERT INTO Locations (l_address, phone_number) VALUES
    ('Newport, OR', '971-233-2314'),
    ('Astoria, OR', '971-230-1234'),
    ('Cannon Beach, OR', '503-230-3210');

    DROP TABLE IF EXISTS Customers;
    CREATE TABLE Customers (
        customer_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
        c_name varchar(45) NOT NULL,
        phone_number varchar(45) NOT NULL,
        email varchar(45) NOT NULL,
        PRIMARY KEY (customer_ID)
    );

    INSERT INTO Customers (c_name, phone_number, email) VALUES
    ('John Smith', '971-340-2165', 'cmail@gmail.com'),
    ('Smith John', '972-348-7283', 'blackmail@gmail.com'),
    ('Cruella Deville', '971-328-2104', 'ihatedogs@gmail.com');


    DROP TABLE IF EXISTS Guitars;
    CREATE OR REPLACE TABLE Guitars (
        product_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
        g_year INT NOT NULL,
        amount FLOAT NOT NULL,
        brand varchar(45) NOT NULL,
        model varchar(45) NOT NULL,
        g_condition varchar(45) NOT NULL,
        serial_num varchar(45) NOT NULL,
        PRIMARY KEY (product_ID)
    );

    INSERT INTO Guitars (g_year, amount, brand, model, g_condition, serial_num) VALUES
    (1973, 3000, 'Fender', 'Precision Bass', 'Good', '1001231'),
    (2009, 900, 'Epiphone', 'Riviera', 'Great', '2001352'),
    (1962, 5000, 'Fender', 'Telecaster', 'Good', '3333333'),
    (2022, 600, 'Fender', 'Player Jazz Bass', 'Good', '6666666'),
    (2013, 3000, 'Gibson', 'Les Paul', 'Mint', '4242424');

    DROP TABLE IF EXISTS Employees;
    CREATE TABLE Employees (
        employee_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
        e_name varchar(45) NOT NULL,
        role_ID INT NOT NULL,
        location_ID INT NOT NULL,
        phone_number varchar(45) NOT NULL,
        email varchar(45) NOT NULL,
        is_Teacher BOOL NOT NULL,
        instrument varchar(45),
        PRIMARY KEY (employee_ID),
        FOREIGN KEY (role_ID) REFERENCES Roles(role_ID)
            ON DELETE CASCADE
            ON UPDATE CASCADE,
        FOREIGN KEY (location_ID) REFERENCES Locations(location_ID)
            ON DELETE CASCADE
            ON UPDATE CASCADE
    );

    INSERT INTO Employees (e_name, role_ID, location_ID, phone_number, email, is_Teacher, instrument) VALUES
    ('James Jamerson', 1, 2, '971-329-2104', 'email1@gmail.com', 0, NULL),
    ('Jim Johnman', 1, 1, '971-329-2105', 'email2@gmail.com', 0, NULL),
    ('John Jimman', 2, 2, '971-329-2165', 'email3@gmail.com', 1, 'Guitar/Bass'),
    ('Man Jimjohn', 1, 1, '971-329-2175', 'email@gmail.com', 0, NULL),
    ('Steve Screeb', 3, 2, '971-339-2175','mail@gmail.com', 0, NULL),
    ('Carol Crumb', 3, 1, '971-349-2175','mail2@gmail.com', 0, NULL);


    DROP TABLE IF EXISTS Guitars;
    CREATE OR REPLACE TABLE Guitars (
        product_ID INT UNIQUE NOT NULL AUTO_INCREMENT,
        g_year INT NOT NULL,
        amount FLOAT NOT NULL,
        brand varchar(45) NOT NULL,
        model varchar(45) NOT NULL,
        g_condition varchar(45) NOT NULL,
        serial_num varchar(45) NOT NULL,
        PRIMARY KEY (product_ID)
    );

    INSERT INTO Guitars (g_year, amount, brand, model, g_condition, serial_num) VALUES
    (1973, 3000, 'Fender', 'Precision Bass', 'Good', '1001231'),
    (2009, 900, 'Epiphone', 'Riviera', 'Great', '2001352'),
    (1962, 5000, 'Fender', 'Telecaster', 'Good', '3333333'),
    (2022, 600, 'Fender', 'Player Jazz Bass', 'Good', '6666666'),
    (2013, 3000, 'Gibson', 'Les Paul', 'Mint', '4242424');

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

    INSERT INTO Sales (customer_ID, employee_ID, product_ID, location_ID, s_date, amount) VALUES
    (1, 2, 3, 1, '2024-03-12', 3000),
    (2, 2, 4, 2, '2024-04-09', 900),
    (3, 4, 5, 2, '2024-06-13', 5000),
    (3, 3, 2, 1, '2024-11-17', 2000);

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

    INSERT INTO Lessons (customer_ID, employee_ID, rate, instrument, location_ID) VALUES
    (1, 3, 25.00, 'Guitar', 2),
    (2, 3, 25.00, 'Guitar', 2),
    (3, 3, 25.00, 'Bass', 2);

    SET FOREIGN_KEY_CHECKS = 1;
END//
DELIMITER ;

DELIMITER //
CREATE OR REPLACE PROCEDURE sp_delete_one()
BEGIN
    DELETE FROM Sales
    WHERE amount = 900
    LIMIT 1;
END//
DELIMITER ;

DELIMITER //
CREATE OR REPLACE PROCEDURE sp_reset_sstevedb()
BEGIN
    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN   
        ROLLBACK;
    END;

    START TRANSACTION;

    DELETE FROM Lessons;
    DELETE FROM Sales;
    DELETE FROM Employees;
    DELETE FROM Guitars;
    DELETE FROM Customers;
    DELETE FROM Locations;
    DELETE FROM Roles;

    CALL sp_load_sstevedb();

    COMMIT;
END//
DELIMITER ;

DELIMITER //
CREATE OR REPLACE PROCEDURE insert_sale_record (
    IN  p_entity      VARCHAR(50),
    IN  p_operation   VARCHAR(50),
    IN  p_customer_id INT,
    IN  p_employee_id INT,
    IN  p_product_id  INT,
    IN  p_location_id INT,
    IN  p_sale_date   DATE,
    IN  p_amount      DECIMAL(10,2),
    OUT p_new_sale_id INT
)
BEGIN
    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN   
        ROLLBACK;
        RESIGNAL;
    END;

    START TRANSACTION;

    IF IFNULL(p_entity, '') != 'Sales' OR IFNULL(p_operation, '') != 'add' THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'Invalid operation. Entity must be "Sales" and operation must be "add".';
    END IF;

    INSERT INTO Sales (
        customer_ID, 
        employee_ID, 
        product_ID, 
        location_ID, 
        s_Date, 
        amount
    ) 
    VALUES (
        p_customer_id, 
        p_employee_id, 
        p_product_id, 
        p_location_id, 
        p_sale_date, 
        p_amount
    );

    SET p_new_sale_id = LAST_INSERT_ID();

    COMMIT;
END//
DELIMITER ;

DELIMITER //
CREATE OR REPLACE PROCEDURE sp_update_lesson (
    IN p_customer_ID INT,
    IN p_employee_ID INT,
    IN p_location_ID INT,
    IN p_rate FLOAT,
    IN p_instrument VARCHAR(45)
)
BEGIN
    UPDATE Lessons 
    SET 
        location_ID = p_location_ID,
        rate = p_rate,
        instrument = p_instrument
    WHERE 
        customer_ID = p_customer_ID AND 
        employee_ID = p_employee_ID;
END //
DELIMITER ;

DELIMITER //
CREATE OR REPLACE PROCEDURE sp_delete_lesson (
    IN p_customer_ID INT,
    IN p_employee_ID INT
)
BEGIN
    DELETE FROM Lessons 
    WHERE 
        customer_ID = p_customer_ID AND 
        employee_ID = p_employee_ID;
END //
DELIMITER ;