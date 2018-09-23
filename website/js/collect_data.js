let sensor_data = {};


$(function () {

    let ged_d = function () {

        let set_data = function () {
            $('#current-humidex').text(sensor_data['humidex']);
            $('#current-temp').text(sensor_data['temperature']);
            $('#current-dewpoint').text(sensor_data['dew_point']);
            $('#current-humidity').text(sensor_data['humidity']);
            $('#current-pressure').text(sensor_data['pressure']);
            pressure_indicator.set(sensor_data['pressure']);
            $('#current-gas').text(sensor_data['gas']);
            gas_indicator.set(sensor_data['gas']);
            $('#max-humidity').text(sensor_data['max_humi']);
            $('#min-humidity').text(sensor_data['min_humi']);
            $('#max-temp').text(sensor_data['max_temp']);
            $('#min-temp').text(sensor_data['min_temp']);
            $('#max-pressure').text(sensor_data['max_press']);
            $('#min-pressure').text(sensor_data['min_press']);
            $('#max-gas').text(sensor_data['max_gas']);
            $('#min-gas').text(sensor_data['min_gas']);
        };

        $.get(location.protocol + '//' + location.host + '/http/current_data.php', function (response) {
            sensor_data = JSON.parse(response);
            set_data();
        })
    };

    ged_d();


    setInterval(ged_d, 600000);
});