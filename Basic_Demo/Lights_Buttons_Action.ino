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

DHT11 temperature and humidity tester on Pin 15

*/

int blue = 5;
int green = 18;
int yellow = 19;
int ledDelay;
//int delay1;

int potPin = 32;   //Potentiometer on GPIO 32
int lightLevel;
const int sensorPin = 33; //GL5528 phtoresistor on GPIO33

const int button1 = 35;     //Button1 Top, active high, GPIO35 
const int button2 = 25;          //and 32 is bottom button, 32(but2)  GPIO32

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status

//----------for DHT11 Enviro Sensor on Board-------------

 #include "DHT.h"

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
}

// the loop function runs over and over again forever
void loop() {
    //delay(1000); //delay for DHT if needed
  
  //Photoresistor GL5528 tester
    lightLevel = analogRead(sensorPin);
    Serial.println((String)"The Photoresistor light level is: "+ lightLevel);


//LED chaser tester for 3 colored LEDs
 ledDelay = analogRead(potPin); //potentiomter on GPIO 32 potPin
 Serial.println((String)"The Potentiometer is set at: "+  ledDelay);
 digitalWrite(blue, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  delay(ledDelay);
  digitalWrite(blue, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(yellow, LOW);
  delay(ledDelay);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  delay(ledDelay);

// 2-pushbutton tester section
  
   buttonState1 = digitalRead(button1) ;
   buttonState2 = digitalRead(button2) ;
   
   if(buttonState1 == LOW) {
     Serial.println("button 1 pressed " ) ;
   }

    if(buttonState2 == LOW) {
     Serial.println("button 2 pressed " ) ;
   }

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

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  //-------End DHT tester section
  
}
