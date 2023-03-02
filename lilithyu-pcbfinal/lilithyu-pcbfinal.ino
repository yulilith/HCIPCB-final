#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include "Keyboard.h"

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

// push button constants
const int buttonPin = 8;
int buttonState = 0;
int menuCount = 0;

//led constants
const int ledPin = 13;

int pageNumber = 0; // page number

void setup() {
  SerialUSB.begin(115200);
  // while (!SerialUSB);
  SerialUSB.println("MPU6050 OLED demo");
  Keyboard.begin();

  if (!mpu.begin()) {
    SerialUSB.println("Sensor init failed");
    while (1)
      yield();
  }
  SerialUSB.println("Found a MPU-6050 sensor");

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

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  //SerialUSB.println(buttonState);
  // SerialUSB.println(digitalRead(8));

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (Serial.available() > 0) {
    SerialUSB.println("serial available\n");
    // turn LED on:
    if (menuCount < 2) {
      menuCount++;
    } else {
      menuCount = 0;
    }
  }

  if (pageNumber == 0) {
    displayMenu();
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
}

void cursorMove() { // when button is pressed the selection ">" sign will move down
  int x = digitalRead(8); //read button
}
