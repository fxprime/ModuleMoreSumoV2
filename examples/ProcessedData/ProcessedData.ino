/**
 * @file ProcessedData.ino
 * @author ModuleMore Co.,Ltd. Thanabadee Bulunseechart (modulemore@gmail.com)
 * @brief Example of how to use the processed data from the enemy detector and the line detector to debug the robot
 * @version 1.0
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023 ModuleMore Co.,Ltd.
 * 
 */
#include <Arduino.h>
#include "ModuleMoreSumoV2.h"

  
enemy_detector  _enemy(SENSOR_VL530X);      // Define the enemy detector using the VL530X sensor called _enemy
line_detector   _line;                      // Define the line detector called _line
  

void setup()
{ 
 
  Serial.begin (115200);                    // Start the serial communication
 
  _enemy.init();                            // Initialize the enemy detector
    _enemy.setDetectThreshold(999);         // Set the threshold for the enemy detector
    _enemy.setInvalidRange(1000);           // Set the invalid range for the enemy detector
    _enemy.setRangeFar(750);                // Set the far range for the enemy detector

  _line.init();                             // Initialize the line detector
    _line.setThreshold(300);                // Set the threshold for the line detector

}

void loop()
{
   
  /**
   * @brief Debug the status of the robot
   * 
   */
  _enemy.update();                          // Update the enemy detector
  _line.update();                           // Update the line detector

  Serial.print("Enemy: "); 
  Serial.print(_enemy.pos_str());           // Print the position of the enemy
  Serial.print(" ");
  Serial.print(_enemy.range_str());         // Print the range of the enemy
  Serial.print(" Line: ");
  Serial.println(_line.str());              // Print the status of the line detector

  delay(100);
}