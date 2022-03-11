START TRANSACTION;
USE madang;

UPDATE Book 
SET     price=price+100
WHERE  bookid=1;

-- t2

UPDATE Book 
SET     price=price+100
WHERE  bookid=2;

-- …(대기상태)…
-- t2

COMMIT;

