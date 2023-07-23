#include <Arduino.h>
#include "ModuleMore_Sumo_V2.h"
#include "ppm.h"

#define PPM_INPUT       4

#define THROTTLE        3
#define ROLL            1
#define PITCH           2
#define YAW             4
#define SWITCH3WAY_1    5
#define BUTTON          6
#define SWITCH3WAY_2    7     
#define POT             8  

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
    _robot.setCountdown(100);              //Set the countdown time in auto mode (0.1s)

  ppm.begin(4, false);
}

void loop()
{
    _robot.update();                        //Update the robot UI module
    if (_robot.isRobotStartAuto()) {

      // Read the PPM signal
      short throttle      =   ppm.read_channel(THROTTLE);
      short roll          =   ppm.read_channel(ROLL); 

      // Map the PPM signal to the speed and steer
      float speed_pct = map(throttle, 900,2100, -1000, 1000)/10.0;   //[-100, 100]
      float steer_pct = map(roll, 900, 2100, -1000, 1000)/10.0;      //[-100, 100]

      // Normalize the speed and steer
      float sum_normalized = fabs(speed_pct) + fabs(steer_pct);
      if (sum_normalized >= 100) {
        float scale_factor = 100 / sum_normalized;
        speed_pct *= scale_factor;
        steer_pct *= scale_factor;
      }

      Serial.print(speed_pct);
      Serial.print("\t");
      Serial.println(steer_pct);

      // Drive the robot
      if(fabs(speed_pct) > 5 || fabs(steer_pct) > 5) { 
        int8_t M_left = speed_pct + steer_pct;
        int8_t M_right = speed_pct - steer_pct;
        _driver.drive(M_left, M_right);
      }else{
        _driver.stop();
      }

    } 
    delay(1);
} 