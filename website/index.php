<!DOCTYPE html>
<html>
<head>
    <!--    <meta http-equiv="refresh" content="5">-->
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">

    <link rel="stylesheet" href="css/bootstrap.css">
    <link rel="stylesheet" href="css/style.css">
    <!--    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css"-->
    <!--          integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO"-->
    <!--          crossorigin="anonymous">-->
</head>
<body class="bg-dark-dark text-light">

<?php
//Connect to database and create table
$servername = "localhost";
$username = "root";
$password = "qwerty";
$dbname = "weather_station";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    echo "<a href='install.php'>If first time running click here to install database</a>";
    die("Database Connection failed: " . $conn->connect_error);
}
?>

<a href="/" class="link">
    <div class="brand bg-dark d-flex justify-content-between align-items-center">
        <div class="brand-item" style="height: 100%">
            <img class="d-none d-lg-block d-xl-block" src="../img/TU-KL.png" width="auto" height="100%">
        </div>
        <div class="brand-item-title text-center">
            <p class="h2" align="center">Weather station</p>
        </div>
        <div class="brand-item">
            <p class="h2 d-none d-lg-block d-xl-block">TU Kaiserslautern</p>
        </div>
    </div>
</a>

<div class="container mt-3">
    <div class="row">
        <div class="col-lg-4 my-3">
            <div id="temperature-href" class="bg-dark rounded data-field">
                <div style="width: 100%">
                    <p style="margin: 0" align="center">Temperature</p>
                </div>
                <div class="row sensor-data">
                    <div class="col-3 h-100 d-flex justify-content-center align-items-center">
                        <div class="humidex d-flex justify-content-center align-items-center">
                            <div class="text-light text-center">
                                <span>Humidex</span>
                                <span id="current-humidex">35</span><span>&deg;C</span>
                            </div>
                        </div>
                    </div>
                    <div class="col-6 h-100 d-flex justify-content-center align-items-center">
                        <div class="temp-now d-flex justify-content-center align-items-center">
                            <div class="text-light">
                                <span><span id="current-temp">22</span>&deg;C</span>
                            </div>
                        </div>
                    </div>
                    <div class="col-3 h-100 d-flex justify-content-end align-items-center">
                        <div class="d-flex justify-content-start align-items-center">
                            <div style="font-size: 0.8rem">
                                <span>T max:</span>
                                <br>
                                <div style="color: orange"><span id="max-temp">30</span><span>&deg; C</span></div>
                                <br>
                                <span>T min:</span>
                                <br>
                                <div style="color: orange"><span id="min-temp">15</span><span>&deg; C</span></div>
                                <br>
                            </div>
                        </div>
                    </div>

                </div>
                <div class="graph">
                    <canvas id="temp-graph"></canvas>
                </div>
            </div>
        </div>
        <div class="col-lg-4 my-3">
            <div class="bg-dark rounded data-field">
                <div>
                    <div class="dateTime">
                        <div id="clockDisplay" class="clock"></div>
                        <div id="date-day"></div>
                        <div id="date"></div>
                    </div>
                </div>
            </div>
        </div>
        <div class="col-lg-4 my-3">
            <div id="humidity-href" class="bg-dark rounded data-field">
                <div style="width: 100%">
                    <p style="margin: 0" align="center">Relative humidity</p>
                </div>
                <div class="row sensor-data">
                    <div class="col-3 h-100 d-flex justify-content-center align-items-center">
                        <div class="dew-point d-flex justify-content-center align-items-center">
                            <div class="text-light text-center">
                                <span>Dew point</span>
                                <span id="current-dewpoint">7.6</span><span>&deg;C</span>
                            </div>
                        </div>
                    </div>
                    <div class="col-6 h-100 d-flex justify-content-center align-items-center">
                        <div class="humidity-now d-flex justify-content-center align-items-center">
                            <img style="position: absolute" src="img/drop.png" width="120px" height="auto">
                            <div style="position: absolute" class="text-light">
                                <br>
                                <span><span id="current-humidity">100.0</span>%</span>
                            </div>
                        </div>
                    </div>
                    <div class="col-3 h-100 d-flex justify-content-end align-items-center">
                        <div class="d-flex justify-content-start align-items-center">
                            <div style="font-size: 0.8rem">
                                <span>Rh max:</span>
                                <br>
                                <div style="color: dodgerblue"><span id="max-humidity">30</span><span> %</span></div>
                                <br>
                                <span>Rh min:</span>
                                <br>
                                <div style="color: dodgerblue"><span id="min-humidity">15</span><span> %</span></div>
                                <br>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="graph">
                    <canvas id="humidity-graph"></canvas>
                </div>
            </div>
        </div>
    </div>
