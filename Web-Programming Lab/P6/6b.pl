#!/usr/bin/perl
use CGI ":standard";
print header();
print start_html(-title=>"WebPage Counter",-bgcolor=>"yellow",-
text=>"blue");
#keep count of visitors in a file -count.txt.
#everytime perl executes, open count.txt, read its current value,
#increment the file value and write it back to file.
#open file in read mode
open(FILE,"<count.txt");
#read file content into $count
$noOfVisitors=<FILE>;
close(FILE);
$noOfVisitors++;
#open file in write mode
open(FILE,">count.txt");
#write updated count back to file.
print FILE "$noOfVisitors";
close(FILE);print b(" This Page Has Been Visited $noOfVisitors times");
print end_html();
