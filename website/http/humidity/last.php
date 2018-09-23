<?php
/**
 * Created by PhpStorm.
 * User: Piotr Meller
 * Date: 21.09.2018
 * Time: 15:21
 */

include '../mysql_login.php';

$interval = $_REQUEST["interval"];


$sql ="select id, humidity, Date, TIME_FORMAT(Time,'%H:%i') as Time from logs where TimeStamp >= DATE_SUB(NOW(),INTERVAL ".$interval." HOUR)";
$rows = array();
if ($result = mysqli_query($conn, $sql)) {

    while ($row = mysqli_fetch_assoc($result)) {

        $rows[]=$row;
    }
    mysqli_free_result($result);
}
echo json_encode($rows);
mysqli_close($conn);