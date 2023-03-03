void displayClock() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(40, 10);
  display2digits(rtc.getDay());
  display.println("/");
  display2digits(rtc.getMonth());
  display.println("/");
  display2digits(rtc.getYear());
  display.setTextSize(2);
  display.setCursor(30, 30);
  display2digits(rtc.getHours());
  display.println(":");
  display2digits(rtc.getMinutes());
  display.println(":");
  display2digits(rtc.getSeconds());
  display.display();
  delay(1000);
}

void display2digits(int number) {
  if (number < 10) {
    display.println("0");
  }
  display.println(number);
}
