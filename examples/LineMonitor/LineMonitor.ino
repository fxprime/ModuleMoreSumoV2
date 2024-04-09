#include <Arduino.h>
#include "ModuleMore_Sumo_V2.h"  

robot_ui        _robot;                   // Define the robot UI called _robot
line_detector   _line;                    // Define the line detector called _line



void setup()
{ 
 
  Serial.begin (115200);                  // Start the serial communication with the baud rate of 115200
  while(!Serial) delay(1);                // Wait for the serial communication to be ready

  _robot.init();                          // Initialize the robot UI
  _line.init();                           // Initialize the line detector
  _line.setThreshold(300);                // Set the threshold for the line detector
}

void loop()
{ 
  delay(1);
  _line.update();

  if(!_line.isLineDetected()) {
    Serial.print("No line detected");
  } else if(_line.isLineDetectedFrontLeft()) {
    Serial.print("Line detected front left");
  } else if(_line.isLineDetectedFront()) {
    Serial.print("Line detected front");
  } else if(_line.isLineDetectedFrontRight()) {
    Serial.print("Line detected front right");
  } else {
    Serial.print(" ?");
  }

  Serial.print("\tLeft: ");
  Serial.print(_line.getRawData(IR_LEFT));
  Serial.print("\tRight: ");
  Serial.println(_line.getRawData(IR_RIGHT));

 
  
} 