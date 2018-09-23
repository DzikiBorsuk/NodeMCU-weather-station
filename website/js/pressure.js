var pressure_indicator;
$(function () {
    var opts = {
        angle: 0, // The span of the gauge arc
        lineWidth: 0.25, // The line thickness
        radiusScale: 1, // Relative radius
        pointer: {
            length: 0.57, // // Relative to gauge radius
            strokeWidth: 0.04, // The thickness
            color: '#000000' // Fill color
        },
        limitMax: false,     // If false, max value increases automatically if value > maxValue
        limitMin: false,     // If true, the min value of the gauge will be fixed
        colorStart: '#6FADCF',   // Colors
        colorStop: '#8FC0DA',    // just experiment with them
        strokeColor: '#E0E0E0',  // to see which ones work best for you
        generateGradient: true,
        highDpiSupport: true,     // High resolution support
        // renderTicks is Optional
        renderTicks: {
            divisions: 5,
            divWidth: 1.1,
            divLength: 0.7,
            divColor: '#333333',
            subDivisions: 3,
            subLength: 0.5,
            subWidth: 0.6,
            subColor: '#666666'
        }

    };
    var target = document.getElementById('pressure-indicator'); // your canvas element
    pressure_indicator = new Gauge(target).setOptions(opts); // create sexy gauge!
    pressure_indicator.maxValue = 1060; // set max gauge value
    pressure_indicator.setMinValue(950);  // Prefer setter over gauge.minValue = 0
    pressure_indicator.animationSpeed = 32; // set animation speed (32 is default value)
    pressure_indicator.set(977); // set actual value
});