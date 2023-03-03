/*** UI for main menu ***/

void displayMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(34, 6);
  display.print("LILITH  YU");
  for (int i = 32; i < 97; i += 3) {
    display.drawFastHLine(i, 15, 1, SSD1306_WHITE);
  }
  
  display.setTextSize(1);
  display.setCursor(10, 25);
  display.setTextColor(WHITE);
  if (menuCount == 0) {
    display.setTextColor(BLACK, WHITE);
  }
  display.println("CLOCK");

  display.setCursor(10, 38);
  display.setTextColor(WHITE);
    if (menuCount == 1) {
    display.setTextColor(BLACK, WHITE);
  }
  display.println("IMU INFO");

  display.setCursor(10, 51);
  display.setTextColor(WHITE);
  if (menuCount == 2) {
    display.setTextColor(BLACK, WHITE);
  }
  display.println("SECRET SURPRISE");

  display.setTextColor(WHITE);
  display.setCursor(0, menuCount * 13 + 25);
 display.println(">");

  display.display();
  delay(1000);
}

void navigateMenu(sensors_event_t a, sensors_event_t g) {
    int accY = a.acceleration.y + 1.5;
      /* menu navigation */
    if (accY < -2.5) {
      if (menuCount < 2) {
        menuCount++;
      }
    }
//      imuRst = false;
//    } else if (a.acceleration.y >= 1) {
//      imuRst = true;

  
    if (accY > 2.5) {
        if (menuCount > 0) {
          menuCount--;
        }
    }
//        imuRst = false;
//    } else if (a.acceleration.y <= 1) {
//      imuRst = true;

}
