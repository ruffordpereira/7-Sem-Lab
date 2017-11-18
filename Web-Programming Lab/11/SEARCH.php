<html>
<body>
<?php
$con=mysql_connect("localhost","root","") or die("error ==>".mysql_error());
mysql_select_db("address");
 $result=mysql_query("SELECT * FROM student WHERE name='$_POST[searchname]'") or die("Error==>".mysql_error());
 $no_of_rows=mysql_num_rows($result);
 if($no_of_rows==0)
	echo"No Matching record";
else
{
	echo"<table border='1'>
	<tr>
	<th>Name</th>
	<th>Address1</th>
	<th>Address2</th>
	<th>Email</th>
	</tr>";
	while($rw=mysql_fetch_row($result))
	{
		echo "<tr>";
		echo "<td>" .$rw[0] ."</td>";
		echo "<td>" .$rw[1] ."</td>";
		echo "<td>" .$rw[2] ."</td>";
		echo "<td>" .$rw[3] ."</td>";
		echo "</tr>";
	}
	echo"</table>";
}
mysql_close($con);
?>
</body>
</html>