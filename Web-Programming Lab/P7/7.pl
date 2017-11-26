#!/usr/bin/perl
use CGI ":standard";
#add http header to reload page every second
print "Refresh: 1\n";
print "Content-Type:text/html\n\n";
print start_html(-title=>"Digital Clock");
($s,$m,$h)=localtime(time);
print p("The Currnet System Time Is $h:$m:$s");
print hr;
print p("In Words: $h hours $m minutes $s seconds");
print end_html();
