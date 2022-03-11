
ALTER TABLE Orders ADD bname VARCHAR(40);

UPDATE	Orders
SET		bname=(SELECT	bookname
           		    FROM	Book
 			    WHERE	Book.bookid=Orders.bookid);
                
select * from orders;