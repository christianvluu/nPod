#include <ThingerWiFiNINA.h>

/*#############################
 * nPod 2019
 * Christian Luu and Nick Healy
 ##############################*/

//WiFi credentials
#define SSID "Lville MiFi5"
#define SSID_PASSWORD "XXXXXXXX"
#define DEVICE_OBJ LIB_B1_POD_1
#define DEVICE_ID "LIB_B1_POD_1"
#define DEVICE_CREDS "CREDENTIALS_LIB_B1_POD_1"

//variable declaration
int sensorPin = 5; //pir sensor pin

int val = LOW; //raw sensor value
int pirState = LOW; //flag variable

boolean roomFull = false; //calculated vacancy

int bufferTime = 300000; //milliseconds buffer
unsigned long lastMotion; //reset variable

double timeSinceMotion = 0;
double timeAtMotionStart = 0;
boolean motionToggle = true;

//create Thinger device object
ThingerWiFiNINA DEVICE_OBJ("npod", DEVICE_ID, DEVICE_CREDS);

void wifiConnect(){ //connects device to wifi
  DEVICE_OBJ.add_wifi(SSID, SSID_PASSWORD);
}

void setup() {

  wifiConnect(); //initial WiFi connection

  //pin setup
  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  DEVICE_OBJ["isMotion"] >> outputValue(isMotion()); //returns the 'calculated' vacant/present state with bufferTime
  DEVICE_OBJ["millis"] >> outputValue(millis()); //returns time since Arduino bootup
  DEVICE_OBJ["LEDStatus"] >> outputValue(lightLED()); //returns LED status (raw sensor status)
  //DEVICE_OBJ["bufferTimePost"] << inputValue(bufferTime); //POST from Server to change bufferTime
  DEVICE_OBJ["timeSinceMotion"] >> outputValue(getTimeSinceMotion()); //returns timeSinceMotion

}

void loop() {
  if(WiFi.status() != WL_CONNECTED){ //reconnects WiFi when disconnected
    wifiConnect();
  }

  DEVICE_OBJ.handle(); //handles all device parameters

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
