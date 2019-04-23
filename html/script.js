
var username = "supernick125";
var password = "nPod2019";

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
  /*$.get("https://api.thinger.io/v1/users/supernick125/devices/slave_1/millis()", {authorization: access_token})
    .done(data => document.write(data))//console.log(data))
    .fail(data => console.log("failure", data))*/
})
.fail( data => console.log(data))


var button = document.createElement("testButton");
button.innerHTML = "Button";

var body = document.getElementsByTagName("body")[0];
body.appendChild(button);

button.addEventListener ("click", function() {
  $.get("https://api.thinger.io/v1/users/supernick125/devices/slave_1/millis()", {authorization: access_token})
    .done(data => document.write(data))//console.log(data))
    .fail(data => console.log("failure", data))
});
