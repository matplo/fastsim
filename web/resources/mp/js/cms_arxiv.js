$(document).ready(function()
		  {
		      var options =
			  {
			      chart:
			      {
				  renderTo: 'plotContainerCMS'
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
		      $.getJSON('plot2/arxiv/cms', function(data) {
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
			      color: '#916e80',			      
			      name : 'CMS',
			      data : chartSeriesData});
			  document.getElementById("cms").innerHTML = 'CMS: ' + chartSeriesData.length
		      });

		      chart.redraw();				    		      
	      
		  }
		 );

