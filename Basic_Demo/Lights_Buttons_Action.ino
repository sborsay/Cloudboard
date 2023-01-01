/*
Key
------------

3- coloblue LED's
--------------
Blue on Pin 5
Green on Pin 18
Yellow on Pin 19
------------
GL5528 Photoresistor GPIO 23 
---------------------------
Header Block Output pins at 3.3 volts
------------
Pin GPIO 33 by GND wokrs goes 0 and 3.33v
Pin GPIO 25 
Pin GPIO 26 
Pin GPIO 27 
Pin GPIO 14

2- Push Buttons
--------------
Button 1 GPIO 35;     //Button1, active low, GPIO35 
Button 2 GPIO 25;     //Button1, active low, GPIO25      
---------------------
*/


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



int blue = 5;
int green = 18;
int yellow = 19;
//int potOhms;
//int delay1;

//int potPin = 32;   //Potentiometer on GPIO 32
int potOhms = analogRead(32);

int lightLevel;
const int sensorPin = 33; //GL5528 phtoresistor on GPIO23

const int button1 = 35;     //Button1 Top, active high, GPIO35 
const int button2 = 25;          //and 32 is bottom button, 32(but2)  GPIO32

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status

//----------for DHT11 Enviro Sensor on Board-------------

// #include "DHT.h"

#define DHTPIN 15     // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //three light bar by chip g y b
  //three light bar by chip g y b
  pinMode(blue, OUTPUT); // blue light tied high, next to chip GPIO 5 works
  pinMode(green, OUTPUT); // Green light GPIO 18 next to chip works
  pinMode(yellow, OUTPUT); //Yellow light GPIO 19 next to chip works


//header block all work
      pinMode(13, OUTPUT); //header pin GPIO 13 by GND wokrs goes 0 and 3.33v
      pinMode(23, OUTPUT); //header pin GPIO 23 by 33 wokrs goes 0 and 3.29v
      pinMode(26, OUTPUT); //header pin GPIO 26 by 25 wokrs goes 0 and 3.30v
      pinMode(27, OUTPUT); //header pin GPIO 27 by 26 wokrs goes 0 and 3.34v
      pinMode(14, OUTPUT); //header pin GPIO 14 by 26 wokrs goes 0 and 3.31v


      //buttons
      pinMode(button1, INPUT);
      pinMode(button2, INPUT);

      dht.begin();
      Serial.begin(115200);

      // initialize with the I2C address 0x3C
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
       
     Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
    //delay(1000); //delay for DHT if needed
    lightLevel = analogRead(sensorPin);
    Serial.println((String)"The Photoresistor light level is: "+ lightLevel);



  //clear OLED display
  display.clearDisplay();

   //-----------DHT tester Section

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  // display Photoresistor
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Light Level: ");
  //display.setTextSize(2);
  display.setCursor(0,8);
  display.print(lightLevel/10); //normalize lux to same magnitude as enviro readings 
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(1);
  display.print(" lux");

  
  // display Photoresistor2
  display.setTextSize(1);
  display.setCursor(0,15);
  display.print("Light Level: ");
  //display.setTextSize(2);
  display.setCursor(0,25);
  display.print(lightLevel/10); //normalize lux to same magnitude as enviro readings 
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(1);
  display.print(" lux");

    // display Potentiomter resistence
  Serial.println(potOhms/10); //normalize pot value for 
  display.setTextSize(1);
  display.setCursor(0, 32);
  display.print("Potentiometer Resist: ");
 //display.setTextSize(2);
 // display.setCursor(0, 45);
  //display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.print(potOhms/10);
  //display.write(2126);
  display.print("  Ohms"); 

      // display Potentiomter resistence2
  Serial.println(potOhms/10); //normalize pot value for 
  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("Potentiometer Resist: ");
 //display.setTextSize(2);
 // display.setCursor(0, 45);
  //display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.print(potOhms/10);
  //display.write(2126);
  display.print("  Ohms"); 

  display.display(); 
  delay(1000); //delay so readimgs don't flutter

  //-------End DHT tester section
  
}
