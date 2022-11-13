/*
sdb
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

const int sensorPin = 33; //GL5528 phtoresistor on GPIO23
int lightLevel;
const int potPin = 32;     //pin with 10k trimmer potentiometer
int potValue;

#define DHTPIN 15     // Digital pin connected to the DHT sensor

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);

  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  delay(2000);

   lightLevel = analogRead(sensorPin);
   Serial.println((String)"The Photoresistor light level is: " + lightLevel);

   potValue = analogRead(potPin);
   Serial.println((String)"The Potentiometer Trimmer resistence is: " + potValue);

  //read temperature and humidity
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }

   Serial.println((String)"The Temperature value in ° Celcius is: " + t);
   Serial.println((String)"The humidity index % is: " + h);

  //clear display
  display.clearDisplay();

  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0); //display.setCursor(x,y) – set the coordinates to start writing text
  display.print("Temp:");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(((t * 9/5) + 32),1);  // (°C × 9/5) + 32 = °F

  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity:");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h,1);
 //display.print("%"); 

    
  // display humidity2 
  display.setTextSize(1);
  display.setCursor(70, 0);
  display.print("Resistence:");
  display.setTextSize(2);
  display.setCursor(70, 10);
  display.print(potValue);  //normalize 24 turn 10k trimmer to keep magigniture in line


    // display Photoresistor
  display.setTextSize(1);
  display.setCursor(70,35);
  display.print("Lux Level:");
  display.setTextSize(2);
  display.setCursor(70, 45);
  display.print(lightLevel/10); //normalize lux to same magnitude as enviro readings 


  
  display.display(); 
}