</div>
<div class="container">
    <div class="row">
        <div class="col-lg-4 my-3">
            <div id="pressure-href" class="bg-dark rounded data-field">
                <div style="width: 100%">
                    <p style="margin: 0" align="center">Pressure</p>
                </div>
                <div class="row sensor-data">
                    <div class="col-3 h-100 d-flex justify-content-center align-items-center">
                        <div class="d-flex justify-content-center align-items-center">
                            <div class="text-light text-center">
                                <div style="font-size: 0.8rem">
                                    <span>Pressure min:</span>
                                    <br>
                                    <div style="color: dodgerblue"><span id="min-pressure">940</span><span> hPa</span>
                                    </div>
                                    <br>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div class="col-6 h-100 d-flex justify-content-center align-items-center">
                        <div class="pressure-now d-flex justify-content-center align-items-center">
                            <div style="position: absolute; top: 25px;"><span><span id="current-pressure">977</span> hPa</span>
                            </div>
                            <canvas class="gauge" id="pressure-indicator"></canvas>
                        </div>
                    </div>
                    <div class="col-3 h-100 d-flex justify-content-end align-items-center">
                        <div class="d-flex justify-content-start align-items-center">
                            <div class="text-light text-center" style="font-size: 0.8rem">
                                <span>Presure max:</span>
                                <br>
                                <div style="color: dodgerblue"><span id="max-pressure">999</span><span> hPa</span></div>
                                <br>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="graph">
                    <canvas id="pressure-graph"></canvas>
                </div>
            </div>
        </div>
        <div class="col-lg-4">
            <div style="height: 1px"></div>
        </div>
        <div class="col-lg-4 my-3">
            <div id="gas-href" class="bg-dark rounded data-field">
                <div style="width: 100%">
                    <p style="margin: 0" align="center">Gas (VOC)</p>
                </div>
                <div class="row sensor-data">
                    <div class="col-3 h-100 d-flex justify-content-center align-items-center">
                        <div class="d-flex justify-content-center align-items-center">
                            <div class="text-light text-center">
                                <div style="font-size: 0.8rem">
                                    <span>Gas min:</span>
                                    <br>
                                    <div style="color: dodgerblue"><span id="min-gas">10</span><span> k&ohm;</span>
                                    </div>
                                    <br>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div class="col-6 h-100 d-flex justify-content-center align-items-center">
                        <div class="pressure-now d-flex justify-content-center align-items-center">
                            <div style="position: absolute; top: 25px;"><span><span
                                            id="current-gas">30</span> k&ohm;</span>
                            </div>
                            <canvas class="gauge" id="gas-indicator"></canvas>
                        </div>
                    </div>
                    <div class="col-3 h-100 d-flex justify-content-end align-items-center">
                        <div class="d-flex justify-content-start align-items-center">
                            <div class="text-light text-center" style="font-size: 0.8rem">
                                <span>Gas max:</span>
                                <br>
                                <div style="color: dodgerblue"><span id="max-gas">50</span><span> k&ohm;</span></div>
                                <br>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="graph">
                    <canvas id="gas-graph"></canvas>
                </div>
            </div>
        </div>
    </div>
</div>


<!--<div id="cards" class="cards">-->
<!---->
<!--    --><?php
//    $sql = "SELECT * FROM logs ORDER BY id DESC";
//    if ($result = mysqli_query($conn, $sql)) {
//        // Fetch one and one row
//        echo "<TABLE id='c4ytable'>";
//        echo "<TR><TH>Sr.No.</TH><TH>Temperature</TH><TH>Pressure</TH><TH>Altitude</TH><TH>Humidity</TH><TH>Gas</TH><TH>Dust</TH><TH>Date</TH><TH>Time</TH></TR>";
//        while ($row = mysqli_fetch_row($result)) {
//            echo "<TR>";
//            echo "<TD>" . $row[0] . "</TD>";
//            echo "<TD>" . $row[1] . "</TD>";
//            echo "<TD>" . $row[2] . "</TD>";
//            echo "<TD>" . $row[3] . "</TD>";
//            echo "<TD>" . $row[4] . "</TD>";
//            echo "<TD>" . $row[5] . "</TD>";
//            echo "<TD>" . $row[6] . "</TD>";
//            echo "<TD>" . $row[7] . "</TD>";
//            echo "<TD>" . $row[8] . "</TD>";
//            echo "</TR>";
//        }
//        echo "</TABLE>";
//        // Free result set
//        mysqli_free_result($result);
//    }
//
//    mysqli_close($conn);
//    ?>


<script src="https://code.jquery.com/jquery-3.3.1.min.js"
        integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8="
        crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js"
        integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49"
        crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"
        integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy"
        crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.22.2/moment.min.js"
        integrity="sha256-CutOzxCRucUsn6C6TcEYsauvvYilEniTXldPa6/wu0k="
        crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.2/Chart.min.js"
        integrity="sha256-CfcERD4Ov4+lKbWbYqXD6aFM9M51gN4GUEtDhkWABMo="
        crossorigin="anonymous"></script>

<script src="js/charts.js"></script>
<script src="js/gauge.min.js"></script>
<script src="js/main.js"></script>
<script src="js/pressure.js"></script>
<script src="js/gas.js"></script>
<script src="js/collect_data.js"></script>


</body>
</html>