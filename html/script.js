
//shortened pod names
const pods = ["LIB_FLR0_POD_1", "LIB_FLR0_POD_2"];

//resource variables
const millis = "millis";
const isMotion = "isMotion";

//how many pods on floor
const floor0 = 2;


var username ="npod";

var loginParams = {
  grant_type: "password",
  username: username,
  password: password
}


var access_token = "";
$.post("https://api.thinger.io/oauth/token", loginParams)
.done( data => {
  console.log(data);
  access_token = data.access_token;
})
.fail( data => console.log(data))

function getFloorTest() { //UNFINISHED
  for(i = 0; i < 2; i++) {
    getPod(pods[i], isMotion, )
  }
}

function getPod(device, resource, id) {
  var url = "https://api.thinger.io/v1/users/npod/devices/" + device + "/" + resource;
  $.get(url, {authorization: access_token})
    .done(data => document.getElementById(id).innerHTML = data)
    .fail(data => console.log("failure", data))
}
