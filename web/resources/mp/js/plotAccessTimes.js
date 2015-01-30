function plotGraph (param) {
    //alert (param);
    var options =
	{
	    chart:
	    {
		plotBackgroundColor: null,
		renderTo: 'plotContainer',
		zoomType: 'x',
		//type : 'line',		
		//plotBackgroundColor: "#000000"
		//plotBackgroundColor:  "rgba(255, 255, 255, 0.8)",
		backgroundColor: "rgba(255, 255, 255, 0.8)",
		//backgroundColor: "rgba(125, 0, 0, 0.8)",
		type: 'column', //'pie', //'column',
		margin: 70,
		options3d: {
                    enabled: true,
                    alpha: 10,
                    beta: 7,
                    depth: 200,
                    viewDistance: 1
		}		
	    },
	    title:
	    {
		//text: param
		text: ''
	    },
	    legend: {
		enabled: false
            },
	    /*
            subtitle: {
		text: document.ontouchstart === undefined ?
                    'Click and drag in the plot area to zoom in' :
                    'Pinch the chart to zoom in'
            },*/
            xAxis: {
		//type: 'datetime',
		//minRange: 8 * 3600000 // fourteen days
		minRange: 5,
		title: {
		    text: 'Access Hour - Server TZ'
		}
            },
	    yAxis: {
		min: 0,
		labels: {
		    align: 'left',
		    x: 0,
		    y: 0
		},
		title : {
		    text : "Number of entries"
		}
	    },
            legend: {
		enabled: false
            },
            plotOptions: {
		area: {
                    fillColor: {
			linearGradient: { x1: 0, y1: 0, x2: 0, y2: 1},
			stops: [
                            [0, Highcharts.getOptions().colors[3]],
                            [100, Highcharts.Color(Highcharts.getOptions().colors[4]).setOpacity(0.5).get('rgba')]
			]
                    },
                    marker: {
			radius: 2
                    },
                    lineWidth: 1,
                    states: {
			hover: {
                            lineWidth: 1
			}
                    },
                    threshold: null
		},
		column: {
                    depth: 15
		}
            } //end plotOptions	    
	};
    
    var chart = new Highcharts.Chart(options);		      
    $.getJSON(param, function(data) {
	var chartSeriesData = [];			  
	var i = 0;
	for (d of data) {
	    var label = ' <b> Access time: ' + d['x'] + ' </b> '//+ d['title'];
	    var series = {
		name : label,
		x : d['x'],
		y : d['y'] };
	    chartSeriesData[i] = series
	    i = i + 1; }
	chart.addSeries({
	    //color: "rgba(125, 0, 0, 0.25)",//'#ff004c',
	    color: "rgba(1, 1, 1, 0.1)",//'#ff004c',	      			      
	    name : 'Counts',
	    data : chartSeriesData});
    });    
    chart.redraw();				    		          

    $.getJSON('query/time', function(dt) {
	for (d of dt)
	    {
		chart.xAxis[0].addPlotLine({
		    label: { 
			//text: 'Server Time @ Load',
			text: 'Server@Load',
			rotation: -45,
			y: -5
		    },
		    //color: 'blue',
		    color: "rgba(0, 0, 125, 0.3)",		    
                    value: parseFloat(d['h']) + parseFloat(d['m'])/60.,
		    width: '5',
                    //color: '#FCFFC5',
                    id: 'plot-line-1'
		});
	    };
	
	var currentDate = new Date();
	var now = currentDate.getHours() + currentDate.getMinutes()/60.;
	chart.xAxis[0].addPlotLine({
	    label: { 
		//text: 'Client Time @ Load',
		text: 'Client@Load',		
		rotation: -45,
		y: -5
	    },
	    //color: 'green',
	    color: "rgba(0, 125, 0, 0.3)",
            value: now,
	    width: '5',
            //color: '#FCFFC5',
            id: 'plot-line-1'
	});
	
    });
};
