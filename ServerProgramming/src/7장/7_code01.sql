DROP TABLE  IF EXISTS Summer; /* 기존 테이블이 있으면 삭제 */

CREATE TABLE Summer
( sid   INTEGER,
  class VARCHAR(20),
  price INTEGER
);

INSERT INTO Summer VALUES (100, 'FORTRAN', 20000);
INSERT INTO Summer VALUES (150, 'PASCAL', 15000);
INSERT INTO Summer VALUES (200, 'C', 10000);
INSERT INTO Summer VALUES (250, 'FORTRAN', 20000);

/* 생성된 Summer 테이블 확인 */
SELECT *
FROM   Summer;