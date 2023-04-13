/**
 * @file SwitchTest.ino
 * @author ModuleMore Co.,Ltd. Thanabadee Bulunseechart (modulemore@gmail.com)
 * @brief Example of how to use the robot UI to get the button and dip switch state
 * @version 1.0
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023 ModuleMore Co.,Ltd.
 * 
 */
#include <Arduino.h>
#include "ModuleMore_Sumo_V2.h"  
  
robot_ui        _robot;   // Robot UI contain button and dip switch and LED called _robot
   

void setup()
{ 
 
  Serial.begin (115200);      // Init serial communication with baudrate 115200
  while(!Serial) delay(1);    // Wait for serial communication ready
 
  _robot.init();              // Init robot UI

}

void loop()
{ 
  _robot.updateButton();  // Update button state
  _robot.updateMode();    // Update dip switch state

  /** GET Raw button state */
  Serial.println("\n\n\n");
  Serial.print("Is pressed ? ");
  Serial.println(_robot.getRawButton() == robot_ui::BUTTON_PRESSED);   // Get raw button state if it pressed
  Serial.print("Is released ? ");
  Serial.println(_robot.getRawButton() == robot_ui::BUTTON_RELEASED);  // Get raw button state if it releaseed 
  Serial.print("DIP SW : ");
  Serial.println(_robot.getRawMode());  // Get dip switch integer
  Serial.print("Mode Int : ");
  Serial.println(_robot.getMode());     // Get mode integer
  Serial.print("Mode Str : ");
  Serial.println(_robot.getModeStr());  // Get mode string
  Serial.println("======================");
   
   
  delay(100);
}