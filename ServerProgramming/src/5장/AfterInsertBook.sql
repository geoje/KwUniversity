delimiter //
CREATE TRIGGER AfterInsertBook 
  AFTER INSERT ON Book FOR EACH ROW
BEGIN  
  DECLARE average INTEGER;
  INSERT INTO Book_log 
    VALUES(new.bookid, new.bookname, new.publisher, new.price);
END;
//
delimiter ;

/* 삽입한 내용을 기록하는 트리거 확인 */
INSERT INTO Book VALUES(14, '스포츠 과학 1', '이상미디어', 25000);
SELECT * FROM Book WHERE BOOKID=14;
SELECT * FROM Book_log  WHERE BOOKID_L='14' ; -- 결과 확인