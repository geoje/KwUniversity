SELECT	SUM(saleprice) 'total'
FROM	Orders
WHERE	custid IN (SELECT     custid
			   FROM	Customer
			   WHERE	address LIKE '%대한민국%');