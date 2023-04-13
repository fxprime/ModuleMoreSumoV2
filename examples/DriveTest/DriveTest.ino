#include <Arduino.h>
#include "ModuleMoreSumoV2.h"
  
driver          _driver; //This is the driver module (motor, encoder, etc.)
robot_ui        _robot;  //This is the robot UI module (button, mode, etc.)
 
bool RobotStateFn(void) { return _robot.isRobotStartAuto(); } //This function is called by the driver to check if the robot is in auto mode

void setup()
{ 
 
  Serial.begin (115200);
  
  _driver.init();                           //Initialize the driver module
    _driver.setMaxSpeed(150);               //Set the maximum speed of the robot
    _driver.always_stop(false);             //Set the driver to always block the motor from running. This is useful for debugging.
    _driver.setRobotStateFn(RobotStateFn);  //Set the function that the driver will call to check if the robot is in auto mode
 
  _robot.init();                            //Initialize the robot UI module
    _robot.setCountdown(5000);              //Set the countdown time in auto mode (5s)

}

void loop()
{
    _robot.update();                        //Update the robot UI module

    if (_robot.isRobotStartAuto()) {        //Check if the robot is in auto mode
        Serial.println("RUN");
        _driver.forwardForMs(300);          //Drive forward for 300ms
        _driver.reverseForMs(300);          //Drive backward for 300ms
        _driver.rotateRightForMs(500);      //Rotate right for 500ms
        _driver.rotateLeftForMs(1000);      //Rotate left for 1000ms
        _driver.arcTurnSharpRightForMs(1000); //Arc turn right for 1000ms
        _driver.ReverseArcTurnSharpRightForMs(1000); //Reverse Arc turn right for 1000ms
        _driver.arcTurnSharpLeftForMs(1000); //Arc turn left for 1000ms
        _driver.ReverseArcTurnSharpLeftForMs(1000); //Reverse Arc turn left for 1000ms
        _driver.arcTurnMidRightForMs(1000);   //Arc turn right for 1000ms
        _driver.ReverseArcTurnMidRightForMs(1000);  //Arc turn right for 1000ms
        _driver.arcTurnMidLeftForMs(1000);   //Arc turn left for 1000ms
        _driver.ReverseArcTurnMidLeftForMs(1000); //Arc turn left for 1000ms
        _driver.arcTurnWideRightForMs(1000);   //Arc turn right for 1000ms
        _driver.ReverseArcTurnWideRightForMs(1000); //Arc turn right for 1000ms
        _driver.arcTurnWideLeftForMs(1000);   //Arc turn left for 1000ms
        _driver.ReverseArcTurnWideLeftForMs(1000); //Arc turn left for 1000ms
        Serial.println("STOP");               
        _driver.stop();                      //Stop the robot
        _driver.wait(10000);                 //Wait for 10s
    }  
 
    delay(1);
} 