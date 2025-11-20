//email leafdisease7@gmail.com.
//Leaf2003
//Your username is plant_diseases_777.
//Projectiot@2025


#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <Arduino_DebugUtils.h>
#include <Wire.h>
#include <ArduinoMqttClient.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(D0,D1,D2,D5,D6,D7);
#include <DHT.h>
DHT dht(D3, DHT11);

const char DEVICE_LOGIN_NAME[]  = "8c7e31bf-4efc-4751-a023-7069cff2e853";
const char SSID[] = "projectiot"; // WiFi Network SSID
const char PASS[] = "123456789";  // WiFi Password
const char DEVICE_KEY[] = "6K90SchigYePNEnl8fB?S5@al"; // Secret Device Key

void onPlantDiseaseChange();
void onHumChange();
void onTempChange();
void onHumStatusChange();
void onTempStatusChange();

String plantDisease;
int hum;
int temp;
bool humStatus;
bool temp_Status;

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 1000; // 1 second

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(plantDisease, READWRITE, ON_CHANGE, onPlantDiseaseChange);
  ArduinoCloud.addProperty(hum, READWRITE, ON_CHANGE, onHumChange);
  ArduinoCloud.addProperty(temp, READWRITE, ON_CHANGE, onTempChange);
  ArduinoCloud.addProperty(humStatus, READWRITE, ON_CHANGE, onHumStatusChange);
  ArduinoCloud.addProperty(temp_Status, READWRITE, ON_CHANGE, onTempStatusChange);

}


WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void setup() {
  Serial.begin(9600);
  initProperties();
  dht.begin();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  lcd.begin(16, 2);  // Set up a 16x2 LCD
  lcd.setCursor(0, 0); // Set cursor to top row
  lcd.print("  Plant Disease   ");
  lcd.setCursor(0, 1);
  lcd.print(" Identification   ");
  
  delay(2000); // Wait for 2 seconds

  lcd.clear();
}

void loop() {
   unsigned long currentMillis = millis();
  // Update cloud at set intervals
  if (currentMillis - lastUpdateTime >= updateInterval) {
    ArduinoCloud.update();
    lastUpdateTime = currentMillis;
  }

  int t = dht.readTemperature();
  int h = dht.readHumidity();

  // Display temperature
  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.print(t);
  lcd.print(char(223)); // Degree symbol
  lcd.print("C   "); // Clear trailing characters
  temp = t;
  hum= h;

  
  
  // Display humidity
  lcd.setCursor(9, 1);
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%  ");

  // Temperature status
  lcd.setCursor(7, 1);
  if (t > 36) {
    lcd.print("H");
    temp_Status=false;

    
  } else {
    lcd.print("L");
    temp_Status=true;

  }

  // Humidity status
  lcd.setCursor(15, 1);
  if (h > 60) {
    lcd.print("H");
    humStatus=false;


  } else {
    lcd.print("L");
    humStatus=true;
    


  }

  if(Serial.available() > 0) {
    char a = Serial.read();
    lcd.clear(); // Clear the previous message
    
    if(a == 'A') {
      lcd.setCursor(0, 0);
      lcd.print("Bact.Leaf Blight");
      plantDisease = "Bact.Leaf Blight";
    }
    else if(a == 'B') {
      lcd.setCursor(0, 0);
      lcd.print(" Brown Spot     ");
      plantDisease = "Brown Spot";
    }
    else if(a == 'C') {
      lcd.setCursor(0, 0);
      lcd.print(" Healthy       ");
      plantDisease = "Healthy";
    }
    else if(a == 'D') {
      lcd.setCursor(0, 0);
      lcd.print(" Leaf Blast     ");
      plantDisease = "Leaf Blast";
    }
    else if(a == 'E') {
      lcd.setCursor(0, 0);
      lcd.print(" Leaf Blight    ");
     plantDisease = "Leaf Blight";
    }
    else if(a == 'F') {
      lcd.setCursor(0, 0);
      lcd.print(" Leaf Scald     ");
      plantDisease = "Leaf Scald";
    }
    else if(a == 'G') {
      lcd.setCursor(0, 0);
      lcd.print(" Leaf Smut      ");
      plantDisease = "Leaf Smut";
    }
    else if(a == 'H') {
      lcd.setCursor(0, 0);
      lcd.print("Narrow BrownSpot");
      plantDisease = "Narrow BrownSpot";
    }
    
    delay(100);


    
  }
}

void onTempChange()  {}
void onHumChange()  {}
void onHumStatusChange()  {}
void onTempstatusChange()  {}
void onPlantDiseaseChange()  {}
void onTempStatusChange()  {}
