#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);
                         
#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN A5    // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 

int t;
DHT dht(DHTPIN, DHTTYPE);

///////////////////////////////////
const int trigPin = 7;
const int echoPin = 6;
long duration;
int d, distanceInch;

int A,B,Y;

void setup() 

{

Serial.begin(9600);
lcd.begin(16,2);
lcd.setCursor(0, 0);
lcd.print("  Smart Plant   ");
lcd.setCursor(0, 1);
lcd.print("Disease usingIOT");
delay(3000);
lcd.clear();


dht.begin();

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

pinMode(2,OUTPUT);// water motor
pinMode(4,OUTPUT);// Sparyer motor
pinMode(A5,INPUT); //temperature


pinMode(A0,INPUT); //Moisture
 
 digitalWrite(2,LOW);
  digitalWrite(4,LOW);
}



void loop()
{

  if(Serial.available() > 0) {
    char a = Serial.read();
  //  lcd.clear(); // Clear the previous message
    
    if(a == 'A') {
      Serial.print('R');
       delay(100);
       digitalWrite(4,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Bact.Leaf Blight");
      delay(4000);
       digitalWrite(4,LOW);
   
    }
    if(a == 'B') 
    {
        digitalWrite(4,HIGH);
      lcd.setCursor(0, 0);
      lcd.print(" Brown Spot     ");
      Serial.print('B');
      delay(100);
            delay(4000);
       digitalWrite(4,LOW);
    
    }
    if(a == 'C')
    {
        digitalWrite(4,LOW);
      lcd.setCursor(0, 0);
      lcd.print(" Healthy       ");
      Serial.print('C');
      delay(100);
   
    
    }
    if(a == 'D') 
    {
        digitalWrite(4,HIGH);
      lcd.setCursor(0, 0);
      lcd.print(" Leaf Blast     ");
      Serial.print('Q');
      delay(100);
            delay(4000);
       digitalWrite(4,LOW);
     
    }
    if(a == 'E')
    {
        digitalWrite(4,HIGH);
      lcd.setCursor(0, 0);
      lcd.print(" Leaf Blight    ");
      Serial.print('E');
      delay(100);
            delay(4000);
       digitalWrite(4,LOW);
   
    }
    if(a == 'F')
    {
        digitalWrite(4,HIGH);
      lcd.setCursor(0, 0);
      lcd.print(" Leaf Scald     ");
      Serial.print('F');
      delay(100);
            delay(4000);
       digitalWrite(4,LOW);
 
    }
    if(a == 'G') 
    {
        digitalWrite(4,HIGH);
      lcd.setCursor(0, 0);
      lcd.print(" Leaf Smut      ");
      Serial.print('G');
      delay(100);
            delay(4000);
       digitalWrite(4,LOW);
 
    }
    if(a == 'H')
    {
        digitalWrite(4,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Narrow BrownSpot");
      Serial.print('H');
      delay(100);
            delay(4000);
       digitalWrite(4,LOW);
    
    }
    
    delay(100);


    
  }



if((A==1) && (B==1) && (Y==1))
{

   digitalWrite(2,HIGH);
   Serial.print('M');
   delay(700);
}

else
{
     digitalWrite(2,LOW);
     Serial.print('m');
     delay(700);
}


int m=digitalRead(A0);
if (m==LOW)
{
   lcd.setCursor(6,1);
 lcd.print("MH");
  Y=0;
  Serial.print("y");
       delay(700);
}
else
{
 lcd.setCursor(6,1);
 lcd.print("ML");
  Y=1;
  Serial.print("Y");
       delay(700);
}

dht11();
  
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
d = duration*0.034/2;
 lcd.setCursor(13,1);
 lcd.print(d);
 lcd.print(' ');
Serial.print('D');
Serial.print(d);
delay(700);
if (d <5)
{

 lcd.setCursor(9,1);
 lcd.print("W_H:");
  B=1;
  Serial.print("Z");
  delay(700);
}
else
{
   B=0;
 lcd.setCursor(9,1);
 lcd.print("W_L:");
 
  Serial.print("z");
  delay(700);
}

}

void dht11()
{     
 int h = dht.readHumidity();
         t = dht.readTemperature();
        float f = dht.readTemperature(true);
        
        if (isnan(h) || isnan(t) || isnan(f)) 
        {
          //Serial.println("Failed to read from DHT sensor!");
          return;
        }

             lcd.setCursor(0,1);
             lcd.print("T:");
             lcd.setCursor(2,1);
             lcd.print(t); 
             
             Serial.print('T');
             Serial.print(t);
             delay(700);
             
                  
if(t > 38)
{
 lcd.setCursor(4,1);
 lcd.print("H");  

A=1;

}
else
{
lcd.setCursor(4,1);
lcd.print("L");

A=0;

}
}
