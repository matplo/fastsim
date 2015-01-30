$(document).ready(function()
		  {
		      var options =
			  {
			      chart:
			      {
				  renderTo: 'plotContainerAlice'
			      },
			      title:
			      {
				  text: 'Publications on arXiv'
			      },
			      xAxis:
			      {
				  type   : 'datetime'
			      }
			  };
		      
		      var chart = new Highcharts.Chart(options);		      
		      $.getJSON('plot2/arxiv/alice', function(data) {
			  var chartSeriesData = [];			  
			  var i = 0;
			  for (d of data) {
			      var label = ' <b>' + d['date'] + ' ' + 'arXiv:' + d['absid'] + ' </b> '//+ d['title'];
			      var valn = parseFloat(d['n']);
			      var series = {
				  name : label,
				  title : d['title'],
				  date : d['date'],
				  x : Date.parse(d['date']),
				  y : valn };
			      chartSeriesData[i] = series
			      i = i + 1; }
			  chart.addSeries({
			      color: '#ff004c',			      			      
			      name : 'ALICE',
			      data : chartSeriesData});
			  document.getElementById("alice").innerHTML = 'ALICE: ' + chartSeriesData.length
		      });
		      
		      chart.redraw();				    		      
	      
		  }
		 );

