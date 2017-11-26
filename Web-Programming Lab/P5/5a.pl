#!/usr/bin/perl
use CGI ":standard";
print header();
print start_html("About Server");
print h2("Server Information");
print hr;
print "Server Name:$ENV{'SERVER_NAME'}",br;
print "Running on Port:$ENV{'SERVER_PORT'}",br;
print "Server Software:$ENV{'SERVER_SOFTWARE'}",br;
print "Server Protocol:$ENV{'GATEWAY_INTERFACE'}",br;
print "CGI Version:$ENV{'GATEWAY_INTERFACE'}",br;
print end_html();
