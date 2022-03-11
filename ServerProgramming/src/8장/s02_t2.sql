START TRANSACTION;
USE madang;
UPDATE Book 
SET     price=price*1.1
WHERE  bookid=2;

-- t1

UPDATE Book 
SET     price=price*1.1
WHERE  bookid=1;

-- Deadlock
--	Error Code: 1213. Deadlock found when trying to get lock; try restarting transaction	0.062 sec


COMMIT;

