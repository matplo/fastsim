$(document).ready(function()
		  {
		      var options =
			  {
			      chart:
			      {
				  renderTo: 'plotContainer',
				  zoomType: 'x',
				  type : 'line',				  
				  plotBackgroundColor:  "rgba(255, 255, 255, 0.8)",
				  backgroundColor: "rgba(255, 255, 255, 0.8)"				  
			      },
			      title:
			      {
				  text: 'Publications on arXiv'
			      },
			      xAxis:
			      {
				  type   : 'datetime',
				  minRange: 14 * 24 * 3600000,
				  
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
			      }
			  };
			      
		      var chart = new Highcharts.Chart(options);		      
		      //$.getJSON('plot2/arxiv/alice', function(data) {
		      $.getJSON('data/alice.json', function(data) {		      
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
			  document.getElementById("alice").innerHTML = 'ALICE: ' + chartSeriesData.length;
		      });


		      $.getJSON('data/atlas.json', function(data) {
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
			  document.getElementById("atlas").innerHTML = 'ATLAS: ' + chartSeriesData.length;
		      });

		      $.getJSON('data/cms.json', function(data) {
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
			  document.getElementById("cms").innerHTML = 'CMS: ' + chartSeriesData.length;
		      });

		      $.getJSON('data/lhcb.json', function(data) {
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
			  document.getElementById("lhcb").innerHTML = 'LHCb: ' + chartSeriesData.length;
		      });
		      
		      chart.redraw();				    		      
	      
		  }
		 );

