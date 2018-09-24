$(function () {

    $('.data-field').on('click', function () {
        let link = $(this).attr('id');
        link = link.replace('-href', '');
        window.location.href = 'charts/' + link + '.php';
    });

    let interval = '12';

    let temp_graph = null;
    let humidity_graph = null;
    let pressure_graph = null;
    let gas_graph = null;
    load_chart('temperature', 'temp-graph', interval, temp_graph);
    load_chart('humidity', 'humidity-graph', interval, humidity_graph);
    load_chart('pressure', 'pressure-graph', interval, pressure_graph);
    load_chart('gas', 'gas-graph', interval, gas_graph);

    function showTime() {
        var date = new Date();
        var h = date.getHours(); // 0 - 23
        var m = date.getMinutes(); // 0 - 59
        var s = date.getSeconds(); // 0 - 59
        //let ms = moment().milliseconds();
        var session = "";

        h = (h < 10) ? "0" + h : h;
        m = (m < 10) ? "0" + m : m;
        s = (s < 10) ? "0" + s : s;

        // if(ms<10)
        // {
        //     ms="00"+ms;
        // }
        // else if(ms<100)
        // {
        //     ms="0"+ms;
        // }

        var time = h + ":" + m + ":" + s + ' ' + session;
        document.getElementById("clockDisplay").innerText = time;
        document.getElementById("clockDisplay").textContent = time;





    }

    function showDay(){
        document.getElementById('date-day').innerText = moment().format('dddd');
        document.getElementById('date').innerText = moment().format('DD MMMM YYYY');
    }

    showTime();
    showDay();
    setInterval(showTime, 1000);
    setInterval(showDay, 1000);

});
