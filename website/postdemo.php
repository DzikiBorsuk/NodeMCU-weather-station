<?php
	$servername="localhost";
	$username="root";
	$password="qwerty";
	$dbname="weather_station";
	
	$conn=new mysqli($servername,$username,$password,$dbname);
	if($conn->connect_error)
	{
		die("Database connection failed: " . $conn->connect_error);
	}
	date_default_timezone_set('Europe/Berlin');
	$d=date("Y-m-d");
	$t=date("H:i:s");

    //$datetime = date_create()->format('Y-m-d H:i:s');

	if(!empty($_POST['temperature']) && !empty($_POST['pressure'])&& !empty($_POST['altitude']) && !empty($_POST['humidity'])&& !empty($_POST['gas']))
    {
    	$temperature = $_POST['temperature'];
    	$pressure = $_POST['pressure'];
		$altitude = $_POST['altitude'];
		$humidity = $_POST['humidity'];
		$gas = $_POST['gas'];
		$dust = $_POST['dust'];
		
 
	    $sql = "INSERT INTO logs (temperature, pressure, altitude, humidity, gas, dust, Date, Time)
		
		VALUES ('".$temperature."', '".$pressure."', '".$altitude."', '".$humidity."', '".$gas."', '".$dust."', '".$d."','".$t."')";
 
		if ($conn->query($sql) === TRUE) {
		    echo "OK";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}
	else
	{
		echo "To co przychodzi jest puste!:(";
	}
	$conn->close();
	
?>