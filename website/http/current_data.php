<?php
/**
 * Created by PhpStorm.
 * User: Piotr Meller
 * Date: 21.09.2018
 * Time: 15:21
 */

include 'mysql_login.php';

$sql ="select TimeStamp,temperature,humidity,pressure,gas from logs ORDER BY TimeStamp DESC LIMIT 1";
$sqlMIN="select MIN(temperature) AS min_temp, MIN(humidity) AS min_humi, MIN(pressure) AS min_press, MIN(gas) AS min_gas FROM logs WHERE TimeStamp >= DATE_SUB(NOW(),INTERVAL 12 HOUR)";
$sqlMAX="select MAX(temperature) AS max_temp, MAX(humidity) AS max_humi, MAX(pressure) AS max_press, MAX(gas) AS max_gas FROM logs WHERE TimeStamp >= DATE_SUB(NOW(),INTERVAL 12 HOUR)";
$data = array();
if ($result = mysqli_query($conn, $sql)) {

    while ($row = mysqli_fetch_assoc($result)) {

		//echo "$row[temperature]<br>";
		//echo "$row[humidity]<br>";
		$temp=$row[temperature];
		$humi=$row[humidity];
		$dew_point=round(pow(($humi/100),1/8)*(112+0.9*$temp)+0.1*$temp-112,2);
		$e=6.11*exp(5417.7530 * ((1/273.16) - (1/(273.16+$dew_point))));
		$h = (0.5555)*($e - 10.0);
		$humidex=round($temp+$h,2);
		$data['dew_point']=$dew_point;
		$data['humidex']=$humidex;
		$data['temperature']=$temp;
		$data['pressure']=$row[pressure];
		$data['gas']=$row[gas];
		$data['humidity']=$humi;
		//echo "Humidex=$humidex";
		
		
    }
	
	
    mysqli_free_result($result);
}
if ($result = mysqli_query($conn, $sqlMIN))
{
	if($row=mysqli_fetch_assoc($result))
	{
		$data['min_temp']=$row['min_temp'];
		$data['min_humi']=$row['min_humi'];
		$data['min_press']=$row['min_press'];
		$data['min_gas']=$row['min_gas'];
		
	}
	mysqli_free_result($result);
}
if ($result = mysqli_query($conn, $sqlMAX))
{
	if($row=mysqli_fetch_assoc($result))
	{
		$data['max_temp']=$row['max_temp'];
		$data['max_humi']=$row['max_humi'];
		$data['max_press']=$row['max_press'];
		$data['max_gas']=$row['max_gas'];
		echo json_encode($data);
		
	}
	mysqli_free_result($result);
}
mysqli_close($conn);

