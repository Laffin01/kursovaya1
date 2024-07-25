CREATE TABLE `cars` (
 id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
`Марка` VARCHAR(45) NOT NULL,
`Країна виробник` VARCHAR(45) NOT NULL
);

INSERT INTO cars (`Марка`, `Країна виробник`)
VALUES 
('Volvo', 'Швеція'),
('BMW', 'Німеччина'),
('Mercedes-Benz', 'Німеччина'),
('Audi', 'Німеччина'),
('Peugeot', 'Франція'),
('Toyota', 'Японія'),
('Land-Rover', 'Великобританія'),
('Porsche', 'Німеччина'),
('Subaru', 'Японія');

CREATE TABLE models_of_the_car (
    model_name VARCHAR(50) not null,
    year_of_release INT not null,
    model_id INT auto_increment primary key,
    conf_id INT,
    FOREIGN KEY (conf_id) REFERENCES cars(id)
);


INSERT INTO models_of_the_car (model_name, year_of_release, conf_id) VALUES
('XC90', 2019, 1),
('XC60', 2021, 1),
('S90', 2021, 1),
('X5', 2019, 2),
('X6', 2018, 2),
('C', 2019, 3),
('CLS', 2021, 3),
('A4', 2019, 4),
('A5', 2021, 4),
('A7', 2021, 4),
('A8', 2019, 4),
('208', 2020, 5),
('3008', 2021, 5),
('408', 2019, 5),
('Land-Cruiser', 2019, 6),
('Camry', 2019, 6),
('Corolla', 2021, 6),
('Range-Rover', 2021, 7),
('Discovery', 2019, 7),
('Defender', 2020, 7),
('Panamera', 2021, 8),
('Cayenne', 2019, 8),
('Cayman', 2019, 8),
('Forester', 2019, 9),
('Impreza', 2020, 9),
('Outback', 2021, 9),
('Legacy', 2019, 9);

CREATE TABLE сonfigurations (
    configuration_id INT PRIMARY KEY auto_increment,
    configuration_name VARCHAR(50),
    price DECIMAL(10, 2),
    model_id INT,
    color VARCHAR(20),
    doors INT,
    seats INT,
    fuel_type VARCHAR(20),
    transmission VARCHAR(20),
    engine_volume DECIMAL(3, 1),
    fuel_consumption DECIMAL(4, 1),
    `power` INT,
    FOREIGN KEY (model_id) REFERENCES models_of_the_car(model_id)
);

