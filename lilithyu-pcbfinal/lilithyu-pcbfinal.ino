#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <RTCZero.h>

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
RTCZero rtc;

/*** CONSTANTS ***/

//led constants
const int ledPin = 13;
const int ledTop = 10;
const int ledBot = 18;

// push button constants
const int buttonPin = 8;
int buttonState = 0;

// RTC constants
/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 41;
const byte hours = 5; 
/* Change these values to set the current initial date */
const byte day = 2;
const byte month = 3;
const byte year = 23;

// UI constants
int menuCount = 0;
int pageNumber = 0; // page number

// surprise page constants
long randNumber; 
bool surpriseRst;

/*** SETUP ***/

void setup() {
  SerialUSB.begin(115200);
  // while (!SerialUSB);
  SerialUSB.println("MPU6050 OLED demo");

  /* initialize MPU */
  if (!mpu.begin()) {
    SerialUSB.println("Sensor init failed");
    while (1)
      yield();
  }
  SerialUSB.println("Found a MPU-6050 sensor");
  
  //setupt motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(2);
  mpu.setMotionDetectionDuration(30);
  mpu.setInterruptPinLatch(true);  // Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  /* RTC initializer */
  rtc.begin();
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);
  rtc.setDay(day);
  rtc.setMonth(month);
  rtc.setYear(year);

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
  pinMode(ledTop, OUTPUT);
  pinMode(ledBot, OUTPUT);
}


/*** MAIN LOOP ***/

void loop() {

  /* get mpu data */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  if (a.acceleration.x <= -6) {
    display.ssd1306_command(SSD1306_DISPLAYOFF);
    delay(5000);
  } else if (a.acceleration.x >= -4) {
    display.ssd1306_command(SSD1306_DISPLAYON);
    display.display();
  }
  
  
  // buttonState = digitalRead(buttonPin);


  /* light up LEDs */
  digitalWrite(ledTop, HIGH);
  digitalWrite(ledBot, HIGH);

  /* page navigation */
  if (a.acceleration.x < -3.5) {
    pageNumber = menuCount + 1;
   }
  if (a.acceleration.x > 3.5) {
    pageNumber = 0;
   }

  SerialUSB.println("menuCount: " + menuCount);
  SerialUSB.println("pageNumber: " + pageNumber);

  if (pageNumber == 0) {
    displayMenu();
    navigateMenu(a, g);
    randNumber = random(2);
    surpriseRst = true;
  } 
  
  if (pageNumber == 1) {
    displayClock();
  } 
  
  if (pageNumber == 2) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      displayData(a, g, temp);
  } 
  if (pageNumber == 3) {
    displaySurprise(randNumber, a, g);
  }
}
