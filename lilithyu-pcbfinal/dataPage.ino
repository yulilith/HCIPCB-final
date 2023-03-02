//  sensors_event_t a, g, temp;
//  mpu.getEvent(&a, &g, &temp);
//
//  display.clearDisplay();
//  display.setCursor(0, 0);
//
//  SerialUSB.print("Accelerometer ");
//  SerialUSB.print("X: ");
//  SerialUSB.print(a.acceleration.x, 1);
//  SerialUSB.print(" m/s^2, ");
//  SerialUSB.print("Y: ");
//  SerialUSB.print(a.acceleration.y, 1);
//  SerialUSB.print(" m/s^2, ");
//  SerialUSB.print("Z: ");
//  SerialUSB.print(a.acceleration.z, 1);
//  SerialUSB.println(" m/s^2");
//
//  display.println("Accelerometer - m/s^2");
//  display.print(a.acceleration.x, 1);
//  display.print(", ");
//  display.print(a.acceleration.y, 1);
//  display.print(", ");
//  display.print(a.acceleration.z, 1);
//  display.println("");
//
//  SerialUSB.print("Gyroscope ");
//  SerialUSB.print("X: ");
//  SerialUSB.print(g.gyro.x, 1);
//  SerialUSB.print(" rps, ");
//  SerialUSB.print("Y: ");
//  SerialUSB.print(g.gyro.y, 1);
//  SerialUSB.print(" rps, ");
//  SerialUSB.print("Z: ");
//  SerialUSB.print(g.gyro.z, 1);
//  SerialUSB.println(" rps");
//
//  display.println("Gyroscope - rps");
//  display.print(g.gyro.x, 1);
//  display.print(", ");
//  display.print(g.gyro.y, 1);
//  display.print(", ");
//  display.print(g.gyro.z, 1);
//  display.println("");
//
//  display.display();
//  delay(100);
