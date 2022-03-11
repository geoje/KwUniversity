CREATE OR REPLACE VIEW vw_Customer (custid, name, address)
AS  SELECT		custid, name, address
	FROM		Customer
	WHERE		address LIKE '%영국%';
    
SELECT	*
FROM	vw_Customer;    