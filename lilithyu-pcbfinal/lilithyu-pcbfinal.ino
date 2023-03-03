#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <RTCZero.h>

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
RTCZero rtc;

/*** SETUP ***/

void setup() {
  SerialUSB.begin(115200);
  // while (!SerialUSB);
  SerialUSB.println("MPU6050 OLED demo");

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



  SerialUSB.println("menuCount: " + menuCount);
  SerialUSB.println("pageNumber: " + pageNumber);

  if (pageNumber == 0) {
    displayMenu();
    
    /* menu navigation */
    if (a.acceleration.y < -1.5) {
      if (menuCount < 2) {
        menuCount++;
      }
    }
  
    if (a.acceleration.y > 1.5) {
        if (menuCount > 0) {
          menuCount--;
        }
     }
    } 
  
  if (pageNumber == 1) {
    displayClock();
  } 
  if (pageNumber == 2) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextColor(WHITE);
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
