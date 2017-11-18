<html>
<body>
<?php
$con=mysql_connect("localhost","root","") or die("error ==>".mysql_error());
mysql_select_db("address");
$sql="INSERT INTO student VALUES('$_POST[name]','$_POST[addr1]','$_POST[addr2]','$_POST[email]')";
mysql_query($sql) or die("Error ==>".mysql_error());
echo "1 record inserted successfully";
mysql_close($con);
?>
<form action="http://localhost/cgi-bin/nov/search.php" method="post">
<br>
<hr>
Enter the name to be searched for :
Name:<input type="text" name="searchname"/>
<input type="submit"/>
</form>
</body></html>