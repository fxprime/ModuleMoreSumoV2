/**
 * @file RawData.ino
 * @author ModuleMore Co.,Ltd. Thanabadee Bulunseechart (modulemore@gmail.com)
 * @brief Example of how to use the raw data from the enemy detector and the line detector to debug the robot
 * @version 1.0
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023 ModuleMore Co.,Ltd.
 * 
 */
#include <Arduino.h>
#include "ModuleMore_Sumo_V2.h"
 
enemy_detector  _enemy(SENSOR_VL530X);      // Define the enemy detector using the VL530X sensor called _enemy
line_detector   _line;                      // Define the line detector called _line

void setup()
{ 
 
    Serial.begin (115200);                  // Start the serial communication
    while(!Serial) delay(1);                // Wait for the serial communication to be ready

    _enemy.init();                          // Initialize the enemy detector
    _line.init();                           // Initialize the line detector

}

void loop()
{   
    /**
     * @brief Debug the raw data of the robot
     * 
     */
    _enemy.update();                        // Update the enemy detector
    _line.update();                         // Update the line detector

    Serial.print("D : ");
    Serial.print(_enemy.getRawData(DIST_LEFT));     // Print the raw data of the left distance sensor
    Serial.print(", ");
    Serial.print(_enemy.getRawData(DIST_FRONT));    // Print the raw data of the front distance sensor
    Serial.print(", ");
    Serial.print(_enemy.getRawData(DIST_RIGHT));    // Print the raw data of the right distance sensor
    Serial.print(", ");
    Serial.print("L : ");
    Serial.print(_line.getRawData(IR_LEFT));        // Print the raw data of the left IR sensor
    Serial.print(", ");
    Serial.print(_line.getRawData(IR_RIGHT));       // Print the raw data of the right IR sensor
    Serial.print("\n");  
  

    delay(100);
}