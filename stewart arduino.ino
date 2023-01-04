//********************************************************************************************
// MM_stewart_test4.ino
// 6 x RC Model Servos, as used in minature Stewart platform
// Arduino code written by MadMat for testing 6DOF interface.
// Use this code to recieve data from SimTools or FlyPT
//
// Add info: details about data format
//           details about servo data
//
//********************************************************************************************

#include <Servo.h>
Servo servo[6];                                 // 6 element servo array, variable name is "servo". Can be any valid variable name.
int i, j, k;
int rawServoData[6];                            // 6 element array to hold raw servo data as read from sim.
int servoData[6];                               // 6 element array to hold servo positoin data ready to write to servos.
String fromSim;                                 // Data from sim in format: A<Axis1a>B<Axis2a>C<Axis3a>D<Axis4a>E<Axis5a>F<Axis6a>X (eg. A127B127C127D127E127F127X)
char wasteData[99];                             // when parseInt'íng it was found that the data stream sometimes contained floating points. This wasteData char is a buffer to collect

void setup()
{
  for (i = 0; i <= 5; i++) {                    // loop to set up 6 servos
    servo[i].attach(i + 4);                     // attach servos 0 - 5 to pins 4 - 9
    servo[i].write(90);                         // set each servo to mid point (90°)
  }

  Serial.begin(57600);                          // opens serial port at a baud rate of 57600
  Serial.println("MM_stewart_test4");           // report the current loaded software
  delay(1);
}
void loop() {
  while (Serial.available() > 0) {                // wait for serial data available
    Read_Servo_Data();                            // read the serial data.
    Map_Servo_Data();                             // Function to turn 'rawServoData[]' values into values suitable for your servos.
    Set_Servos2();                                // Function to write the posiditon data 'servoData' to each servo.
    Serial.read();                               //读一个少一个，一直读，直到没有缓存数据了。
  }
}
void Read_Servo_Data() {
  Serial.readBytesUntil('A', wasteData, 18);      // read data until 'A' is read. Throw the rest away.
  rawServoData[0] = Serial.parseInt();            // read the next bytes of numerical data in the buffer and treat them as an integer to be stored in integer array 'rawServoData[]'.
  Serial.readBytesUntil('B', wasteData, 18);      // This function could be handled in a loop but testing revealed a slightly shorter processing time using this method.
  Serial.print(rawServoData[0]);
  rawServoData[1] = Serial.parseInt();            
  Serial.readBytesUntil('C', wasteData, 18);
  Serial.print(rawServoData[1]);
  rawServoData[2] = Serial.parseInt();
  Serial.readBytesUntil('D', wasteData, 18);
  Serial.print(rawServoData[2]);
  rawServoData[3] = Serial.parseInt();
  Serial.readBytesUntil('E', wasteData, 18);
  Serial.print(rawServoData[3]);
  rawServoData[4] = Serial.parseInt();
  Serial.readBytesUntil('F', wasteData, 18);
  Serial.print(rawServoData[4]);
  rawServoData[5] = Serial.parseInt();
  Serial.readBytesUntil('X', wasteData, 18);
  Serial.print(rawServoData[5]);
  delay(1);
}

void Map_Servo_Data() {
  servoData[0] = map(rawServoData[0], 0, 1491, 553, 2399); // Map the 'rawServoData[]' values into values suitable for your servos. Can be into °rotation or pwm values
  servoData[1] = map(rawServoData[1], 0, 1491, 553, 2399); // This function could be handled in a loop but testing revealed a slightly shorter processing time using this method.
  servoData[2] = map(rawServoData[2], 0, 1491, 553, 2399);
  servoData[3] = map(rawServoData[3], 0, 1491, 553, 2399);	// you can also use the min/max values output from "MM_stewart_find_servo_ranges2.ino" here to fine tune.
  servoData[4] = map(rawServoData[4], 0, 1491, 553, 2399);
  servoData[5] = map(rawServoData[5], 0, 1491, 553, 2399);
}

void Set_Servos2() {
  servo[0].write(servoData[0]);                               // Method 2 (slightly faster):
  //Serial.print(servoData[0]);
  servo[1].write(servoData[1]);                               // Write the scaled values to each servo. No loop.
  //Serial.print(servoData[1]);
  servo[2].write(servoData[2]);
  //Serial.print(servoData[2]);
  servo[3].write(servoData[3]);
  //Serial.print(servoData[3]);
  servo[4].write(servoData[4]);
  //Serial.print(servoData[4]);
  servo[5].write(servoData[5]);
  //Serial.print(servoData[5]);
}