INSERT INTO сonfigurations ( configuration_name, price, model_id, color, doors, seats, fuel_type, transmission, engine_volume, fuel_consumption,`power`)
VALUES
    ('Base XC90', '50000', '1', 'Black', '4', '5', 'Gasoline', 'Automatic', '2', '8.5', '250'),
    ('Premium XC90', '60000', '1', 'White', '4', '5', 'Gasoline', 'Automatic', '2.5', '9', '300'),
    ('Base XC60', '45000', '2', 'Blue', '4', '5', 'Gasoline', 'Automatic', '2', '8', '220'),
    ('Premium XC60', '55000', '2', 'Red', '4', '5', 'Gasoline', 'Automatic', '2.5', '8.5', '260'),
    ('Base S90', '48000', '3', 'Silver', '4', '5', 'Diesel', 'Manual', '2', '9', '200'),
    ('Premium S90', '58000', '3', 'Green', '4', '5', 'Diesel', 'Automatic', '2.5', '9.5', '240'),
    ('Base X5', '55000', '4', 'Gray', '4', '5', 'Gasoline', 'Automatic', '3', '9', '300'),
    ('Premium X5', '65000', '4', 'Black', '4', '5', 'Gasoline', 'Automatic', '3.5', '9.5', '350'),
    ('Base X6', '60000', '5', 'White', '4', '5', 'Diesel', 'Automatic', '3', '10', '320'),
    ('Premium X6', '70000', '5', 'Silver', '4', '5', 'Diesel', 'Automatic', '3.5', '10.5', '360'),
    ('Base C', '45000', '6', 'Blue', '4', '5', 'Gasoline', 'Manual', '2', '8.5', '180'),
    ('Premium C', '55000', '6', 'Red', '4', '5', 'Gasoline', 'Automatic', '2.5', '9', '220'),
    ('Base CLS', '60000', '7', 'Black', '4', '5', 'Gasoline', 'Automatic', '2.5', '9.5', '250'),
    ('Premium CLS', '70000', '7', 'White', '4', '5', 'Gasoline', 'Automatic', '3', '10', '280'),
    ('Base A4', '40000', '8', 'Silver', '4', '5', 'Diesel', 'Manual', '2', '8', '180'),
    ('Premium A4', '50000', '8', 'Black', '4', '5', 'Diesel', 'Automatic', '2.5', '8.5', '220'),
    ('Base A5', '55000', '9', 'Blue', '4', '5', 'Gasoline', 'Automatic', '2', '8.5', '230'),
    ('Premium A5', '65000', '9', 'Red', '4', '5', 'Gasoline', 'Automatic', '2.5', '9', '270'),
    ('Base A7', '60000', '10', 'Black', '4', '5', 'Diesel', 'Automatic', '3', '9', '280'),
    ('Premium A7', '70000', '10', 'White', '4', '5', 'Diesel', 'Automatic', '3.5', '9.5', '320'),
    ('Base A8', '65000', '11', 'Gray', '4', '5', 'Gasoline', 'Automatic', '3', '9', '300'),
    ('Premium A8', '75000', '11', 'Black', '4', '5', 'Gasoline', 'Automatic', '3.5', '9.5', '350'),
    ('Base 208', '30000', '12', 'White', '4', '5', 'Gasoline', 'Manual', '1.6', '7.5', '120'),
    ('Premium 208', '35000', '12', 'Blue', '4', '5', 'Gasoline', 'Automatic', '2', '8', '150'),
    ('Base 3008', '40000', '13', 'Gray', '4', '5', 'Gasoline', 'Manual', '1.8', '7', '140'),
    ('Premium 3008', '45000', '13', 'Black', '4', '5', 'Gasoline', 'Automatic', '2', '7.5', '170'),
    ('Base 408', '35000', '14', 'Silver', '4', '5', 'Diesel', 'Manual', '1.6', '7.5', '130'),
    ('Premium 408', '40000', '14', 'Red', '4', '5', 'Diesel', 'Automatic', '2', '8', '160'),
    ('Base Land-Cruiser', '60000', '15', 'Black', '4', '7', 'Diesel', 'Automatic', '4', '12', '280'),
    ('Premium Land-Cruiser', '70000', '15', 'White', '4', '7', 'Diesel', 'Automatic', '4.5', '13', '320'),
    ('Base Camry', '35000', '16', 'Blue', '4', '5', 'Gasoline', 'Manual', '2', '8', '180'),
    ('Premium Camry', '45000', '16', 'Red', '4', '5', 'Gasoline', 'Automatic', '2.5', '8.5', '220'),
    ('Base Corolla', '30000', '17', 'White', '4', '5', 'Gasoline', 'Manual', '1.8', '7.5', '120'),
    ('Premium Corolla', '40000', '17', 'Black', '4', '5', 'Gasoline', 'Automatic', '2', '8', '150'),
    ('Base Range-Rover', '80000', '18', 'Gray', '4', '5', 'Diesel', 'Automatic', '4', '12', '350'),
    ('Premium Range-Rover', '90000', '18', 'Black', '4', '5', 'Diesel', 'Automatic', '4.5', '13', '380'),
    ('Base Discovery', '70000', '19', 'Silver', '4', '7', 'Diesel', 'Automatic', '3', '10', '280'),
    ('Premium Discovery', '80000', '19', 'White', '4', '7', 'Diesel', 'Automatic', '3.5', '11', '320'),
    ('Base Defender', '60000', '20', 'Green', '4', '7', 'Diesel', 'Manual', '2.5', '9', '250'),
    ('Premium Defender', '70000', '20', 'Black', '4', '7', 'Diesel', 'Automatic', '3', '9.5', '290'),
    ('Base Panamera', '90000', '21', 'Red', '4', '5', 'Gasoline', 'Automatic', '3', '10', '320'),
    ('Premium Panamera', '100000', '21', 'White', '4', '5', 'Gasoline', 'Automatic', '3.5', '11', '360'),
    ('Base Cayenne', '80000', '22', 'Black', '4', '5', 'Gasoline', 'Automatic', '3', '10', '350'),
    ('Premium Cayenne', '90000', '22', 'Silver', '4', '5', 'Gasoline', 'Automatic', '3.5', '11', '380'),
    ('Base Cayman', '70000', '23', 'Blue', '2', '2', 'Gasoline', 'Automatic', '2', '8.5', '250'),
    ('Premium Cayman', '80000', '23', 'Red', '2', '2', 'Gasoline', 'Automatic', '2.5', '9', '300'),
    ('Base Forester', '35000', '24', 'Gray', '4', '5', 'Gasoline', 'Manual', '2', '8', '180'),
    ('Premium Forester', '45000', '24', 'Black', '4', '5', 'Gasoline', 'Automatic', '2.5', '8.5', '220'),
    ('Base Impreza', '30000', '25', 'White', '4', '5', 'Gasoline', 'Manual', '1.8', '7.5', '120'),
    ('Premium Impreza', '40000', '25', 'Blue', '4', '5', 'Gasoline', 'Automatic', '2', '8', '150'),
    ('Base Outback', '45000', '26', 'Black', '4', '5', 'Diesel', 'Manual', '2', '8.5', '180'),
    ('Premium Outback', '55000', '26', 'Green', '4', '5', 'Diesel', 'Automatic', '2.5', '9', '220'),
    ('Base Legacy', '40000', '27', 'Silver', '4', '5', 'Gasoline', 'Manual', '1.8', '7.5', '120'),
    ('Premium Legacy', '50000', '27', 'Black', '4', '5', 'Gasoline', 'Automatic', '2', '8', '150');





CREATE TABLE employee (
    employee_id INT auto_increment primary key,
    town VARCHAR(255),
   `password` INT,
    fib VARCHAR(255),
    number_of_the_phone VARCHAR(255),
    birthdate DATE
);





CREATE TABLE `zamovlennya` (
    `zamovlennya_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
    `employee_id` INT NOT NULL ,  
    `Марка` VARCHAR(45) NOT NULL,
    `Модель` VARCHAR(45) NOT NULL,
    `Комплектація` VARCHAR(100) NOT NULL,
    `Ціна` INT NOT NULL,
    `Дата оформлення замовлення` DATE NOT NULL,
    `ФІБ` VARCHAR(100) NOT NULL,
    `Місто проживання` VARCHAR(30)  NOT NULL,
    `РНОКПП` VARCHAR(20)  NOT NULL,
    `Номер паспорта` VARCHAR(30)  NOT NULL,
    `Номер телефона` VARCHAR(30) NOT NULL,
    `VIN` VARCHAR(30) NOT NULL,
    FOREIGN KEY (`employee_id`) REFERENCES `employee`(`employee_id`)
);





