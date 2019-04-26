#include <ThingerWiFiNINA.h>

/*
 * nPod 2019
 * Christian Luu and Nick Healy
 */

//WiFi credentials
#define SSID "LVproj"
#define SSID_PASSWORD "18101810"

//variable declaration
int sensorPin = 2; //pir sensor pin

int val = LOW; //raw sensor value
int pirState = LOW; //flag variable

boolean roomFull = false; //calculated vacancy

int bufferTime = 10000; //milliseconds buffer
unsigned long lastMotion; //reset variable

//create Thinger device object
ThingerWiFiNINA LIB_FLR0_POD_1("nPod", "LIB_FLR0_POD_1", "CREDENTIALS_LIB_FLR0_POD_1"); //CHANGE ACCOUNT AND ID LATER

void setup() {

  wifiConnect(); //initial WiFi connection

  //pin setup
  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);


  LIB_FLR0_POD_1["isMotion"] >> outputValue(isMotion()); //returns the 'calculated' vacant/present state with bufferTime
  LIB_FLR0_POD_1["millis"] >> outputValue(millis()); //returns time since Arduino bootup
  LIB_FLR0_POD_1["LEDStatus"] >> outputValue(lightLED()); //returns LED status (raw sensor status)

  LIB_FLR0_POD_1["bufferTimePost"] << inputValue(bufferTime); //POST from Server to change bufferTime

}

void loop() {
  if(WiFi.status() != WL_CONNECTED){ //reconnects WiFi when disconnected
    wifiConnect();
  }

  LIB_FLR0_POD_1.handle(); //handles all device parameters
}

boolean isMotion(){
  val = digitalRead(sensorPin); //raw output from sensor

  if((millis() - lastMotion) <= bufferTime){ //resets lastMotion
    if(val == HIGH){
      lastMotion = millis();
    }
  }
  if((val == HIGH) || ((millis() - lastMotion) <= bufferTime)){
      roomFull = true;
      if(pirState == LOW){
        pirState = HIGH;
        lastMotion = millis();
      }
  }
  else{
      roomFull = false;
      if(pirState == HIGH){
        pirState = LOW;
      }
  }
  return roomFull;
}

boolean lightLED(){ //controls built in LED based on raw sensor value
  if(val){
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN,LOW);
  }
  return(val); //returns LED status
}

void wifiConnect(){ //connects device to wifi
  LIB_FLR0_POD_1.add_wifi(SSID, SSID_PASSWORD);
}
