//var gEmail = "None"

document.getElementById("myForm").onsubmit = function() {test()};

function test()
{
    var email, pass;

    email = document.getElementById('emailField').value;
    pass = document.getElementById('passwordField').value;

    var data =
	{
	    email : "none",
	    pass  : "none"
	};

    data.email = email
    data.pass  = pass
    
    document.getElementById('output').innerHTML = "Email provided: " + data.email;

    //gEmail = data.email
    //    return email;
}

//document.getElementById('output').innerHTML = "Email provided: " + gEmail;
//document.getElementById('checkbox').innerHTML = "Email provided: " + test();
