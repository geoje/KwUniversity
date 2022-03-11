use madang
delimiter //
CREATE PROCEDURE InsertBook(
  IN myBookID INTEGER, 
  IN myBookName VARCHAR(40), 
  IN myPublisher VARCHAR(40), 
  IN myPrice INTEGER)
BEGIN
  INSERT INTO Book(bookid, bookname, publisher, price)
      VALUES(myBookID, myBookName, myPublisher, myPrice);
END;
//
delimiter ;

CALL InsertBook(13, '스포츠과학', '마당과학서적', 25000);
SELECT * FROM Book;