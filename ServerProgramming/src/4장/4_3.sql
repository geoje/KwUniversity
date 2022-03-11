SELECT	custid '고객번호', ROUND(SUM(saleprice)/COUNT(*), -2) '평균금액'
FROM	Orders
GROUP BY	custid;



-- 두 문자열을 연결
select CONCAT('마당', ' 서점');
-- 대상 문자열을 모두 소문자로 변환
select LOWER('MR. SCOTT') ;
-- 대상 문자열의 왼쪽부터 지정한 자리수까지 지정한 문자로 채움
select  LPAD('Page 1', 10, '*');
-- 대상 문자열의 지정한 문자를 원하는 문자로 변경
select  REPLACE('JACK & JUE', 'J', 'BL') ;
-- 대상 문자열의 오른쪽부터 지정한 자리수까지 지정한 문자로 채움
select  RPAD('AbC', 5, '*');
-- 대상 문자열의 지정된 자리에서부터 지정된 길이만큼 잘라서 반환
select  SUBSTR('ABCDEFG', 3, 4);
-- 대상 문자열의 양쪽에서 지정된 문자를 삭제
-- (문자열만 넣으면 기본값으로 공백 제거)
select  TRIM('=' FROM '==BROWNING==');
-- 대상 문자열을 모두 대문자로 변환
select  UPPER('mr. scott') ;
-- 대상 알파벳 문자의 아스키 코드 값을 반환
select  ASCII('D') ;
-- 대상 문자열의 글자 수를 반환
select  LENGTH('CANDIDE');
-- 한글과 같은 multi byte 문자열의 글자 수를 반환
select  CHAR_LENGTH('데이터');
