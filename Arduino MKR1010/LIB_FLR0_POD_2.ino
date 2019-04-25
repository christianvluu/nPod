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
boolean timeSinceMotionFlag = true;

ThingerWiFiNINA LIB_FLR0_POD_2("supernick125", "slave_2", "lK304w%k%7BU"); //CHANGE ACCOUNT AND ID LATER

void setup() {

  wifiConnect();

  pinMode(sensorPin, INPUT);
  pinMode(13, OUTPUT);

  LIB_FLR0_POD_2["isMotion"] >> outputValue(isMotion()); //returns the 'calculated' vacant/present state with bufferTime

  LIB_FLR0_POD_2["millis"] >> outputValue(millis()); //returns time since Arduino bootup

  LIB_FLR0_POD_2["timeSinceMotion"] >> outputValue(); //returns timeSinceMotion

  LIB_FLR0_POD_2["bufferTimePost"] << inputValue(bufferTime); //allows POST from Server to change bufferTime

}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    wifiConnect();
  }
  LIB_FLR0_POD_2.handle();
  lightLED();
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
        timeSinceMotionFlag = true;
      }
  }
  else{
      roomFull = false;
      if(pirState == HIGH){
        Serial.println("Motion ended");
        pirState = LOW;
      }
      timeSinceMotionFlag = false;
  }
  return roomFull;
}

long timeSinceMotion(){ //UNFINISHED

}

void lightLED(){
  if(roomFull){
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13,LOW);
  }
}

void wifiConnect(){
  LIB_FLR0_POD_2.add_wifi(SSID, SSID_PASSWORD);
}
