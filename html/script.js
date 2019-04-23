
var username = "";
var password = "";

var myObject = {
  grant_type: "password",
  username: username,
  password: password
}
var access_token = "";
$.post("https://api.thinger.io/oauth/token", myObject)
.done( data => {
  console.log(data);
  access_token = data.access_token;
  $.get("https://api.thinger.io/v1/users/supernick125/devices/slave_1/millis()", {authorization: access_token})
    .done(data => console.log(data))
    .fail(data => console.log("failure", data))
})
.fail( data => console.log(data))
