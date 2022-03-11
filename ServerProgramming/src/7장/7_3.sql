/* FORTRAN 강좌 수강료 수정 */
UPDATE	Summer
SET		price=15000
WHERE	class='FORTRAN';

SELECT	*
FROM	Summer;


SELECT	DISTINCT price 'FORTRAN 수강료'
FROM	Summer
WHERE	class LIKE 'FORTRAN';

/* 다음 실습을 위해 FORTRAN 강좌의 수강료를 다시 20,000원으로 복구 */
UPDATE	Summer
SET		price=20000
WHERE	class LIKE 'FORTRAN';

/* 만약 UPDATE 문을 다음과 같이 작성하면 데이터 불일치 문제가 발생함 */
UPDATE	Summer
SET		price=15000
WHERE	class LIKE 'FORTRAN' AND sid=100;

/* Summer 테이블을 조회해보면 FORTRAN 강좌의 수강료가 1건만 수정되었음 */
SELECT	*
FROM	Summer;

/* FORTRAN 수강료를 조회하면 두 건이 나옴(데이터 불일치 문제 발생) */
SELECT	price 'FORTRAN 수강료'
FROM	Summer
WHERE	class LIKE 'FORTRAN';

/* 다음 실습을 위해 FORTRAN 강좌의 수강료를 다시 20,000원으로 복구 */
UPDATE	Summer
SET		price=20000
WHERE	class LIKE 'FORTRAN';

/* 다음 실습을 위해 sid가 NULL인 투플 삭제 */
DELETE
FROM	Summer
WHERE	sid IS NULL;