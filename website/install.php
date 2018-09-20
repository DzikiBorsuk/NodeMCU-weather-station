<?php

	//database creation
	$servername="localhost";
	$username="root";
	$password="";
	
	//create connection
	$conn=new mysqli($servername,$username,$password);
	//Check connection
	if($conn->connect_error)
	{
		die("Unable to connect" . $conn->connect_error); //zwraca jaki error wystapil! die rowniez zamyka skrypt
	}
	//create database
	$sql="Create database sensorsd";
	if($conn->query($sql)===true) //jest rowny i tego samego typu! -operator scislego porownania
	{
		echo "Database created succesfully";
	}	
	else
	{
		echo "Problems with creating database:(" .$conn->error;
	}
	$conn->close();
	
	echo "<br>";
	
	//connect to database and create table
	$servername="localhost";
	$username="root";
	$password="";
	$dbname="sensorsd";
	
	//create connection
	$conn=new mysqli($servername,$username,$password,$dbname);
	//check connection
	if($conn->connect_error)
	{
		die("Connection failed" . $conn->connect_error);
	}
	
	//sql create table
	$sql = "CREATE TABLE logs (
	id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
	temperature VARCHAR(10),
	pressure VARCHAR(10),
	altitude VARCHAR(10),
	humidity VARCHAR(10),
	gas VARCHAR(10),
	dust VARCHAR(10),
	`Date` DATE NULL,
	`Time` TIME NULL, 
	`TimeStamp` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
	)";
	
	if($conn->query($sql)===TRUE)
	{
		echo "Table logs created succesfully";
	}
	else
	{
		echo "Table logs are not created succesfully" . $conn->error;
	}
	
	$conn->close();
?>
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	
	
	
	
	
	
	
	
	