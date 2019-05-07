#include <ThingerWiFiNINA.h>

/*
 * nPod 2019
 * Christian Luu and Nick Healy
 */

/*#############################
Change per file:
- ThingerWiFiNINA Obj at creation
- ThingerWiFiNINA Obj at wifiConnect() reference
- Resources Output/Input Obj reference in setup()
#############################*/

//WiFi credentials
#define SSID "LVproj"
#define SSID_PASSWORD "XXXXXXXX"

//variable declaration
int sensorPin = 5; //pir sensor pin

int val = LOW; //raw sensor value
int pirState = LOW; //flag variable

boolean roomFull = false; //calculated vacancy

int bufferTime = 10000; //milliseconds buffer
unsigned long lastMotion; //reset variable

double timeSinceMotion = 0;
double timeAtMotionStart = 0;
boolean motionToggle = true;

//create Thinger device object
ThingerWiFiNINA LIB_FLR0_POD_2("npod", "LIB_FLR0_POD_2", "CREDENTIALS_LIB_FLR0_POD_2"); //CHANGE ACCOUNT AND ID LATER

void wifiConnect(){ //connects device to wifi
  LIB_FLR0_POD_2.add_wifi(SSID, SSID_PASSWORD); //change OBJ name as necessary
}

void setup() {

  wifiConnect(); //initial WiFi connection

  //pin setup
  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  LIB_FLR0_POD_2["isMotion"] >> outputValue(isMotion()); //returns the 'calculated' vacant/present state with bufferTime
  LIB_FLR0_POD_2["millis"] >> outputValue(millis()); //returns time since Arduino bootup
  LIB_FLR0_POD_2["LEDStatus"] >> outputValue(lightLED()); //returns LED status (raw sensor status)
  LIB_FLR0_POD_2["bufferTimePost"] << inputValue(bufferTime); //POST from Server to change bufferTime
  LIB_FLR0_POD_2["timeSinceMotion"] >> outputValue(getTimeSinceMotion()); //returns timeSinceMotion

}

void loop() {
  if(WiFi.status() != WL_CONNECTED){ //reconnects WiFi when disconnected
    wifiConnect();
  }

  LIB_FLR0_POD_2.handle(); //handles all device parameters

  isMotion();
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

double getTimeSinceMotion(){ //returns timeSinceMotion
  if (roomFull && !motionToggle){ //init timeAtMotionStart when based on roomFull var
    timeAtMotionStart = millis();
    motionToggle = true;
  }
  if (roomFull && motionToggle){ //starts reporting timeSinceMotion
    timeSinceMotion = millis() - timeAtMotionStart;
    return timeSinceMotion;
  }
  if (!roomFull){ //returns -1 when no motion
    motionToggle = false;
    return -1;
  }
}

boolean lightLED(){ //controls built in LED based on raw sensor value
  if(val){
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN,LOW);
  }
  return(val); //returns LED status
}
