SELECT	price 'C 수강료'
FROM	SummerPrice
WHERE	class LIKE 'C';

DELETE	FROM	SummerEnroll 
WHERE	sid=200;

SELECT	*
FROM	SummerEnroll;

/* C 강좌의 수강료가 존재하는지 확인 */
SELECT	price "C 수강료"
FROM	SummerPrice
WHERE	class LIKE 'C';
