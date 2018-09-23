<?php
/**
 * Created by PhpStorm.
 * User: Piotr Meller
 * Date: 21.09.2018
 * Time: 15:21
 */

include '../mysql_login.php';


$sql ="select TimeStamp,temperature,humidity from logs ORDER BY TimeStamp DESC LIMIT 1";
$rows = array();
if ($result = mysqli_query($conn, $sql)) {

    while ($row = mysqli_fetch_assoc($result)) {

        $rows[]=$row;
		echo "$row[temperature]<br>";
		echo "$row[humidity]<br>";
		
		$temp=$row[temperature];
		$humi=$row[humidity];
		$dew_point=round(pow(($humi/100),1/8)*(112+0.9*$temp)+0.1*$temp-112,2);
		echo "$dew_point";
		
    }
	
	
    mysqli_free_result($result);
}
mysqli_close($conn);

