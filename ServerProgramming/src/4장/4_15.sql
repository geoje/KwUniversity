SELECT	orderid, saleprice
FROM	Orders
WHERE	saleprice <= (SELECT AVG(saleprice)
			      FROM   Orders);