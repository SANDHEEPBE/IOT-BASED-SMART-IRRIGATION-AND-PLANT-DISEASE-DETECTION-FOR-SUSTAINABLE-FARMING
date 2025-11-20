
//App username:planty_123
//App PW: Projectiot@2025


#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <Arduino_DebugUtils.h>
#include <Wire.h>
#include <ArduinoMqttClient.h>

const char DEVICE_LOGIN_NAME[]  = "2f269604-9ce6-4dcb-b546-1849022086e2";
const char SSID[] = "projectiot"; // WiFi Network SSID
const char PASS[] = "123456789";  // WiFi Password
const char DEVICE_KEY[] = "eQY4Ny6W8tHQd!DdGm2YHQb?y"; // Secret Device Key
void onStatusChange();
void onTempChange();
void onWlChange();
void onMotorStatusChange();
void onWaterLevelStatusChange();

String status;
int temp;
int wl;
bool motorStatus;
bool waterLevelStatus;

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 1000; // 1 second

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(status, READWRITE, ON_CHANGE, onStatusChange);
  ArduinoCloud.addProperty(temp, READWRITE, ON_CHANGE, onTempChange);
  ArduinoCloud.addProperty(wl, READWRITE, ON_CHANGE, onWlChange);
  ArduinoCloud.addProperty(motorStatus, READWRITE, ON_CHANGE, onMotorStatusChange);
  ArduinoCloud.addProperty(waterLevelStatus, READWRITE, ON_CHANGE, onWaterLevelStatusChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void setup() {
  Serial.begin(9600);
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
 
  delay(1000); // Wait for 1 seconds

}

void loop() {
   unsigned long currentMillis = millis();
  // Update cloud at set intervals
  if (currentMillis - lastUpdateTime >= updateInterval) {
    ArduinoCloud.update();
    lastUpdateTime = currentMillis;
  }

  if(Serial.available() > 0) {
    char a = Serial.read();
  
   switch (a) {
    case 'T':temp = Serial.parseInt();
    break;
    
    case 'D': wl=Serial.parseInt();
    break;
    
    case 'Z': waterLevelStatus=true;
    break;
    case 'z':waterLevelStatus=false;
    break;

    case  'M': motorStatus=true;
    break;
    

    case 'm' : motorStatus=false;
        break;
 
       case 'Y' : status = "Moisture Low";
      break; 

          case 'y' : status = "Moisture High";
      break; 
         case 'R' : status = "Bact.Leaf Blight";
      break;
    case 'B': status = "Brown Spot";
      break;
    case 'C': status = "Healthy";
    break;
    
    case 'Q':status = "Leaf Blast";
    break;
    case 'E': status = "Leaf Blight";
     break;
     case 'F':status = "Leaf Scald";
      break;
    case 'G': status = "Leaf Smut";
     break;
    case 'H': status = "Narrow BrownSpot";
      break;
    }      
    
    delay(100);
   
  }
}


void onTempChange()  {}
void onWlChange()  {}
void onMotorStatusChange()  {}
void onStatusChange()  {}
void onWaterLevelStatusChange()  {}
