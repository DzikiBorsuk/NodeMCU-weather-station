<!DOCTYPE html>
<html>
<head>
<!--    <meta http-equiv="refresh" content="5">-->


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
$password = "";
$dbname = "sensorsd";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    echo "<a href='install.php'>If first time running click here to install database</a>";
    die("Database Connection failed: " . $conn->connect_error);
}
?>


<div class="container">
    <div class="row">
        <div class="col-md-4">fdd</div>
        <div class="col-md-4">dsf</div>
        <div class="col-md-4">fds</div>
    </div>
</div>


<div id="cards" class="cards">

    <?php
    $sql = "SELECT * FROM logs ORDER BY id DESC";
    if ($result = mysqli_query($conn, $sql)) {
        // Fetch one and one row
        echo "<TABLE id='c4ytable'>";
        echo "<TR><TH>Sr.No.</TH><TH>Temperature</TH><TH>Pressure</TH><TH>Altitude</TH><TH>Humidity</TH><TH>Gas</TH><TH>Dust</TH><TH>Date</TH><TH>Time</TH></TR>";
        while ($row = mysqli_fetch_row($result)) {
            echo "<TR>";
            echo "<TD>" . $row[0] . "</TD>";
            echo "<TD>" . $row[1] . "</TD>";
            echo "<TD>" . $row[2] . "</TD>";
            echo "<TD>" . $row[3] . "</TD>";
            echo "<TD>" . $row[4] . "</TD>";
            echo "<TD>" . $row[5] . "</TD>";
            echo "<TD>" . $row[6] . "</TD>";
            echo "<TD>" . $row[7] . "</TD>";
            echo "<TD>" . $row[8] . "</TD>";
            echo "</TR>";
        }
        echo "</TABLE>";
        // Free result set
        mysqli_free_result($result);
    }

    mysqli_close($conn);
    ?>


<script src="https://code.jquery.com/jquery-3.3.1.min.js"
        integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8="
        crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js"
        integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49"
        crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"
        integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy"
        crossorigin="anonymous"></script>

<script src="js/main.js"></script>


</body>
</html>