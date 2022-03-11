SELECT	SUBSTR(name, 1, 1) '성', COUNT(*) '인원'
FROM	Customer
GROUP BY	SUBSTR(name, 1, 1);

