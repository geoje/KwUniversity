SELECT	orderid '주문번호', orderdate '주문일', ADDDATE(orderdate, INTERVAL 10 DAY) '확정'
FROM	Orders;