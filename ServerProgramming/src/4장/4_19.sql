SELECT	SUM(saleprice) 'total'
FROM	Orders od
WHERE	EXISTS (SELECT  *
			 FROM	   Customer cs
			 WHERE	   address LIKE '%대한민국%' AND cs.custid=od.custid);