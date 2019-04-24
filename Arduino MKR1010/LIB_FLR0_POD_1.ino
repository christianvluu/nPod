#include <ThingerWiFiNINA.h>

#define SSID "LVproj"
#define SSID_PASSWORD "18101810"

int sensorPin = 2;
int pirState = LOW;
boolean roomFull = false;
int val = 0;
int bufferTime = 10000; //in milliseconds
unsigned long lastMotion;
long timeSinceMotion = 0;
long timeAtMotionStart;

ThingerWiFiNINA LIB_FLR0_POD_1("supernick125", "slave_1", "lK304w%k%7BU"); //CHANGE ACCOUNT AND ID LATER

void setup() {

  wifiConnect();

  pinMode(sensorPin, INPUT);

  LIB_FLR0_POD_1["isMotion"] >> outputValue(isMotion()); //returns the 'calculated' vacant/present state with bufferTime

  LIB_FLR0_POD_1["millis"] >> outputValue(millis()); //returns time since Arduino bootup

  LIB_FLR0_POD_1["timeSinceMotion"] >> outputValue(); //returns timeSinceMotion

  LIB_FLR0_POD_1["bufferTimePost"] << inputValue(bufferTime); //allows POST from Server to change bufferTime

}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    wifiConnect();
  }
  slave_1.handle();
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
      Serial.println("Motion detected");
      pirState = HIGH;
      lastMotion = millis();
    }
    return roomFull;
  }else{
    roomFull = false;
    if(pirState == HIGH){
      Serial.println("Motion ended");
      pirState = LOW;
    }
    return roomFull;
  }
}

long timeSinceMotion(){ //UNFINISHED
  if (roomFull == true){
    timeAtMotionStart = millis();
  }



}

void wifiConnect(){
  LIB_FLR0_POD_1.add_wifi(SSID, SSID_PASSWORD);
}
