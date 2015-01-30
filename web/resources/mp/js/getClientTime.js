$(document).ready(function() {
    var currentDate = new Date();
    var now = ('0' + currentDate.getHours()).slice(-2) + ':' + ('0' + currentDate.getMinutes()).slice(-2);
    if (document.getElementById("clientTime"))
    {
	document.getElementById("clientTime").innerHTML = ' Your time at load: ' + now
    }
});
	     
