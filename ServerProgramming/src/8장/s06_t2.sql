
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

START TRANSACTION;
USE madang;
SELECT SUM(price) 총액
FROM   Book;
 
 
UPDATE Book 
SET     price=price+500
WHERE  bookid=1;

SELECT SUM(price) 총액 
FROM   Book;

COMMIT;

-- > t1

