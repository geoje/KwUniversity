INSERT INTO Book(bookid, bookname, price, publisher)
	   SELECT	bookid, bookname, price, publisher
	   FROM 	Imported_book;
       
select * from book;


