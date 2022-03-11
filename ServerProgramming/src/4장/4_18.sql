SELECT	orderid, saleprice
FROM	Orders
WHERE	saleprice > ALL (SELECT saleprice
				  FROM   Orders
				  WHERE custid='3');