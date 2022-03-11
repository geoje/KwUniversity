delimiter //
CREATE PROCEDURE AveragePrice(
  OUT AverageVal INTEGER)
BEGIN
  SELECT AVG(price) INTO AverageVal 
  FROM Book WHERE price IS NOT NULL;
END;
//
delimiter ;

/* 프로시저 AveragePrice를 테스트하는 부분 */
CALL AveragePrice(@myValue);
SELECT @myValue;