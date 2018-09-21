<?php
/**
 * Created by PhpStorm.
 * User: Piotr Meller
 * Date: 21.09.2018
 * Time: 15:21
 */

include '../mysql_login.php';


$sql ="select * from logs where TimeStamp >= DATE_SUB(NOW(),INTERVAL 12 HOUR)";
$rows = array();
if ($result = mysqli_query($conn, $sql)) {

    while ($row = mysqli_fetch_assoc($result)) {

        $rows[]=$row;
    }
    mysqli_free_result($result);
}
echo json_encode($rows);
mysqli_close($conn);

