CREATE USER mdguest2  IDENTIFIED BY 'mdguest2';
   # mdguest2 사용자 생성은 User 테이블을 확인해본다.
SELECT * FROM User WHERE User LIKE 'mdguest2';
