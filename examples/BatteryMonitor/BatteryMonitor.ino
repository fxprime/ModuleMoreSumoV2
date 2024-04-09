#include <Arduino.h>
#include "ModuleMore_Sumo_V2.h" 
 
robot_ui        _robot;  //This is the robot UI module (button, mode, etc.)
 
void setup()
{ 
 
  Serial.begin (115200); 
  _robot.init();                            //Initialize the robot UI module 
  
}

void loop()
{
  _robot.update();                        //Update the robot UI module

  Serial.print("Battery: ");
  Serial.print(_robot.getBatteryPCT());
  Serial.print("%\t");
  Serial.print(_robot.getBatteryVoltage());
  Serial.print("V\t");
  Serial.print(_robot.getBatteryCurrent()); 
  Serial.println("mA");

  delay(1);
} 