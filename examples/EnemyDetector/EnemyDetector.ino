#include <Arduino.h>
#include "ModuleMore_Sumo_V2.h"  

enemy_detector  _enemy(SENSOR_VL530X);    // Define the enemy detector using the VL530X sensor called _enemy
robot_ui        _robot;                   // Define the robot UI called _robot
  

void setup()
{ 
 
  Serial.begin (115200);                  // Start the serial communication with the baud rate of 115200
  while(!Serial) delay(1);                // Wait for the serial communication to be ready

  _enemy.init();                          // Initialize the enemy detector
  _enemy.setDetectThreshold(600);         // Set the threshold for the enemy detector 
  _enemy.setInvalidRange(1000);           // Set the invalid range for the enemy detector
  _enemy.setRangeFar(350);                // Set the range for the enemy detector
  _enemy.setRangeMid(250);                // Set the range for the enemy detector
  _enemy.setRangeClose(150);              // Set the range for the enemy detector
 
  _robot.init();                          // Initialize the robot UI

}

void loop()
{ 
  delay(1);
  _robot.update();                        // Update the robot UI e.g., countdown, start button, dip switches, state LED
  _enemy.update();                        // Update the enemy detector
  
  if(_enemy.at_front()) {
    Serial.print("Enemy at front : ");
  }else if (_enemy.at_front_left()) {
    Serial.print("Enemy at front left : ");
  }else if (_enemy.at_front_right()) {
    Serial.print("Enemy at front right : ");
  }else if (_enemy.at_left()) {
    Serial.print("Enemy at left : ");
  }else if (_enemy.at_right()) {
    Serial.print("Enemy at right : ");
  }else {
    Serial.println("No enemy detected.");
  }

  if(!_enemy.detected()) return;
  
  if(_enemy.enemy_close()) {
    Serial.print("CLOSE");
  } else if(_enemy.enemy_mid()) {
    Serial.print("MID");
  } else if(_enemy.enemy_far()) {
    Serial.print("FAR");
  } 

  Serial.print(" - ");
  Serial.print(_enemy.getRawData(DIST_LEFT));
  Serial.print(" - ");
  Serial.print(_enemy.getRawData(DIST_FRONT));
  Serial.print(" - ");
  Serial.println(_enemy.getRawData(DIST_RIGHT));

  
} 