SELECT	cs.name, SUM(od.saleprice) 'total'
FROM	(SELECT   custid, name
		 FROM     Customer
		 WHERE   custid <= 2) cs,
		Orders	od
WHERE	cs.custid=od.custid
GROUP BY	cs.name;