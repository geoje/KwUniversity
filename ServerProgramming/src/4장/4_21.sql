CREATE VIEW	vw_Orders (orderid, custid, name, bookid, bookname, saleprice, orderdate)
AS SELECT		od.orderid, od.custid, cs.name,
			od.bookid, bk.bookname, od.saleprice, od.orderdate
	FROM		Orders od, Customer cs, Book bk
	WHERE		od.custid=cs.custid AND od.bookid=bk.bookid;
    

SELECT	orderid, bookname, saleprice
FROM	vw_Orders
WHERE	name ='김연아';    