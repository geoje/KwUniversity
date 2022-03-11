SELECT	price+100
FROM	Mybook
WHERE	bookid=3; 

SELECT	SUM(price), AVG(price), COUNT(*), COUNT(price)
FROM	Mybook; 

SELECT	SUM(price), AVG(price), COUNT(*)
FROM	Mybook
WHERE	bookid >= 4;

SELECT	*
FROM	Mybook
WHERE	price IS NULL;

SELECT	*
FROM	Mybook
WHERE	price='';

