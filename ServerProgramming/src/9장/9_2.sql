CREATE USER mdguest@'localhost' IDENTIFIED BY 'mdguest';

# mdguest 사용자 생성은 User 테이블을 확인해본다.
SELECT * FROM User WHERE User LIKE 'mdguest';
