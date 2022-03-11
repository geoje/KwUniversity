/* 자바 강좌 삽입 */
INSERT INTO Summer VALUES (NULL, 'JAVA', 25000);

/* Summer 테이블 조회 */
SELECT	*
FROM	Summer;

/* NULL 값이 있는 경우 주의할 질의 : 투플은 5 개이지만 수강학생은 총 4 명임 */
SELECT	COUNT(*) '수강인원'
FROM	Summer;

SELECT	COUNT(sid) '수강인원'
FROM	Summer;

SELECT	COUNT(*) '수강인원'
FROM	Summer
WHERE	sid IS NOT NULL;