#include<SPI.h>
#include<stdlib.h>
#include <dht.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
 
int dustPin=A0;
int ledPower=2;
int delayTime=280;
int delayTime2=40;
float offTime=9680;
 
int dustVal=0;
int i=0;
float ppm=0;
char s[32];
float voltage=0;
float dustdensity=0;
float ppmpercf=0;
 
LiquidCrystal_I2C lcd(0x27,16,2);

dht DHT;
int DHT11_PIN=8;

void setup()
{
Serial.begin(9600);
pinMode(ledPower,OUTPUT);
 
// give the ethernet module time to boot up:
delay(1000);
   
lcd.init();
delay(100);
lcd.clear();
lcd.print(" Hellow Words! ");
//lcd.init();
lcd.backlight();  
//
//lcd.setCursor(0,0);
//lcd.print(" DEROBOT E.M.S ");
//lcd.setCursor(0,1);
//lcd.print("CD Site IoT Team");
//delay(3000);  
//
//lcd.clear();
//lcd.setCursor(0,0);
//lcd.print("Pls Wait For 10s");
//lcd.setCursor(0,1);
//lcd.print("Sensor Stabling ");
//lcd.backlight();  
//delay(10000); 
 
i=0;
ppm=0;
}
 
void loop()
{
i=i+1;
digitalWrite(ledPower,LOW);// power on the LED
delayMicroseconds(delayTime);
dustVal=analogRead(dustPin);// read the dust value
ppm=ppm+dustVal;
delayMicroseconds(delayTime2);
digitalWrite(ledPower,HIGH);// turn the LED off
delayMicroseconds(offTime);

int chk = DHT.read11(DHT11_PIN);
//  hum =DHT.humidity;
//  tem=DHT.temperature;

Serial.print("humidity: ");
Serial.println(DHT.humidity, 1);
Serial.print("temperature: ");
Serial.println(DHT.temperature, 1);
  
voltage=ppm/i*0.0049;
//Serial.print("Voltage: ");
//Serial.println(voltage);

dustdensity=1000 * (0.17 * voltage - 0.1);
if(dustdensity<0)
dustdensity=0;
Serial.print("Dustdensity: ");
Serial.println(dustdensity);

//ppmpercf=(voltage-0.0256)*120000;
//if(ppmpercf<0)
//ppmpercf=0;
//Serial.print("Ppmpercf: ");
//Serial.println(ppmpercf);

//if(dustdensity<0)
//dustdensity=0;
//if(dustdensity>0.5)
//dustdensity=0.5;
//String dataString="";
//dataString+=dtostrf(voltage,9,4,s);
//dataString+=",";
//dataString+=dtostrf(dustdensity,5,2,s);
//dataString+=",";
//dataString+=dtostrf(ppmpercf,8,0,s);
//i=0;
//ppm=0;
//Serial.println(dataString);
delay(1000);
}
