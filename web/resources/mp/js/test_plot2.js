$(document).ready(function()
		  {
		      var options =
			  {
			      chart:
			      {
				  renderTo: 'plotContainer'
			      },
			      title:
			      {
				  text: 'Publications on arXiv'
			      },
			      xAxis:
			      {
				  type   : 'datetime'
			      }
			      yAxis: {
				  labels: {
				      align: 'left',
				      x: 0,
				      y: -2
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


		      $.getJSON('plot2/arxiv/atlas', function(data) {
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
			      color: '#0266c8',
			      name : 'ATLAS',
			      data : chartSeriesData});
			  document.getElementById("atlas").innerHTML = 'ATLAS: ' + chartSeriesData.length
		      });

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

		      $.getJSON('plot2/arxiv/lhcb', function(data) {
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
			      color: '#00933b',
			      name : 'LHCb',
			      data : chartSeriesData});
			  document.getElementById("lhcb").innerHTML = 'LHCb: ' + chartSeriesData.length
		      });
		      
		      chart.redraw();				    		      
	      
		  }
		 );

