#!/usr/bin/perl
#CGI Module consists of useful pre-programmed functions web programming
use CGI ":standard";
#declare a pre-defined set of messages in an array . @->array
@msgs=("Welcome to Web Programming Lab"," Have A Nice Time In Lab ",
"Practice All The Programs", "Well Done, Have A Good Day ");
$range=4; #no of values in array
#generate a random no [0-3 range], and display that message to the user
$random_number = int(rand($range));
#if any parameters(user's name) was passed when this file was requested
if(param() == null)
{
#if no param is received when this page was requested ,display the
# fetch_user details webpage.
print header();
print start_html("Fetch User Details");
print start_form(),
label("Enter Name:"),
textfield(-name=>"name",-value=>" "),
submit(-value=>"Greet"),
reset();
print end_form();
print end_html();
}
else
{
#create the webpage that display the greet message to user.
print header();print start_html("Greetings");
$username=param("name");
print b("Hello $username, $msgs[$random_number]"),br();
print start_form();
print submit(-value=>"Back");
print end_form();
print end_html();
}
