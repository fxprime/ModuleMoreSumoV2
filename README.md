# ModuleMore Sumo robot V2
ไลบรารี่สำหรับหุ่นยนต์ ModuleMore Sumo Robot V2 สำหรับใช้ฝึกฝนการเขียนโปรแกรมโดยใช้หุ่นยนต์จริงช่วยให้เห็นภาพยิ่งขึ้น

ไลบรารี่นี้ประกอบด้วยฟังก์ชันอำนวยความสะดวกเพื่อให้สามารถอ่านค่าเซนเซอร์ต่าง ๆ ได้อย่างเป็นรูปธรรม โดยไม่จำเป็นต้องยุ่งกับส่วนที่เป็น low-level code มากนัก จึงเหมาะสำหรับผู้เริ่มต้น และผู้ที่สนใจในการนำไปแข่งขันในรายการ Mini Sumo Robot ต่าง ๆ    

<br><br>

## Installation
1. Open the Arduino IDE, select `Sketch` -> `Include Library` -> `Manage Libraries...`.
2. Search for `ModuleMore Sumo V2`.
3. Click `Install` to install the library. 
4. Examples can be opened in Arduino IDE from `File` -> `Examples` -> `ModuleMore Sumo V2` -> `ProcessedData`.
 
**Example Code:**<br>
```c++
#include <Arduino.h>
#include "ModuleMoreSumoV2.h"
 
enemy_detector  _enemy(SENSOR_VL530X);
line_detector   _line;
driver          _driver; 
robot_ui        _robot;  

void setup()
{ 
 
  Serial.begin (115200);
  while(!Serial) delay(1);
 
  _enemy.init(); 
  _line.init(); 
  _driver.init(); 
  _robot.init();

}

void loop()
{ 
  _robot.update();  
  _line.update();
  _enemy.update();

  if (_robot.isRobotStartAuto()) { 
    /**
     * @brief YOU CODE
     */

  } else {
    _driver.stop();
  } 

  delay(1);
} 
```

