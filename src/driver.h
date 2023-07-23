#ifndef DRIVER_H
#define DRIVER_H

#include <Arduino.h>
#include "drivers/motor_driver.h"

using namespace motor_driver_ns;
    
namespace mdmbot
{
    class driver
    {
    public:
        typedef bool (*CallbackFunction)(void); // define a callback function type

        typedef enum
        {
            DRIVE_SPEED_SLOW,
            DRIVE_SPEED_MEDIUM,
            DRIVE_SPEED_FAST,
            DRIVE_SPEED_FASTEST
        } drive_speed_t;

        typedef enum
        {
            DRIVE_FORWARD=0,
            DRIVE_REVERSE,
            DRIVE_ROTATE_LEFT,
            DRIVE_ROTATE_RIGHT,
            DRIVE_ARCTURN_SHARP_LEFT,
            DRIVE_ARCTURN_SHARP_RIGHT,
            DRIVE_ARCTURN_MID_LEFT,
            DRIVE_ARCTURN_MID_RIGHT,
            DRIVE_ARCTURN_WIDE_LEFT,
            DRIVE_ARCTURN_WIDE_RIGHT,
            DRIVE_COUNT
        } drive_t;



        struct duty_cycles_t
        {
            int8_t left;
            int8_t right;
            duty_cycles_t() {};
            duty_cycles_t(int8_t left, int8_t right)
             : left(left), right(right) {};
        };



        driver();
        ~driver();

        void init();
        void stop();
        void always_stop(bool always_stop);
        void set(drive_t drive, bool reverse, drive_speed_t drive_speed);
        void setMaxSpeed(uint8_t max_speed) { _motor_driver.set_max_speed(max_speed); };
        void setRobotStateFn(CallbackFunction callback) { _robotState = callback; }; 
        
        /**
         * @brief Drive the robot in a specific direction
         * 
         */
        void drive(drive_t drive, bool reverse, drive_speed_t drive_speed);
        void drive(drive_t drive, bool reverse);
        void drive(drive_t drive);
        void drive(drive_t drive, drive_speed_t drive_speed);
        void drive(int8_t left_dutycycle, int8_t right_dutycycle);


        /**
         * @brief Drive the robot in block base mode
         * 
         */
        bool wait(uint32_t ms);
        void stopForMs(uint32_t ms);
        void forward(drive_speed_t drive_speed = DRIVE_SPEED_MEDIUM);
        void forwardForMs(uint32_t ms, drive_speed_t drive_speed = DRIVE_SPEED_MEDIUM);
        void reverse(drive_speed_t drive_speed = DRIVE_SPEED_MEDIUM);
        void reverseForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void rotateLeft(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void rotateLeftForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void rotateRight(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void rotateRightForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnSharpLeft(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnSharpLeftForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnSharpRight(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnSharpRightForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnMidLeft(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnMidLeftForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnMidRight(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnMidRightForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnWideLeft(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnWideLeftForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnWideRight(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void arcTurnWideRightForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);



        void ReverseArcTurnSharpLeft(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void ReverseArcTurnSharpLeftForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void ReverseArcTurnSharpRight(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void ReverseArcTurnSharpRightForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void ReverseArcTurnMidLeft(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void ReverseArcTurnMidLeftForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void ReverseArcTurnMidRight(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void ReverseArcTurnMidRightForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void ReverseArcTurnWideLeft(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void ReverseArcTurnWideLeftForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void ReverseArcTurnWideRight(drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);
        void ReverseArcTurnWideRightForMs(uint32_t ms, drive_speed_t drive_speed  = DRIVE_SPEED_MEDIUM);





    private:
        duty_cycles_t    _drive_to_duty_cycle[DRIVE_COUNT][4];
        motor_driver     _motor_driver;
        bool             _always_stop; 
        CallbackFunction _robotState = nullptr;

        void negate(drive_t drive, bool reverse, int8_t *left, int8_t *right);

    };
    
 

};

#endif // DRIVER_H