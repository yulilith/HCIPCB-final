#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <RTCZero.h>
//#include "Keyboard.h"

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
RTCZero rtc;

//led constants
const int ledPin = 13;

// push button constants
const int buttonPin = 8;
int buttonState = 0;

//RTC constants
/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 0;
const byte hours = 16; 
/* Change these values to set the current initial date */
const byte day = 15;
const byte month = 6;
const byte year = 15;

//UI constants
int menuCount = 0;
int pageNumber = 0; // page number


/*** SETUP ***/

void setup() {
  SerialUSB.begin(115200);
  // while (!SerialUSB);
  SerialUSB.println("MPU6050 OLED demo");
  //  Keyboard.begin();

  /*initialize MPU */

  if (!mpu.begin()) {
    SerialUSB.println("Sensor init failed");
    while (1)
      yield();
  }
  SerialUSB.println("Found a MPU-6050 sensor");

  /*RTC initializer*/
  rtc.begin();
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);
  rtc.setDay(day);
  rtc.setMonth(month);
  rtc.setYear(year);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    SerialUSB.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.display();
  delay(500); // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);

  //pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}


/*** MAIN LOOP ***/

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  // read the state of the pushbutton value:
  // buttonState = digitalRead(buttonPin);
  //SerialUSB.println(buttonState);
  // SerialUSB.println(digitalRead(8));

  /* page navigation */
  if (a.acceleration.x > 2) {
    SerialUSB.println("serial available\n");
    // turn LED on:
    pageNumber = menuCount + 1;
   }

  if (a.acceleration.x < -2) {
    pageNumber = 0;
   }

  /* menu navigation */
  if (a.acceleration.y < -1.5) {
    SerialUSB.println("serial available\n");
    // turn LED on:
    if (menuCount < 2) {
      menuCount++;
    } else {
      menuCount = 0;
    }
   }

   if (a.acceleration.y > 1.5) {
      SerialUSB.println("serial available\n");
      // turn LED on:
      if (menuCount > 0) {
        menuCount--;
      } else {
        menuCount = 0;
      }
   }

  SerialUSB.println("menuCount: " + menuCount);
  SerialUSB.println("pageNumber: " + pageNumber);

  if (pageNumber == 0) {
    displayMenu();
  } 
  if (pageNumber == 1) {
    displayClock();
  } 
  if (pageNumber == 2) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
    
      SerialUSB.print("Accelerometer ");
      SerialUSB.print("X: ");
      SerialUSB.print(a.acceleration.x, 1);
      SerialUSB.print(" m/s^2, ");
      SerialUSB.print("Y: ");
      SerialUSB.print(a.acceleration.y, 1);
      SerialUSB.print(" m/s^2, ");
      SerialUSB.print("Z: ");
      SerialUSB.print(a.acceleration.z, 1);
      SerialUSB.println(" m/s^2");
    
      display.println("Accelerometer - m/s^2");
      display.print(a.acceleration.x, 1);
      display.print(", ");
      display.print(a.acceleration.y, 1);
      display.print(", ");
      display.print(a.acceleration.z, 1);
      display.println("");
    
      SerialUSB.print("Gyroscope ");
      SerialUSB.print("X: ");
      SerialUSB.print(g.gyro.x, 1);
      SerialUSB.print(" rps, ");
      SerialUSB.print("Y: ");
      SerialUSB.print(g.gyro.y, 1);
      SerialUSB.print(" rps, ");
      SerialUSB.print("Z: ");
      SerialUSB.print(g.gyro.z, 1);
      SerialUSB.println(" rps");
    
      display.println("Gyroscope - rps");
      display.print(g.gyro.x, 1);
      display.print(", ");
      display.print(g.gyro.y, 1);
      display.print(", ");
      display.print(g.gyro.z, 1);
      display.println("");
    
      display.display();
      delay(100);
  } 
  if (pageNumber == 3) {
    displaySurprise();
  }
}

void displayMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
//  display.invertDisplay(1);

//  display.setCursor(10, 40);
//  display.println("LILITH WATCH");
  //---------------------------------
  
  display.setTextSize(1);
  display.setCursor(10, 2);
  display.println("CLOCK");
//  display.setCursor(60, 20);
//  display.println(valA);

  display.setCursor(10, 12);
  display.println("IMU INFO");
//  display.setCursor(60, 30);
//  display.println(valB);

  display.setCursor(10, 22);
  display.println("SECRET SURPRISE");
//  display.setCursor(60, 40);
//  display.println(valC);
//
//  display.setCursor(10, 30);
//  display.println("Start:");
//  display.setCursor(45, 50);
//  if (encoder0Pos > 5 && menuCount == 4) {
//    display.println("Run!");
//    runState = true;
//  } else {
//    display.println("Idle");
//    runState = false;
//  }
//  display.setCursor(2, (menuCount * 10) + 10);
//  display.println(">");

   display.setCursor(0, menuCount * 10 + 2);
   display.println(">");

  display.display();
  delay(1000);
}

void cursorMove() { // when button is pressed the selection ">" sign will move down
  int x = digitalRead(8); //read button
}
