SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
START TRANSACTION;
USE madang;
SELECT SUM(price) 총액
FROM   Book;

-- 여기까지 실행해본 후 진행 

INSERT INTO Book VALUES (12, '테스트', '테스트출판사', 5500);

/* Lock t1 commit 30초 대기 후 종료 */
-- t1


SELECT SUM(price) 총액
FROM   Book;

COMMIT;
