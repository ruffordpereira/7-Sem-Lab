<html>
<body bgcolor="white">
<?php
date_default_timezone_set('Asia/Calcutta');
$twomonths=60*60*24*60+time();

setcookie("lastvisit1",date("G:i:s-m/d/y"),$twomonths);
if(isset($_COOKIE["lastvisit1"]))
{
	$visit1=$_COOKIE["lastvisit1"];
	print "your last visit was $visit1";
}
else
	print"you got stale cookies";
?>

</body></html>