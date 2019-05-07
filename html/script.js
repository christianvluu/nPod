
//shortened pod names
const podsB1 = ["LIB_FLRB1_POD_0","LIB_FLRB1_POD_1", "LIB_FLRB1_POD_2"];
const podsF0 = ["LIB_FLR0_POD_0", "LIB_FLR0_POD_1", "LIB_FLR0_POD_2", "LIB_FLR0_POD_3"];
const podsF1 = ["LIB_FLR1_POD_0", "LIB_FLR1_POD_1", "LIB_FLR1_POD_2", "LIB_FLR1_POD_3"];

//resource variables
const millis = "millis";
const isMotion = "isMotion";

//floor placeholders
const floorB1 = -1; //basement
const floor0 = 0; //ground floor
const floor1 = 1; //second floor


//login parameters for thinger.io
var username ="npod"; //password in external file
var loginParams = {
  grant_type: "password",
  username: username,
  password: password
}

//gets access token from thinger.io and stores in access_token
var access_token = "";
$.post("https://api.thinger.io/oauth/token", loginParams)
.done( data => {
  console.log(data);
  access_token = data.access_token;
})
.fail( data => console.log(data))


//gets a resource from a single pod and fills an html element with it
//device name, resource to get, HTML id value
function getPod(device, resource, id) {
  var url = "https://api.thinger.io/v1/users/npod/devices/" + device + "/" + resource;
  $.get(url, {authorization: access_token})
    .done(data => document.getElementById(id).innerHTML = data)
    .fail(data => console.log("failure", data))
}

//gets isMotion values for an entire floor
function getFloorMotion(floor) {
  switch(floor) {
    case -1: //basement
      for(i = 0; i < 2; i++) { //2 or 3 in basement?
        var id = B1pod + i;
        getPod(podsB1[i], isMotion, id);
      }
    case 0: //ground floor
      for(i = 0; i < 4; i++) {
        var id = F0pod + i;
        getPod(podsF1[i], isMotion, id);
      }
    case 1: //second floor
      for(i = 0; i < 4; i++) {
        var id = F1pod + i;
        getPod(podsF1[i], isMotion, id);
      }
    default: //invalid parameter
      console.log("Error - floor not valid");
  }
}
