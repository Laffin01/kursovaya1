CREATE DATABASE library CHARACTER SET utf8mb4;

USE library;

CREATE TABLE author (
    author_id TINYINT AUTO_INCREMENT PRIMARY KEY, 
    author_name VARCHAR(30) NOT NULL,
    author_surname VARCHAR(30) NOT NULL
) CHARACTER SET utf8mb4;

CREATE TABLE genre (
    genre_id TINYINT auto_increment PRIMARY KEY, 
    genre_name VARCHAR(30) NOT NULL
) CHARACTER SET utf8mb4;

CREATE TABLE publishing (
    publish_id TINYINT AUTO_INCREMENT PRIMARY KEY, 
    publish_name VARCHAR(70) NOT NULL, 
    publish_address VARCHAR(90) NOT NULL
) CHARACTER SET utf8mb4;

CREATE TABLE book (
    Inventory_id INT auto_increment PRIMARY KEY NOT NULL,
    book_name VARCHAR(40) NOT NULL, 
    author_id TINYINT, 
    publish_id TINYINT, 
    book_year INT(4), 
    genre_id TINYINT,
    count_of_book int not null,
    FOREIGN KEY (author_id) REFERENCES author(author_id),
    FOREIGN KEY (publish_id) REFERENCES publishing(publish_id),
    FOREIGN KEY (genre_id) REFERENCES genre(genre_id)
) CHARACTER SET utf8mb4;

CREATE TABLE post (
    post_id TINYINT AUTO_INCREMENT PRIMARY KEY, 
    post_name VARCHAR(30) NOT NULL, 
    post_salary INT NOT NULL
) CHARACTER SET utf8mb4;

CREATE TABLE reader (
   num_of_subscription int auto_increment PRIMARY KEY not null, 
    read_name VARCHAR(30) NOT NULL, 
    read_surname VARCHAR(30) NOT NULL,
    read_address VARCHAR(90) NOT NULL, 
    read_birth DATE NOT NULL, 
    read_num BIGINT, 
    read_passport INT NOT NULL,
    read_lastname VARCHAR(30) NOT NULL
    
) CHARACTER SET utf8mb4;

CREATE TABLE employee (
    empl_id TINYINT auto_increment PRIMARY KEY,  
    empl_name VARCHAR(30) NOT NULL,  
    empl_birth DATE NOT NULL, 
    empl_address VARCHAR(90) NOT NULL,  
    empl_num BIGINT, 
    empl_passport INT NOT NULL, 
    post_id TINYINT,
    empl_surname VARCHAR(30) NOT NULL,
    empl_lastname VARCHAR(30) NOT NULL,
    FOREIGN KEY (post_id) REFERENCES post(post_id)
) CHARACTER SET utf8mb4;



INSERT INTO publishing ( publish_name, publish_address) VALUES
( 'Видавництво Старого Лева', '79000, м. Львів, вул. Старознесенська, 24-26.'),
( 'Ранок', '61145, м. Харків, вул. Космічна, 21а'),
( 'Видавнича група "Основа"', '61057, м. Харків, вул. Плеханівська, 66, Харків'),
( 'Видавничий дім "Школа"', '61204, м. Харків, вулиця Ахсарова, буд. 13, кв. 544'),
( 'Теза', '21027, м. Вінниця, вулиця Космонавтів, будинок 63'),
( 'Портал', '04071, м. Київ, вулиця Воздвиженська, 45-49'),
( 'А-ба-ба-га-ла-ма-га', '01024, м. Київ, вулиця Басейна, 1/2'),
( 'Віват', '61000, м. Харків, вулиця Микити Гомоненка, 10');

INSERT INTO genre( genre_name)
VALUES 
( 'Пригоди'),
('Драма'),
('Поема'),
('Роман'),
('Історична проза'),
('Повість'),
( 'Трагікомедія'),
( 'Казка'),
( 'Новела');

INSERT INTO author (author_name, author_surname) VALUES
( 'Всеволод', 'Нестайко'),
( 'Леся', 'Українка'),
( 'Тарас', 'Шевченко'),
( 'Іван', 'Франко'),
( 'Ліна', 'Костенко'),
('Михайло', 'Стельмах'),
( 'Пантелеймон', 'Куліш'),
('Марко', 'Вовчок'),
('Олена', 'Пчілка'),
( 'Іван', 'Карпенко-Карий'),
( 'Василь', 'Симоненко'),
( 'Григір', 'Тютюнник'),
('Євген', 'Гуцало'),
( 'Володимир', 'Винниченко'),
( 'Емма', 'Андієвська');

INSERT INTO post ( post_name, post_salary) VALUES
('Бібліотекар', 12000),
('Старший бібліотекар', 14000),
('Головний бібліотекар', 16000),
('Методист бібліотеки', 10500);

