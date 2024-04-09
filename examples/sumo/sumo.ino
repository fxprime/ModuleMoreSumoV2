/**
 * @file sumo.ino
 * @author ModuleMore Co.,Ltd. Thanabadee Bulunseechart (modulemore@gmail.com)
 * @brief Example sketch of how to use the ModuleMore Sumo V2 library to make sumo robot with the ModuleMore Sumo V2 robot
 * @version 1.0
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023 ModuleMore Co.,Ltd.
 * 
 */
#include <Arduino.h>
#include "ModuleMore_Sumo_V2.h"  

enemy_detector  _enemy(SENSOR_VL530X);    // Define the enemy detector using the VL530X sensor called _enemy
line_detector   _line;                    // Define the line detector called _line
driver          _driver;                  // Define the driver called _driver
robot_ui        _robot;                   // Define the robot UI called _robot
  
bool enemyDetected();                     // Declare the function enemyDetected()
bool lineDetected();                      // Declare the function lineDetected()
void avoidLine();                         // Declare the function avoidLine()
void searchForEnemy();                    // Declare the function searchForEnemy()
void attackEnemy();                       // Declare the function attackEnemy()

void setup()
{ 
 
  Serial.begin (115200);                  // Start the serial communication with the baud rate of 115200
  while(!Serial) delay(1);                // Wait for the serial communication to be ready

  _enemy.init();                          // Initialize the enemy detector
  _enemy.setDetectThreshold(600);         // Set the threshold for the enemy detector 
  _enemy.setInvalidRange(1000);           // Set the invalid range for the enemy detector
  _enemy.setRangeFar(300);                // Set the range for the enemy detector

  _line.init();                           // Initialize the line detector
  _line.setThreshold(300);                // Set the threshold for the line detector

  _driver.init();                         // Initialize the driver
  _driver.setMaxSpeed(150);               // Set the maximum speed for the driver
  _driver.always_stop(false);             // Set this to true to alway stop robot for debugging purpose

  _robot.init();                          // Initialize the robot UI

}

void loop()
{ 
  _robot.update();                        // Update the robot UI e.g., countdown, start button, dip switches, state LED
  _line.update();                         // Update the line detector
  _enemy.update();                        // Update the enemy detector

  /**
   * @brief If the robot is in auto mode, check if the line is detected, if the enemy is detected then attack. Or if nothing is detected then search for the enemy by the pattern wrote in the function searchForEnemy()
   */
  if (_robot.isRobotStartAuto()&& !_robot.isBatteryLow()) {      
    if (lineDetected()) {
      avoidLine();
    } else if (enemyDetected()) {
      attackEnemy();
    } else {
      searchForEnemy();
    }
  } else {
    _driver.stop();
  }  
  delay(1);
}







/**
 * @brief Check if white line is detected in each of the 3 sensors
 * 
 * @return true 
 * @return false 
 */
bool lineDetected() {
  return _line.isLineDetected();
}

/**
 * @brief Get away from the line by reversing and turning right (example)
 * 
 */
void avoidLine() {
  // Serial.println("Avoiding Line");
  _driver.reverseForMs(400);
  _driver.rotateRightForMs(400);
}

/**
 * @brief Check if enemy is detected in each of the 3 sensors
 * 
 * @return true 
 * @return false 
 */
bool enemyDetected() {
  return _enemy.detected();
}

/**
 * @brief Attack the enemy in the enemy direction given by the enemy detector
 * 
 */
void attackEnemy() {
  // Serial.println("Attacking Enemy");
  if (_enemy.at_front()) {
    if(_enemy.enemy_close())
      _driver.forward(SPEED_FASTEST); // Fastest attack enemy
    else if(_enemy.enemy_mid())
      _driver.forward(SPEED_FAST);    // Fast to catch up enemy
    else if(_enemy.enemy_far())
      _driver.forward(SPEED_MEDIUM);  // Go easy to check movement of enemy
  } 
  
  
  else if (_enemy.at_front_left()) {
    if(_enemy.enemy_far())
      _driver.arcTurnWideLeft(SPEED_MEDIUM);
    else if(_enemy.enemy_mid() || _enemy.enemy_close())
      _driver.arcTurnMidLeft(SPEED_FAST);
  } 
  
  else if (_enemy.at_front_right()) {
    if(_enemy.enemy_far())
      _driver.arcTurnWideRight(SPEED_MEDIUM);
    else if(_enemy.enemy_mid() || _enemy.enemy_close())
      _driver.arcTurnMidRight(SPEED_FAST);
  } 
  
  else if (_enemy.at_left()) {
    if(_enemy.enemy_close())
      _driver.arcTurnSharpLeft(SPEED_FAST);
    else if(_enemy.enemy_mid() || _enemy.enemy_far())
      _driver.arcTurnMidLeft(SPEED_FAST); 
  } 
  
  else if (_enemy.at_right()) {
    if(_enemy.enemy_close())
      _driver.arcTurnSharpRight(SPEED_FAST);
    else if(_enemy.enemy_mid() || _enemy.enemy_far())
      _driver.arcTurnMidRight(SPEED_FAST); 
  } 
}

/**
 * @brief Keep curving move left to search for the enemy
 * 
 */
void searchForEnemy() {
    _driver.arcTurnMidLeft(SPEED_MEDIUM);
}
