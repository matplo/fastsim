function serverNow(){
    var value = $.ajax({ 
	dataType: 'json',
	url: 'query/time',
	async: false,
	success : modifyLabel
   }).responseText;
   return value;
}

function modifyLabel(data) {
    document.getElementById("time").innerHTML = 'Server time is: ' + data
    };

function serverNowJSON () {
    var now = $.getJSON('query/time', function(data) {
	var now = 3;
	for (d of data)
	    {
		now = parseFloat(d['h'] + '.' + d['m']);
	    };
	return now;
	})
    return now[0]
};


    var currentDate = new Date();
    currentDate.setUTCHours(currentDate.getUTCHours())
    //var now = currentDate.getHours() + currentDate.getMinutes() / 60;
    //var nowJSON = serverNow()
    //var now = nowJSON;//nowJSON['h'] + nowJSON['m']
    var now = 12;
    serverNowAJAX(function(nowAJAX){
	now = nowAJAX.response;
	});




		      $.getJSON('plot2/data', function(data)
				{
				    for (d in data)
				    {
					options.series[0]
				    }
				    // Populate series
				    options.series[0] = data[0]['data'];
				    //chart.addSeries(data[0]); //['data']
				    document.getElementById("worked").innerHTML = data[0]['data'];
				}
			       );


			      series:
			      [
				  {
				      name : 'alice',
				      data : chartSeriesData
				  }
			      ]

			      tooltip:
			      {
			          formatter: function ()
			          {
			              ds = Date(this.x).toString()
			              return 'this is:'+this.name;
			          }
			      }


///// working

		      var chartSeriesData = [];
		      $.getJSON('plot2/data', function(data)
				{
				    var i = 0;
				    for (d of data)
				    {
					//chartSeriesData.push(parseFloat(d));
					//var label = d['absid'] + ' ' + d['date'];
					var label = ' <b>'
					    + d['date']  + ' '
					    + 'arXiv:' + d['absid'] + ' </b> '					
					    + d['title'];
					//chartSeriesData.push([label, parseFloat(data[d]['n'])]);
					var valn = parseFloat(d['n']);
					var series =
					    {
						name : label,
						title : d['title'],
						date : d['date'],
						x : Date.parse(d['date']),
						y : valn
					    };
					//chartSeriesData.push(series);
					chartSeriesData[i] = series
					//var htmltx = document.getElementById("worked").innerHTML
					//document.getElementById("worked").innerHTML = htmltx + " " + valn
					i = i + 1;					
				    }
				    //var htmltx = document.getElementById("worked").innerHTML
				    document.getElementById("worked").innerHTML = 'n-elems : ' + i + ' ' + chartSeriesData.length;
				    chart.addSeries(
					{
					    name : 'ALICE',
					    data : chartSeriesData
					});
				    chart.redraw();				    
				}
			       );