INSERT INTO reader ( read_name, read_surname, read_address, read_birth, read_num, read_passport, read_lastname) VALUES
( 'Марина', 'Сидоренко', 'м. Харків, вулиця Сумська, 20', '2003-03-12', 380957478833, 75683654, 'Петрівна'),
('Петро', 'Матвієнко', 'м. Харків, вулиця Холодногірська, 55', '2005-09-20', 380665437098, 34987465, 'Валерійович'),
( 'Володимир', 'Павленко', 'м. Харків, вулиця Китаєнка, 67', '2002-07-15', 380931116538, 87565978, 'Миколайович'),
( 'Олена', 'Іваненко', 'м. Харків, вулиця Полтавський шлях, 125', '2004-12-05', 380671239548, 54839847, 'Ігорівна'),
('Андрій', 'Коваленко', 'м. Харків, вулиця Шевченка, 78', '2003-05-22', 380932456871, 68743259, 'Віталійович'),
( 'Ірина', 'Мельник', 'м. Харків, вулиця Данилевського, 21', '2002-08-10', 380997654321, 92837465, 'Олександрівна'),
( 'Михайло', 'Стеценко', 'м. Харків, вулиця Мироносицька, 45', '2005-02-17', 380637894512, 23874659, 'Григорович'),
( 'Світлана', 'Гончаренко', 'м. Харків, вулиця Гоголя, 33', '2004-11-01', 380508765432, 43598274, 'Анатоліївна'),
( 'Олександр', 'Тарасенко', 'м. Харків, вулиця Пушкінська, 123', '2003-01-25', 380504321098, 54798321, 'Сергійович'),
( 'Наталія', 'Лисенко', 'м. Харків, вулиця Плеханівська, 92', '2005-06-18', 380971234567, 19876543, 'Михайлівна'),
( 'Юрій', 'Кравченко', 'м. Харків, вулиця Отакара Яроша, 8', '2002-10-30', 380931234567, 98432176, 'Петрович');

INSERT INTO employee (empl_name, empl_birth, empl_address, empl_num, empl_passport, post_id, empl_surname, empl_lastname) VALUES
('Тетяна', '1985-02-14', 'м. Харків, проспект Науки, 5', 380951234567, 12345678, 1, 'Петренко', 'Іванівна'),
('Олексій', '1978-06-23', 'м. Харків, вулиця Свободи, 9', 380931234567, 87654321, 4, 'Коваль', 'Володимирович'),
('Наталія', '1982-11-30', 'м. Харків, проспект Гагаріна, 11', 380671234567, 11223344, 3, 'Левченко', 'Сергіївна'),
('Ірина', '1990-04-15', 'м. Харків, вулиця Мироносицька, 16', 380501234567, 33445566, 1, 'Сидоренко', 'Андріївна'),
('Дмитро', '1985-09-10', 'м. Харків, вулиця Сумська, 20', 380931234567, 99887766, 2, 'Кузьменко', 'Петрович');

INSERT INTO book (book_name, author_id, publish_id, book_year, genre_id, count_of_book)
VALUES 
( 'Тореадори з Васюківки', '1', '3', '1999', '1', 10),
( 'Лісова пісня', '2', '6', '1983', '3', 15),
( 'Давня казка', '2', '1', '1993', '4', 5),
( 'Берестечко', '5', '5', '1999', '6', 7),
( 'Маруся Чурай', '5', '2', '1979', '3', 9),
( 'Катерина', '3', '1', '1989', '8', 12),
( 'Іван Підкова', '3', '3', '1971', '9', 6),
( 'Хатка у березовому лісі', '6', '8', '1984', '3', 14),
( 'Гуси-лебеді летять', '6', '7', '2001', '6', 13),
( 'Хліб і сіль', '6', '3', '1981', '8', 10),
('Чорна рада', '7', '6', '1967', '4', 8),
( 'Огненний змій', '7', '6', '2002', '4',11),
( 'Дев `ять братів і десята сестриця Галя', '8', '1', '2005', '4', 10),
( 'Маруся', '8', '2', '1987', '8', 9),
( 'Сто тисяч', '10', '4', '1989', '2', 7),
( 'Мартин Боруля', '10', '3', '1986', '1', 6),
( 'Цар Плаксій та Лоскотон', '11', '7', '2004', '7', 5),
( 'Подорож в Країну Навпаки', '11', '6', '2005', '4', 4),
('Зав`язь', '12', '7', '1986', '5', 3),
( 'Три зозулі з поклоном', '12', '3', '1976', '7', 2),
( 'Климко', '12', '8', '2001', '9',1),
('Шкільний хліб', '13', '1', '1998', '1', 2),
( 'Журавлі високі пролітають', '13', '2', '1977', '4',3),
( 'Записки кирпатого Мефістофеля', '14', '7', '1916', '8', 4),
( 'Великий Молох', '14', '5', '1980', '5', 5),
( 'Щаблі щастя', '14', '8', '2007', '2', 6),
( 'Казка про Галайла', '15', '4', '2000', '7', 7),
( 'Журавель та Чапля', '9', '3', '2006', '6', 8);

CREATE TABLE Видача_книги (
    id_of_rent INT NOT NULL AUTO_INCREMENT,
    num_of_subscription INT,
    nbook_isdate DATE NOT NULL,
    empl_id TINYINT,
    nbook_retdate DATE,
    Inventory_id INT NOT NULL,
    count_of_book INT NOT NULL,
    FOREIGN KEY (Inventory_id) REFERENCES book(Inventory_id),
    FOREIGN KEY (num_of_subscription) REFERENCES reader(num_of_subscription),
    FOREIGN KEY (empl_id) REFERENCES employee(empl_id),
    PRIMARY KEY (id_of_rent)
) CHARACTER SET utf8mb4;


CREATE TABLE Повернення_книги (
    num_of_subscription INT NOT NULL,
    nbook_retdate DATE,
    empl_id TINYINT,
    Inventory_id INT NOT NULL,
    count_of_book INT NOT NULL,
    FOREIGN KEY (num_of_subscription) REFERENCES reader(num_of_subscription),
    FOREIGN KEY (empl_id) REFERENCES employee(empl_id),
    FOREIGN KEY (Inventory_id) REFERENCES book(Inventory_id)
) CHARACTER SET utf8mb4;







