void displayClock() {
  display.clearDisplay();
  display.setTextColor(WHITE);

  /*** DATE DISPLAY ***/
  display.setTextSize(1);

  /* date text */
  display.setCursor(8, 8);
  display.print("DATE");

  /* date */
  display.setCursor(73, 8);
  display2digits(rtc.getDay());
  display.print("/");
  display2digits(rtc.getMonth());
  display.print("/");
  display2digits(rtc.getYear());

  /* dotted line */
  for (int i = 36; i < 70; i += 4) {
    display.drawFastHLine(i, 11, 1, SSD1306_WHITE);
  }
  
  /*** TIME DISPLAY ***/

  /* time */
  display.setTextSize(2);
  display.setCursor(17, 32);
  display2digits(rtc.getHours());
  display.print(":");
  display2digits(rtc.getMinutes());
  display.print(":");
  display2digits(rtc.getSeconds());

  /* box outline */
  display.drawFastHLine(8, 24, 112, SSD1306_WHITE);
  display.drawFastHLine(8, 54, 112, SSD1306_WHITE);
  display.drawFastVLine(8, 24, 30, SSD1306_WHITE);
  display.drawFastVLine(120, 24, 30, SSD1306_WHITE);

  display.display();
  delay(1000);
}

void display2digits(int number) {
  if (number < 10) {
    display.print("0");
  }
  display.print(number);
}
