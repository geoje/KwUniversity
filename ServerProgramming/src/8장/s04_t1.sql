-- t1
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
START TRANSACTION;
USE madang;
SELECT * 
FROM   Users
WHERE  id=1;

-- > t2

SELECT * 
FROM   Users
WHERE  id=1;

commit;
-- 다음 실습을 위해 초기화
UPDATE Users 
SET     age=30
WHERE  id=1;