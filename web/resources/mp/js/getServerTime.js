$(document).ready(function() {
    $.getJSON('query/time', function(dt) {
	var currentDate = new Date();
	var now = ('0' + currentDate.getHours()).slice(-2) + ':' + ('0' + currentDate.getMinutes()).slice(-2);
	for (d of dt)
	{
	    if (document.getElementById("serverTime"))
	    {
		document.getElementById("serverTime").innerHTML = 'Server time at load: ' + ('0' + d['h']).slice(-2) + ':' + ('0' + d['m']).slice(-2)
	    }
	    if (document.getElementById("clientTime"))
	    {
		document.getElementById("clientTime").innerHTML = ' Your time at load: ' + now
	    }
	}
    });
});
	     
