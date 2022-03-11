SELECT	(SELECT    name
	  	 FROM	     Customer cs
		 WHERE    cs.custid=od.custid) 'name', SUM(saleprice) 'total'
FROM	Orders od
GROUP BY	od.custid;