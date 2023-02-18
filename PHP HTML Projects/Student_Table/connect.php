<?php
/* default xampp mysql settings might change if the settings of the pc
 in use of the program were altered from the default*/
$dbServername = "localhost";
$dbUsername = "root";
$dbPassword = "";
$dbName = "dbschool";

$con = mysqli_connect($dbServername, $dbUsername, $dbPassword, $dbName);
?>