<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<h2><blockquote> 마당서점 도서목록 </blockquote></h2>
<?php
	$conn = mysqli_connect('localhost', 'madang', 'madang', 'madang');
	if (mysqli_connect_error($conn)){
		echo 'Connection Error';
		exit();
	}

	$sql = "SELECT * FROM Book";
	$result = mysqli_query($conn, $sql);

	echo '<table border=1><tr><td>BOOKNAME</td><td>PUBLISHER</td><td>PRICE</td></tr> ';
	while($row = mysqli_fetch_array($result)) {
		echo ('<tr><td><b>
			<a href="bookview.php?id='.$row['bookid'].'">'
			.$row['bookname'].'</a></b></td><td>'
			.$row['publisher'].' </td><td> '
			.$row['price'].'</td></tr>'); 
	}
	echo '</table><p>';

?>