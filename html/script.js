
//shortened pod names
const podsB1 = ["LIB_FLRB1_POD_0","LIB_FLRB1_POD_1", "LIB_FLRB1_POD_2"];
const pods0 = ["LIB_FLR0_POD_0", "LIB_FLR0_POD_1", "LIB_FLR0_POD_2", "LIB_FLR0_POD_3"];
const pods1 = ["LIB_FLR1_POD_0", "LIB_FLR1_POD_1", "LIB_FLR1_POD_"];

//resource variables
const millis = "millis";
const isMotion = "isMotion";

//how many pods on floor
const floorB1 = 3; //basement
const floor0 = 4; //ground floor
const floor1 = 6; //second floor


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
    var id = isMotion + i;
    getPod(pods[i], isMotion, id);
  }
}

function getPod(device, resource, id) {
  var url = "https://api.thinger.io/v1/users/npod/devices/" + device + "/" + resource;
  $.get(url, {authorization: access_token})
    .done(data => document.getElementById(id).innerHTML = data)
    .fail(data => console.log("failure", data))
}
