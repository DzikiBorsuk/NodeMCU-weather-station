let data = {
    labels: [1,2,3,4,5,6,7],
    datasets: [{
        backgroundColor: "rgba(65, 79, 164,1)",
        borderColor: "rgba(85, 124, 255,1)",
        borderWidth: 2,
        pointRadius: 0,
        hoverBackgroundColor: "rgba(255,99,132,0.4)",
        hoverBorderColor: "rgba(255,99,132,1)",
        data: [65, 59, 20, 81, 56, 55, 40],

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
                display: false,
            }
        }],
        xAxes: [{
            gridLines: {
                display: false
            }
        }]
    },
    layout: {
        padding: 0,
    },
    scaleLabel: {
        display: true,
    }
};

let ctx = $('#temp-graph');

let myLineChart = new Chart(ctx, {
    type: 'line',
    options: options,
    data: data
});

$.get('http/last_12h_data.php',function (response) {
    let data = JSON.parse(response);
});
