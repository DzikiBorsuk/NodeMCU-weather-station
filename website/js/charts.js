var chart_big = null;

function load_chart(data, id, interval, chart_to_show) {


    function render_chart(data_name, chart_id, data_points) {

        let regex = /big/;

        let grid = false;
        let pointRadius = 0;
        let miniChart = true;
        let padding = 0;
        if (regex.test(chart_id)) {
            grid = true;
            pointRadius = 8;
            miniChart = false;
            padding = 50;
        }

        data_points = JSON.parse(data_points);
        let labels = new Array();
        let points = new Array();

        for (let key in data_points) {
            if (miniChart === false) {
                labels.push(data_points[key]['Date'] + '\n' + data_points[key]['Time']);
                points.push(data_points[key][data_name])
            } else {
                if (key % 2 !== 0) {
                    labels.push(0);
                    points.push(data_points[key][data_name])
                }
            }
        }

        let data = {
            labels: labels,
            datasets: [{
                backgroundColor: "rgba(65, 79, 164,1)",
                borderColor: "rgba(85, 124, 255,1)",
                borderWidth: 2,
                pointRadius: pointRadius,
                pointBackgroundColor: 'rgba(0,0,0,0)',
                pointBorderColor: 'rgba(0,0,0,0)',
                hoverBackgroundColor: "rgba(255,99,132,0.4)",
                hoverBorderColor: "rgba(255,99,132,1)",
                data: points,

            }]
        };

        let options = {
            legend: {
                display: false
            },
            maintainAspectRatio: false,
            scales: {
                yAxes: [{
                    gridLines: {
                        display: grid,
                    }
                }],
                xAxes: [{
                    gridLines: {
                        display: false
                    }
                }]
            },
            layout: {
                padding: {
                    left: 0,
                    right: padding,
                    top: 0,
                    bottom: 0
                }
            },
            scaleLabel: {
                display: true,
            }
        };

        let chart = $('#' + chart_id);

        if (!regex.test(chart_id)) {
            chart_to_show = new Chart(chart, {
                type: 'line',
                options: options,
                data: data
            });
        }
        else {
            if (chart_big === null) {
                chart_big = new Chart(chart, {
                    type: 'line',
                    options: options,
                    data: data
                });
            }
            else {
                chart_big.data=data;
                chart_big.update();
            }
        }
    }

    $.get(location.protocol + '//' + location.host + '/http/' + data + '/last.php?interval=' + interval, function (response) {
        render_chart(data, id, response)
    });

    // switch (data) {
    //     case 'temperature':
    //         $.get('')
    //         break;
    //
    //     case 'humidity':
    //
    //         break;
    //
    //     case 'pressure':
    //
    //         break;
    //
    //     case 'gas':
    //
    //         break;
    //
    //
    // }

}