#include <ThingerWiFiNINA.h>

#define SSID "LVproj"
#define SSID_PASSWORD "18101810"

int sensorPin = 2;
int pirState = LOW;
boolean roomFull = false;
int val = 0;
int bufferTime = 10000;
unsigned long lastMotion;

ThingerWiFiNINA slave_1("supernick125", "slave_1", "lK304w%k%7BU"); //CHANGE ACCOUNT AND ID LATER

void setup() {

  wifiConnect();

  pinMode(sensorPin, INPUT);

  slave_1["isMotion"] >> outputValue(isMotion());

  slave_1["millis"] >> outputValue(millis());

}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    wifiConnect();
  }
  slave_1.handle();
}

boolean isMotion(){ //ADD COMMENTS

  val = digitalRead(sensorPin); //output from sensor

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

void wifiConnect(){
  slave_1.add_wifi(SSID, SSID_PASSWORD);
}
