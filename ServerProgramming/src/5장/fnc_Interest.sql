delimiter //
CREATE FUNCTION fnc_Interest(
  Price INTEGER) RETURNS INT  
BEGIN
  DECLARE myInterest INTEGER;
-- 가격이 30,000원 이상이면 10%, 30,000원 미만이면 5%
  IF Price >= 30000 THEN SET myInterest = Price * 0.1;
  ELSE SET myInterest := Price * 0.05;
  END IF;
  RETURN myInterest;
END; //
delimiter ;

/* Orders 테이블에서 각 주문에 대한 이익을 출력 */
SELECT custid, orderid, saleprice, fnc_Interest(saleprice) interest 
FROM Orders;