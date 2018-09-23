<?php
/**
 * Created by PhpStorm.
 * User: Piotr Meller
 * Date: 22.09.2018
 * Time: 15:59
 */
?>


<!DOCTYPE html>
<html>
<head>
    <!--    <meta http-equiv="refresh" content="5">-->
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">

    <link rel="stylesheet" href="../css/bootstrap.css">
    <link rel="stylesheet" href="../css/style.css">
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
<div class="container bg-dark mt-4 rounded">
    <div class="d-flex justify-content-center align-items-center">
        <h3 class="d-block">Gas</h3>
    </div>
    <div class="d-flex justify-content-center">
        <div class="btn-group" role="group" aria-label="Basic example">
            <button id="720" type="button" class="btn btn-secondary change-interval">30d</button>
            <button id="360" type="button" class="btn btn-secondary change-interval">15d</button>
            <button id="168" type="button" class="btn btn-secondary change-interval">7d</button>
            <button id="72" type="button" class="btn btn-secondary change-interval">3d</button>
            <button id="24" type="button" class="btn btn-secondary btn-active change-interval">24H</button>
            <button id="12" type="button" class="btn btn-secondary change-interval">12H</button>
            <button id="6" type="button" class="btn btn-secondary change-interval">6H</button>
            <button id="3" type="button" class="btn btn-secondary change-interval">3H</button>
            <button id="1" type="button" class="btn btn-secondary change-interval">1H</button>
        </div>
    </div>
    <div class="row">
        <div class="chart-big">
            <canvas id="chart-big-gas"></canvas>
        </div>
    </div>
</div>


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

<script src="../js/gauge.min.js"></script>
<script src="../js/main.js"></script>
<script src="../js/pressure.js"></script>
<script src="../js/gas.js"></script>
<script src="../js/collect_data.js"></script>
<script src="../js/charts.js"></script>


<script>
    let current_chart=null;
    let show_chart = function (interval,chart) {
        load_chart('gas', 'chart-big-gas', interval,chart);
    };
    show_chart('24',current_chart);
</script>
<script src="../js/chart_settings.js"></script>

</body>
</html>