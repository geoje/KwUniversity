SELECT 	bookname '제목', CHAR_LENGTH(bookname) '문자수',	
		LENGTH(bookname) '바이트수'
FROM 	Book
WHERE 	publisher='굿스포츠';