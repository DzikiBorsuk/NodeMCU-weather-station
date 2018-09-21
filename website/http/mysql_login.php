<?php
/**
 * Created by PhpStorm.
 * User: Piotr Meller
 * Date: 20.09.2018
 * Time: 20:54
 */

$servername = "localhost";
$username = "root";
$password = "qwerty";
$dbname = "weather_station";

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Database connection failed: " . $conn->connect_error);
}