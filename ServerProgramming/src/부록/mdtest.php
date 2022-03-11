<?php
header("Content-Type:text/html;charset=utf-8");
echo "php-mysql madang db 연결 테스트<br>";

$db = mysqli_connect("localhost", "madang", "madang", "madang");
mysqli_set_charset($db, 'utf8'); 
echo "db character set: " . mysqli_character_set_name($db) . "<BR>";

if($db){
    echo "db 접속 : 성공<br>";
}
else{
    echo "db 접속 : 실패<br>";
}

$result = mysqli_query($db, 'SELECT bookname from book where bookid=1');

$data = mysqli_fetch_assoc($result);
echo $data['bookname'];
?> 