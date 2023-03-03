/*** DISPLAY IMU DATA ***/

void displayData(sensors_event_t a, sensors_event_t g, sensors_event_t temp) {
  mpu.getEvent(&a, &g, &temp);
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);

  display.println("Accelerometer - m/s^2\n");
  display.print(a.acceleration.x, 1);
  display.print(", ");
  display.print(a.acceleration.y, 1);
  display.print(", ");
  display.print(a.acceleration.z, 1);
  display.println("\n");
  
  display.println("Gyroscope - rps\n");
  display.print(g.gyro.x, 1);
  display.print(", ");
  display.print(g.gyro.y, 1);
  display.print(", ");
  display.print(g.gyro.z, 1);
  display.println("");

  display.display();
  delay(100);
}
