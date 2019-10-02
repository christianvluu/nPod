"use strict"

//shortened pod names
const podsB1 = ["LIB_B1_POD_0","LIB_B1_POD_1"];
const podsF0 = ["LIB_F0_POD_0", "LIB_F0_POD_1", "LIB_F0_POD_2", "LIB_F0_POD_3"];
const podsF1 = ["LIB_F1_POD_0", "LIB_F1_POD_1", "LIB_F1_POD_2", "LIB_F1_POD_3"];

//resource variables
const millis = "millis";
const isMotion = "isMotion";

//floor placeholders
const floorB1 = -1; //basement
const floor0 = 0; //ground floor
const floor1 = 1; //second floor


//sets square color for one pod
function setSquareColor(isMotion, id) {
  if(isMotion == 2){
    document.getElementById(id).src = "/img/orange.jpg";
  }
  if(isMotion == 1){
    document.getElementById(id).src = "/img/red.jpg";
  }else if(!isMotion){
    document.getElementById(id).src = "/img/green.jpg";
  }
}

//gets a resource from a single pod and fills an html element with it
//device name, resource to get, HTML id value
function getPod(device, resource, id) {
  $.get("/survey/nPod/library?device="+device+"&resource="+resource)
    .fail( function() {
      setSquareColor(2, id);
    } )
    .done( function( data ) {
      setSquareColor(JSON.parse(data), id);
    } );
}

//gets isMotion values for an entire floor
function getFloorMotion(floor) {
  switch(floor) {
    case -1: //basement
      for(var i = 0; i < 2; i++) {
        var id = "B1pod" + i;
        getPod(podsB1[i], isMotion, id);
      }
      break;
    case 0: //ground floor
      for(var i = 0; i < 4; i++) {
        var id = "F0pod" + i;
        getPod(podsF0[i], isMotion, id);
      }
      break;
    case 1: //second floor
      for(var i = 0; i < 4; i++) {
        var id = "F1pod" + i;
        getPod(podsF1[i], isMotion, id);
      }
      break;
    default: //invalid parameter
      console.log("Error - floor not valid");
      break;
  }
}

function collapseStuff(floor){
  switch(floor){
    case -1:
      $('#collapseB1').collapse('show')
      $('#collapse0').collapse('hide')
      $('#collapse1').collapse('hide')
      break;
    case 0:
      $('#collapseB1').collapse('hide')
      $('#collapse0').collapse('show')
      $('#collapse1').collapse('hide')
      break;
    case 1:
      $('#collapseB1').collapse('hide')
      $('#collapse0').collapse('hide')
      $('#collapse1').collapse('show')
      break;
  }
}

function updateTime(floor) {
  $("#lastUpdate")
    .text( "Last updated: " + new Date().toLocaleTimeString() );
  $("#refresh")
    .html( "<button type='button'>Refresh</button>" )
    .off( "click" )
    .click( function() {
      floorClick(floor);
    } );
}

function floorClick(floor){
  collapseStuff(floor);
  getFloorMotion(floor);
  updateTime(floor);
  console.log("click")
}
