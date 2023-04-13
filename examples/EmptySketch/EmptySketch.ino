/**
 * @file EmptySketch.ino
 * @author ModuleMore Co.,Ltd. Thanabadee Bulunseechart (modulemore@gmail.com)
 * @brief Example of an empty sketch for the ModuleMore Sumo V2 robot using the ModuleMoreSumoV2 library 
 * @version 1.0
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023 ModuleMore Co.,Ltd.
 * 
 */

#include <Arduino.h>
#include "ModuleMoreSumoV2.h"
 
enemy_detector  _enemy(SENSOR_VL530X);    // Define the enemy detector using the VL530X sensor called _enemy
line_detector   _line;                    // Define the line detector called _line
driver          _driver;                  // Define the driver called _driver
robot_ui        _robot;                   // Define the robot UI called _robot

void setup()
{ 
 
  Serial.begin (115200);                  // Start the serial communication at 115200 bauds
  while(!Serial) delay(1);                // Wait for the serial communication to be established
 
  _enemy.init();                          // Initialize the enemy detector
    _enemy.setDetectThreshold(600);       // Set the threshold to detect an enemy
    _enemy.setInvalidRange(1000);         // Set the invalid range    
    _enemy.setRangeFar(300);              // Set the range for the enemy to be far

  _line.init();                           // Initialize the line detector
    _line.setThreshold(300);              // Set the threshold to detect a line

  _driver.init();                         // Initialize the driver
    _driver.setMaxSpeed(150);             // Set the maximum speed of the robot
    _driver.always_stop(false);           // Set the robot to stop when the robot is not in auto mode

  _robot.init();                          // Initialize the robot UI
    _robot.setCountdown(5000);            // Set the countdown to 5 seconds

}

void loop()
{ 
  _robot.update();                        // Update the robot UI eg. the countdown, the start button, the dip switches
  _line.update();                         // Update the line detector 
  _enemy.update();                        // Update the enemy detector

  if (_robot.isRobotStartAuto()) {        // If the robot is in auto mode
    /**
     * @brief YOU CODE
     */

  } else {
    _driver.stop();                       // Stop the robot if the robot is not in auto mode
  } 

  delay(1);                               // Wait 1ms before the next loop
} 