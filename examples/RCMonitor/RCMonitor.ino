#include <Arduino.h>
#include "ModuleMore_Sumo_V2.h"  

robot_ui        _robot;                   // Define the robot UI called _robot
  

void setup()
{ 
 
  Serial.begin (115200);                  // Start the serial communication with the baud rate of 115200
  while(!Serial) delay(1);                // Wait for the serial communication to be ready
  _robot.init();                          // Initialize the robot UI

}

void loop()
{ 
  delay(1);
  _robot.update();                        // Update the robot UI e.g., countdown, start button, dip switches, state LED

  Serial.print("RC:");
  
  for(int i=1; i<=7; i++) {
    Serial.print("\t");
    Serial.print(_robot.getRCRaw(i));
  }
  Serial.println();
 
  
} 