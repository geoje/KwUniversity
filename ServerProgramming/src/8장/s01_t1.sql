START TRANSACTION;
USE madang;

SELECT * 
FROM   Book
WHERE  bookid=1;

UPDATE Book 
SET     price=7100
WHERE  bookid=1;

-- t2 실행

SELECT * 
FROM   Book
WHERE  bookid=1;

-- t2 대기 확인
COMMIT;

-- t2쿼리 실행