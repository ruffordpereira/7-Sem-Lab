#!/usr/bin/perl
use CGI ":standard";
use DBI; #DataBase Independent Interface
print header();
print start_html("DataBase Information");
printf "<body bgcolor=white>";
#DBI:driver :dbName, userid, pwd
$dbh=DBI->connect("DBI:mysql:studentdbA1","root","");
$name=param("name");
$age=param("age");
#3steps to perform any operation on db:
#Preparing SQL statement - done using prepare() API.
#Executing SQL query - execute() API.
#Releasing Statement handle if no longer needed - finish() API
$qh=$dbh->prepare("insert into student
values('$name','$age')");
$qh->execute();
$qh=$dbh->prepare("select *from student");
$qh->execute();
print "<table border=2 width =300 >";
print caption(h2("Table Contents: "));
print Tr(th(["Name","Age"]));
#fetch the resultant rows one by one.while(($name,$age)=$qh->fetchrow())
{
print Tr(td([$name,$age]));
}
print "</table>";
$qh->finish();
$dbh->disconnect();
print end_html();
