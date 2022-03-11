START TRANSACTION;
USE madang;

SELECT * 
FROM   Book
WHERE  bookid=1;

UPDATE Book 
SET     price=price+100
WHERE  bookid=1;
-- 30초간 대기 하며 , 시간이 지나면 강제 종료됨
-- Error Code: 2013. Lost connection to MySQL server during query	30.000 sec
-- t1 이어서 실행

SELECT * 
FROM   Book
WHERE  bookid=1;

COMMIT;