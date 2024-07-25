DELIMITER $$

CREATE PROCEDURE borrow_book(
    IN p_empl_name VARCHAR(30),
    IN p_empl_surname VARCHAR(30),
    IN p_empl_lastname VARCHAR(30),
    IN p_num_of_subscription INT,
    IN p_nbook_isdate DATE,
    IN p_count_of_book INT,
    IN p_inventory_id INT
)
BEGIN
    DECLARE v_return_date DATE;
    DECLARE v_empl_id TINYINT;
    DECLARE v_book_count INT;

    SELECT empl_id INTO v_empl_id
    FROM employee
    WHERE empl_name = p_empl_name AND empl_surname = p_empl_surname AND empl_lastname = p_empl_lastname;

    SELECT count_of_book INTO v_book_count
    FROM book
    WHERE Inventory_id = p_inventory_id;

    IF v_book_count >= p_count_of_book THEN
        SET v_return_date = DATE_ADD(p_nbook_isdate, INTERVAL 14 DAY);

        INSERT INTO `Видача_книги` (num_of_subscription, Inventory_id, empl_id, nbook_isdate, nbook_retdate, count_of_book)
        VALUES (p_num_of_subscription, p_inventory_id, v_empl_id, p_nbook_isdate, v_return_date, p_count_of_book);

        UPDATE book
        SET count_of_book = count_of_book - p_count_of_book
        WHERE Inventory_id = p_inventory_id;
    ELSE
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Недостаточно книг для выдачи';
    END IF;
END$$

DELIMITER ;
call library.borrow_book('Тетяна', 'Петренко', 'Іванівна', 3, '2024-06-03', 10, 2);



DELIMITER $$
CREATE PROCEDURE return_book(
    IN p_id_of_rent INT,
    IN p_count_of_book INT
)
BEGIN
    DECLARE v_borrowed_count INT;
    DECLARE v_inventory_id INT;
    DECLARE v_num_of_subscription INT;
    DECLARE v_empl_id TINYINT;
    DECLARE v_nbook_retdate DATE;
    SELECT Inventory_id, num_of_subscription, empl_id, nbook_retdate, count_of_book 
    INTO v_inventory_id, v_num_of_subscription, v_empl_id, v_nbook_retdate, v_borrowed_count
    FROM Видача_книги
    WHERE id_of_rent = p_id_of_rent;
    IF v_borrowed_count >= p_count_of_book THEN
        UPDATE book
        SET count_of_book = count_of_book + p_count_of_book
        WHERE Inventory_id = v_inventory_id;

        INSERT INTO Повернення_книги (num_of_subscription, Inventory_id, empl_id, nbook_retdate, count_of_book)
        VALUES (v_num_of_subscription, v_inventory_id, v_empl_id, v_nbook_retdate, p_count_of_book);
        UPDATE Видача_книги
        SET count_of_book = count_of_book - p_count_of_book
        WHERE id_of_rent = p_id_of_rent;
    ELSE
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Invalid return count';
    END IF;
END$$

DELIMITER ;



DELIMITER $$

CREATE PROCEDURE get_books_by_title(
    IN p_book_name VARCHAR(40)
)
BEGIN
    SELECT * 
    FROM book
    WHERE book_name LIKE CONCAT('%', p_book_name, '%');
END$$

DELIMITER ;

DELIMITER $$
CREATE PROCEDURE get_books_by_author_full_name(
    IN p_author_name VARCHAR(30),
    IN p_author_surname VARCHAR(30)
)
BEGIN
    SELECT book.book_name 
    FROM book
    JOIN author ON book.author_id = author.author_id
    WHERE author.author_name = p_author_name AND author.author_surname = p_author_surname;
END$$

DELIMITER ;

DELIMITER $$

CREATE PROCEDURE get_books_by_publishing(
    IN p_publish_name VARCHAR(70)
)
BEGIN
    SELECT book.book_name 
    FROM book
    JOIN publishing ON book.publish_id = publishing.publish_id
    WHERE publishing.publish_name = p_publish_name;
END$$

DELIMITER ;

