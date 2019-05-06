
//shortened pod names
const podsB1 = ["LIB_FLRB1_POD_0","LIB_FLRB1_POD_1", "LIB_FLRB1_POD_2"];
const pods0 = ["LIB_FLR0_POD_0", "LIB_FLR0_POD_1", "LIB_FLR0_POD_2", "LIB_FLR0_POD_3"];
const pods1 = ["LIB_FLR1_POD_0", "LIB_FLR1_POD_1", "LIB_FLR1_POD_2", "LIB_FLR1_POD_3"];

//resource variables
const millis = "millis";
const isMotion = "isMotion";

//how many pods on floor
const floorB1 = -1; //basement
const floor0 = 0; //ground floor
const floor1 = 1; //second floor


var username ="npod"; //password in external file
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


/*function getFloorTest() {
  for(i = 0; i < 2; i++) {
    var id = isMotion + i;
    getPod(pods[i], isMotion, id);
  }
}*/

function getFloor(floor) { //not done
  switch(floor) {
    case -1:
      for(i = 0; i < 3; i++) {
        var id = B1pod + i;
        getPod(podsB1[i], isMotion, id);
      }
    case 0:
      for(i = 0; i < 3; i++) {
        var id = pod + i;
        getPod(podsB1[i], isMotion, id);
      }
    case 1:
      for(i = 0; i < 3; i++) {
        var id = pod + i;
        getPod(podsB1[i], isMotion, id);
      }
    default:
      console.log("Error - floor not valid");
  }
}

function getPod(device, resource, id) {
  var url = "https://api.thinger.io/v1/users/npod/devices/" + device + "/" + resource;
  $.get(url, {authorization: access_token})
    .done(data => document.getElementById(id).innerHTML = data)
    .fail(data => console.log("failure", data))
}