<!-- ## Library Functions
These functions are provided in the library:<br>
- [begin()](https://github.com/fxprime/ModuleMoreSumoV2#makersumobegin)
- [readDipSwitch()](https://github.com/fxprime/ModuleMoreSumoV2#makersumoreaddipswitch)
- [readBatteryVoltage()](https://github.com/fxprime/ModuleMoreSumoV2#makersumoreadbatteryvoltage)
- [stop()](https://github.com/fxprime/ModuleMoreSumoV2#makersumostop)
- [moveForward()](https://github.com/fxprime/ModuleMoreSumoV2#makersumomoveforward)
- [moveBackward()](https://github.com/fxprime/ModuleMoreSumoV2#makersumomovebackward)
- [turnLeft()](https://github.com/fxprime/ModuleMoreSumoV2#makersumoturnleft)
- [turnRight()](https://github.com/fxprime/ModuleMoreSumoV2#makersumoturnright)
- [setMotorSpeed()](https://github.com/fxprime/ModuleMoreSumoV2#makersumosetmotorspeed)
- [setServoPosition()](https://github.com/fxprime/ModuleMoreSumoV2#makersumosetservoposition)
- [playMelody()](https://github.com/fxprime/ModuleMoreSumoV2#makersumoplaymelody)
- [calibrateEdgeSensors()](https://github.com/fxprime/ModuleMoreSumoV2#makersumocalibrateedgesensors)
- [readEdgeSensorThreshold()](https://github.com/fxprime/ModuleMoreSumoV2#makersumoreadedgesensorthreshold)
- [isEdgeDetected()](https://github.com/fxprime/ModuleMoreSumoV2#makersumoisedgedetected) -->

<br>

## Function Usage 

<details>
  <summary>Motor Driver (<i>driver</i>)</summary>

  ### init()
  Initialize the I/O pins of the controller.<br>
  Must be called once before using motor drive function.
  
  **Syntax:**
  `void driver.init(void);`

  **Parameters:**
  None

  **Returns:**
  None

  **Example Code:**
  ```
  driver _driver;
  void setup() {
    _driver.init();
  }
  ```

  <br>

  ### stop()
  Stop All motor safely.
  
  **Syntax:**
  `void driver.stop(void);`

  **Parameters:**
  None

  **Returns:**
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  driver _driver;
  void setup() {
    _driver.init();
    _driver.stop(); //Stop All motors.
  }
  ```

  <br>

  ### wait(ms)
  Block the program for specific time (in millisecond). <br>
  Note that motor will continue rotate if movement function is called before this function.
  
  **Syntax:**
  `void driver.wait(uint32_t ms);`

  **Parameters:**
  - ***ms*** - Time to wait until next function run (in millisecond).

  **Returns:**
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  driver _driver;
  void setup() {
    _driver.init();

    _driver.forward();          //Forward
    _driver.wait(5000);         //Wait for 5s
    _driver.stop();             //Stop All motors

    //The result is the robot 
    //move forward for 5s then stop 
  }
  ```
  <br>

  ### forward()
  Control robot forward without limit of time.
  
  **Syntax:**
  `void driver.forward();`

  **Parameters:**
  None

  **Returns:**
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  driver _driver;
  void setup() {
    _driver.init(); 
    _driver.stop();
    _driver.wait(1000);         //Wait for 1s, The robot remain stop in this period
    _driver.forward();          //Send command to move forward
    _driver.wait(1000);         //Wait for 1s, The robot will continue forward in this period
    _driver.stop();             //Stop All motors
  }
  ```

  **Similar functions**
  ```c++ 
  void reverse();
  void rotateLeft();
  void rotateRight();
  void arcTurnSharpLeft();
  void arcTurnSharpRight();
  void arcTurnMidLeft();
  void arcTurnMidRight();
  void arcTurnWideLeft();
  void arcTurnWideRight();
  void ReverseArcTurnSharpLeft();
  void ReverseArcTurnSharpRight();
  void ReverseArcTurnMidLeft();
  void ReverseArcTurnMidRight();
  void ReverseArcTurnWideLeft();
  void ReverseArcTurnWideRight();
  ```

  <br>

  ### forward(speed)
  Control robot forward without limit of time with specific speed.
  
  **Syntax:**
  `void driver.forward(drive_speed_t drive_speed);`

  **Parameters:**
  - ***drive_speed*** - Speed of the robot. 
      `SPEED_SLOW` - Slow speed
      `SPEED_MEDIUM` - Medium speed (Default)
      `SPEED_FAST` - Fast speed
      `SPEED_FASTEST` - Fastest speed

  **Returns:**
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  driver _driver;
  void setup() {
    _driver.init(); 
    _driver.stop();             //Stop All motors
    _driver.wait(1000);        //Wait for 1s
    _driver.forward(SPEED_SLOW);          //Forward
    _driver.wait(1000);        //Wait for 1s
    _driver.forward(SPEED_MEDIUM);          //Forward
    _driver.wait(1000);        //Wait for 1s
    _driver.forward(SPEED_FAST);          //Forward
    _driver.wait(1000);        //Wait for 1s  
  }
  ```

  **Similar functions**
  ```c++ 
  void reverse(drive_speed_t drive_speed);
  void rotateLeft(drive_speed_t drive_speed);
  void rotateRight(drive_speed_t drive_speed);
  void arcTurnSharpLeft(drive_speed_t drive_speed);
  void arcTurnSharpRight(drive_speed_t drive_speed);
  void arcTurnMidLeft(drive_speed_t drive_speed);
  void arcTurnMidRight(drive_speed_t drive_speed);
  void arcTurnWideLeft(drive_speed_t drive_speed);
  void arcTurnWideRight(drive_speed_t drive_speed);
  void ReverseArcTurnSharpLeft(drive_speed_t drive_speed);
  void ReverseArcTurnSharpRight(drive_speed_t drive_speed);
  void ReverseArcTurnMidLeft(drive_speed_t drive_speed);
  void ReverseArcTurnMidRight(drive_speed_t drive_speed);
  void ReverseArcTurnWideLeft(drive_speed_t drive_speed);
  void ReverseArcTurnWideRight(drive_speed_t drive_speed);
  ```

  <br>
  
  ### forwardForMs(ms)
  Control robot forward for specific of time (in millisecond).
  
  **Syntax:**
  `void driver.forwardForMs(uint32_t ms);`

  **Parameters:**
  - ***ms*** - Time to forward until stop (in millisecond).

  **Returns:**
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  driver _driver;
  void setup() {
    _driver.init(); 
    _driver.forwardForMs(1000);          //Forward for 1s and stop
  }
  ```

  **Similar functions**
  ```c++ 
  void reverseForMs(uint32_t ms);
  void rotateLeftForMs(uint32_t ms);
  void rotateRightForMs(uint32_t ms);
  void arcTurnSharpLeftForMs(uint32_t ms);
  void arcTurnSharpRightForMs(uint32_t ms);
  void arcTurnMidLeftForMs(uint32_t ms);
  void arcTurnMidRightForMs(uint32_t ms);
  void arcTurnWideLeftForMs(uint32_t ms);
  void arcTurnWideRightForMs(uint32_t ms);
  void ReverseArcTurnSharpLeftForMs(uint32_t ms);
  void ReverseArcTurnSharpRightForMs(uint32_t ms);
  void ReverseArcTurnMidLeftForMs(uint32_t ms);
  void ReverseArcTurnMidRightForMs(uint32_t ms);
  void ReverseArcTurnWideLeftForMs(uint32_t ms);
  void ReverseArcTurnWideRightForMs(uint32_t ms);
  ```

  <br>
  
  ### forwardForMs(ms, speed)
  Control robot forward for specific of time (in millisecond). And set the speed of the motor. 
  
  **Syntax:**
  `void driver.forwardForMs(uint32_t ms, drive_speed_t drive_speed);`

  **Parameters:**
  - ***ms*** - Time to forward until stop (in millisecond).
  - ***speed*** - Speed of the motor 
      `SPEED_SLOW`
      `SPEED_MEDIUM`
      `SPEED_FAST`
      `SPEED_FASTEST`

  **Returns:**
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  driver _driver;
  void setup() {
    _driver.init(); 
    _driver.wait(1000);                              //Wait for 1s
    _driver.forwardForMs(1000, SPEED_FAST);          //Forward for 1s and stop
    _driver.wait(1000);                              //Wait for 1s
    _driver.backwardForMs(1000, SPEED_SLOW);         //Backward for 1s and stop
  }
  ```

  **Similar functions**
  ```c++ 
  void reverseForMs(uint32_t ms, drive_speed_t drive_speed);
  void rotateLeftForMs(uint32_t ms, drive_speed_t drive_speed);
  void rotateRightForMs(uint32_t ms, drive_speed_t drive_speed);
  void arcTurnSharpLeftForMs(uint32_t ms, drive_speed_t drive_speed);
  void arcTurnSharpRightForMs(uint32_t ms, drive_speed_t drive_speed);
  void arcTurnMidLeftForMs(uint32_t ms, drive_speed_t drive_speed);
  void arcTurnMidRightForMs(uint32_t ms, drive_speed_t drive_speed);
  void arcTurnWideLeftForMs(uint32_t ms, drive_speed_t drive_speed);
  void arcTurnWideRightForMs(uint32_t ms, drive_speed_t drive_speed);
  void ReverseArcTurnSharpLeftForMs(uint32_t ms, drive_speed_t drive_speed);
  void ReverseArcTurnSharpRightForMs(uint32_t ms, drive_speed_t drive_speed);
  void ReverseArcTurnMidLeftForMs(uint32_t ms, drive_speed_t drive_speed);
  void ReverseArcTurnMidRightForMs(uint32_t ms, drive_speed_t drive_speed);
  void ReverseArcTurnWideLeftForMs(uint32_t ms, drive_speed_t drive_speed);
  void ReverseArcTurnWideRightForMs(uint32_t ms, drive_speed_t drive_speed);
  ```

  <br>


</details>
 
<details>
  <summary>Line Detector (<i>line_detector</i>)</summary>

  ### init()
  Initialize the I/O pins of the controller.
  Must be called once before using Line Detector functions.
  
  **Syntax:**
  ```c++
  void line_detector.init(void);
  ```

  **Parameters:**
  None

  **Returns:**
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  line_detector _line;
  void setup() {
    _line.init();
  }
  ``` 

  <br>

  ### update()
  Use this inside the loop() to keep sensor up-to-date or
  sensor data will stay the same.
  
  **Syntax:**
  ```c++
  void line_detector.update(void);
  ```

  **Parameters:**
  None

  **Returns:**
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  line_detector _line;
  void setup() {
    _line.init();
  }

  void loop() {
    _line.update();
  }
  ``` 
  
  <br>

  ### str()
  Use this inside Serial.print to monitor the detection status in plain text. Which is useful for check the sensor healthy.
  
  **Syntax:**
  ```c++
  const char* line_detector.str(void);
  ```

  **Parameters:**
  None

  **Returns:**
  ```c++
  "LINE_DETECTION_NONE"
  "LINE_DETECTION_FRONT" 
  "LINE_DETECTION_FRONT_LEFT" 
  "LINE_DETECTION_FRONT_RIGHT" 
  ```

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  line_detector _line;
  void setup() {
    _line.init();
  }

  void loop() {
    _line.update();
    Serial.println(_line.str());
    delay(50);
  }
  ``` 
  
  <br>

  ### setThreshold(threshold) (default : 300)
  When the line detection str return wrong value, try to set the threshold by half of black and white value. The black and white value can be obtained from getRawValue function.
  
  **Syntax:**
  ```c++
  void line_detector.setThreshold(int threshold);
  ```

  **Parameters:**
  - ***threshold*** - Value of infrared line sensor that considered to be white line detected.

  **Returns:**
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  line_detector _line;
  void setup() {
    _line.init();
    _line.setThreshold(200);
  } 
  ``` 
  
  <br>

  ### get_detection()
  Return the state of detection for examples. 
  
  **Syntax:**
  ```c++
  detection_t line_detector.get_detection(void);
  ```

  **Parameters:**
  None

  **Returns:**
  ```c++
  LINE_NOTFOUND
  LINE_FRONT
  LINE_FRONT_LEFT
  LINE_FRONT_RIGHT
  ```

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  line_detector _line;
  void setup() {
    _line.init(); 
  } 

  void loop() {
    _line.update();
    if(_line.get_detection() == LINE_FRONT) {
      Serial.println("Line : Detected front"); 
    }else if(_line.get_detection() == LINE_FRONT_LEFT) {
      Serial.println("Line : Detected on left"); 
    }else if(_line.get_detection() == LINE_FRONT_RIGHT) {
      Serial.println("Line : Detected on right");
    }else{
      Serial.println("Line : Not detected :)");
    }
    delay(100);
  }
  ``` 
  
  <br>

  ### getRawData(id)
  Return the state of detection for examples. 
  
  **Syntax:**
  ```c++
  int16_t line_detector.get_detection(infrared_idx idx);
  ```

  **Parameters:**
  - ***idx*** - Index of sensor that you interest to check raw data. Options are `IR_LEFT` or `IR_RIGHT` 

  **Returns:** 
  0-1023 - 0 Mean black area. more value mean more white.

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  line_detector _line;
  void setup() {
    _line.init(); 
  } 

  void loop() {
    _line.update();
    Serial.print(_line.getRawData(IR_LEFT));
    Serial.print(", ");
    Serial.println(_line.getRawData(IR_RIGHT));
    delay(100);
  }
  ``` 
  
  <br> 

  ### isLineDetected()
  Return the state of detection for examples. 
  
  **Syntax:**
  ```c++
  bool line_detector.isLineDetected();
  ```

  **Parameters:**
  None

  **Returns:** 
  `True / False` - Line detected (True mean white line found by any sensors or all sensors).

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  line_detector _line;
  void setup() {
    _line.init(); 
  } 

  void loop() {
    _line.update();
    Serial.print("Line Detected : ");
    Serial.println(_line.isLineDetected());
    delay(100);
  }
  ``` 

  **Similar function:**
  ```c++
  bool line_detector.isLineDetectedFront();     //Return True, When white line found by both sensor on front.
  bool line_detector.isLineDetectedFrontLeft(); //Return True, When white line found by left sensor.
  bool line_detector.isLineDetectedFrontRight();//Return True, When white line found by right sensor.
  ```
  
  <br>

</details>
 
<details>
  <summary>Enemy Detection (<i>enemy_detector</i>)</summary>

  ### init()
  Initialize the I/O pins of the controller.
  Must be called once before using Enemy Detector functions.
  
  **Syntax:**
  ```c++
  void enemy_detector.init(void);
  ```

  **Parameters:**
  None

  **Returns:**
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init();
  }
  ``` 

  <br> 

  ### update()
  Use this inside the loop() to keep sensor up-to-date or
  sensor data will stay the same.
  
  **Syntax:**
  ```c++
  void enemy_detector.update();
  ```

  **Parameters:**
  None

  **Returns:** 
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init(); 
  } 

  void loop() {
    _enemy.update();  
    delay(10);
  }
  ```  
  
  <br>

  ### pos_str()
  Return the position of enemy for monitor purpose. 
  
  **Syntax:**
  ```c++
  const char *enemy_detector.pos_str();
  ```

  **Parameters:**
  None

  **Returns:** 
  ```c++
  "NONE"
  "FRONT_LEFT"
  "FRONT"
  "FRONT_RIGHT" 
  "FRONT_AND_FRONT_LEFT"
  "FRONT_AND_FRONT_RIGHT"
  "FRONT_ALL"
  "IMPOSSIBLE"
  ```

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init(); 
  } 

  void loop() {
    _enemy.update();  
    Serial.print("Enemy on : ");
    Serial.println(_enemy.pos_str());
    delay(50);
  }
  ```  
  
  <br>

  ### range_str()
  Return the range of enemy for monitor purpose. 
  
  **Syntax:**
  ```c++
  const char *enemy_detector.range_str();
  ```

  **Parameters:**
  None

  **Returns:** 
  ```c++
  "NONE"
  "CLOSE"
  "MID"
  "FAR"
  ```

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init(); 
  } 

  void loop() {
    _enemy.update();  
    Serial.print("Enemy distance : ");
    Serial.println(_enemy.range_str());
    delay(50);
  }
  ```  
  
  <br>

  ### setDetectThreshold(threshold)
  Set the maximum distance to consider a detected object as an enemy (in mm). The distance more than this threshold will be ignore. 
  
  **Syntax:**
  ```c++
  void enemy_detector.setDetectThreshold(int16_t threshold);
  ```

  **Parameters:**
  - ***threshold*** - The maximum distance to consider a detected object as an enemy (in mm). (Default : 600)

  **Returns:** 
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init(); 
    _enemy.setDetectThreshold(600);
  }  
  ```  
  
  <br>

  ### setInvalidRange(threshold)
  Set the return value if the enemy not valid.  
  
  **Syntax:**
  ```c++
  void enemy_detector.setInvalidRange(int16_t threshold);
  ```

  **Parameters:**
  - ***threshold*** - The value that will be returned when enemy not found (Default : 1000)

  **Returns:** 
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init(); 
    _enemy.setInvalidRange(1000);
  }  
  ```  
  
  <br>

  ### setDetectThreshold(threshold)
  Set the maximum distance to consider a detected object as an enemy (in mm). The distance more than this threshold will be ignore. 
  
  **Syntax:**
  ```c++
  void enemy_detector.setDetectThreshold(int16_t threshold);
  ```

  **Parameters:**
  - ***threshold*** - The maximum distance to consider a detected object as an enemy (in mm). (Default : 600)

  **Returns:** 
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init(); 
    _enemy.setDetectThreshold(600);
  }  
  ```  
  
  <br>

  ### setRangeClose(threshold)
  Set the range at which an object is considered to be at a close distance.
  
  **Syntax:**
  ```c++
  void enemy_detector.setRangeClose(int16_t threshold);
  ```

  **Parameters:**
  - ***threshold*** - The distance less than this value will be considered as close distance. (default : 100)

  **Returns:** 
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init(); 
    _enemy.setRangeClose(100);
  }  
  ```  
  
  <br>

  ### setRangeMid(threshold)
  Set the range at which an object is considered to be at a medium distance.
  
  **Syntax:**
  ```c++
  void enemy_detector.setRangeMid(int16_t threshold);
  ```

  **Parameters:**
  - ***threshold*** - The distance less than this value will be considered as medium distance. (default : 200)

  **Returns:** 
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init(); 
    _enemy.setRangeMid(200);
  }  
  ```  
  
  <br>

  ### setRangeFar(threshold)
  Set the range at which an object is considered to be at a medium distance.
  
  **Syntax:**
  ```c++
  void enemy_detector.setRangeFar(int16_t threshold);
  ```

  **Parameters:**
  - ***threshold*** - The distance less than this value will be considered as far distance. (default : 300)

  **Returns:** 
  None

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init(); 
    _enemy.setRangeFar(300);
  }  
  ```  
  
  <br>

  ### detected()
  Check whether an enemy has been detected in any direction.
  
  **Syntax:**
  ```c++
  bool enemy_detector.detected();
  ```

  **Parameters:**
  None

  **Returns:** 
  `True` for enemy found
	`False` for enemy not found

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init();  
  }  

	void loop() {
		_enemy.update();
		Serial.print("Enemy found = ");
		Serial.println(_enemy.detected());
	}
  ```  
  
  <br>

  ### at_left()
  Check if enemy on left side
  
  **Syntax:**
  ```c++
  bool enemy_detector.at_left();
  ```

  **Parameters:**
  None

  **Returns:** 
  `True` for enemy found on left side
  `False` for enemy not found on left side

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init();  
  }  

  void loop() {
    _enemy.update();
    Serial.print("Enemy found on left = ");
    Serial.println(_enemy.at_left());
  }
  ```  

  **Similar function**
  ```c++
  bool at_right()
  bool at_front()
  bool at_front_left()
  bool at_front_right()
  ```

  <br>

  ### enemy_close()
  Check if enemy is close (distance less than close threshold)
  
  **Syntax:**
  ```c++
  bool enemy_detector.enemy_close();
  ```

  **Parameters:**
  None

  **Returns:** 
  `True` when lastest enemy found located close distance 
  `False` when lastest enemy found not located close distance 

  **Example Code:**
  ```c++
  #include <Arduino.h>
  #include "ModuleMoreSumoV2.h"

  enemy_detector _enemy;
  void setup() {
    _enemy.init();  
  }  

  void loop() {
    _enemy.update();
    Serial.print("Enemy is close = ");
    Serial.println(_enemy.enemy_close());
  }
  ```  

  **Similar function**
  ```c++ 
  bool enemy_close();
  bool enemy_mid();
  bool enemy_far();
  ```
  
  <br>

</details>
 
 