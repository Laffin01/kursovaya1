/*CREATE TABLE `car_showroom`.`listofcars` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `Марка` VARCHAR(45) NOT NULL,
  `Модель` VARCHAR(45) NOT NULL,
  `Рік випуску` YEAR(4) NOT NULL,
  `Комплектація` VARCHAR(45) NOT NULL,
  `Ціна` INT NOT NULL,
  PRIMARY KEY (`id`));

INSERT INTO listofcars (`Марка`, `Модель`, `Рік Випуску`, `Комплектація`,`Ціна`)
VALUES 
('Volvo', 'x','2023','Преміум',1000000),
('BMW', 'x5','2023','Преміум',1600000),
('Mercedes-Benz', 'cls','2022','Преміум',1900000),
('Porsche', 'Cayenne','2020','Преміум',5000000),
('Land-Rover', 'Range Rover','2021','Преміум',7000000)*/



/*
CREATE TABLE `car_showroom`.`zamovlennya` (
    `zamovlennya_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
`client_id` INT NOT NULL,  
  `Марка` VARCHAR(45) NOT NULL,
  `Модель` VARCHAR(45) NOT NULL,
  `Комплектація` VARCHAR(100) NOT NULL,
  `Ціна` INT NOT NULL,
  `Дата оформлення замовлення` DATE NOT NULL)
*/
/*ALTER TABLE _client RENAME TO employee;*/
ALTER TABLE employee CHANGE client_id employee_id int;





