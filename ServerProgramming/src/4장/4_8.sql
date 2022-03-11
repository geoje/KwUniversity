SELECT	orderid '주문번호', STR_TO_DATE(orderdate, '%Y-%m-%d %M') '주문일', custid '고객번호', bookid '도서번호'
FROM	Orders
WHERE   orderdate=DATE_FORMAT('20140707', '%Y%m%d');