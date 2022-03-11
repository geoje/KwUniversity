CREATE VIEW	vw_Customer
AS SELECT		*
	FROM		Customer
	WHERE		address LIKE '%대한민국%';
    
    
SELECT	*
FROM	vw_Customer;