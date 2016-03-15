<?php
$database="knxandroid";
$username="androidknx";
$password="password78";

$user=$_GET['user'];
$pass=$_GET['pass'];
$project=$_GET['project'];

mysql_connect("localhost",$username,$password);
@mysql_select_db($database) or die( "Err: Unable to select database");

$query = "SELECT fld_data FROM clients WHERE fld_username='$user' AND fld_password='$pass' AND fld_project='$project'";
$result=mysql_query($query);
if (!$result) {
	echo "query error";
}
else {
	while($row = mysql_fetch_array($result,MYSQL_BOTH))
	{
		echo $row['fld_data'];
	}
}
mysql_close();
?>