#include <Arduino.h>
#include "driver.h"

namespace mdmbot
{
    driver::driver() :
    _always_stop(false)
    {
    }

    driver::~driver()
    {
    }

    void driver::init()
    {
        _drive_to_duty_cycle[DRIVE_FORWARD][DRIVE_SPEED_SLOW]               = duty_cycles_t(25,   25);
        _drive_to_duty_cycle[DRIVE_FORWARD][DRIVE_SPEED_MEDIUM]             = duty_cycles_t(45,   45);
        _drive_to_duty_cycle[DRIVE_FORWARD][DRIVE_SPEED_FAST]               = duty_cycles_t(55,   55);
        _drive_to_duty_cycle[DRIVE_FORWARD][DRIVE_SPEED_FASTEST]            = duty_cycles_t(100,  100);

        _drive_to_duty_cycle[DRIVE_ROTATE_LEFT][DRIVE_SPEED_SLOW]           = duty_cycles_t(-25,  25);
        _drive_to_duty_cycle[DRIVE_ROTATE_LEFT][DRIVE_SPEED_MEDIUM]         = duty_cycles_t(-50,  50);
        _drive_to_duty_cycle[DRIVE_ROTATE_LEFT][DRIVE_SPEED_FAST]           = duty_cycles_t(-60,  60);
        _drive_to_duty_cycle[DRIVE_ROTATE_LEFT][DRIVE_SPEED_FASTEST]        = duty_cycles_t(-100, 100);

        _drive_to_duty_cycle[DRIVE_ARCTURN_SHARP_LEFT][DRIVE_SPEED_SLOW]    = duty_cycles_t(-10,  25);
        _drive_to_duty_cycle[DRIVE_ARCTURN_SHARP_LEFT][DRIVE_SPEED_MEDIUM]  = duty_cycles_t(-10,  50);
        _drive_to_duty_cycle[DRIVE_ARCTURN_SHARP_LEFT][DRIVE_SPEED_FAST]    = duty_cycles_t(-25,  75);
        _drive_to_duty_cycle[DRIVE_ARCTURN_SHARP_LEFT][DRIVE_SPEED_FASTEST] = duty_cycles_t(-20,  100);

        _drive_to_duty_cycle[DRIVE_ARCTURN_MID_LEFT][DRIVE_SPEED_SLOW]      = duty_cycles_t(15,   30);
        _drive_to_duty_cycle[DRIVE_ARCTURN_MID_LEFT][DRIVE_SPEED_MEDIUM]    = duty_cycles_t(25,   50);
        _drive_to_duty_cycle[DRIVE_ARCTURN_MID_LEFT][DRIVE_SPEED_FAST]      = duty_cycles_t(35,   70);
        _drive_to_duty_cycle[DRIVE_ARCTURN_MID_LEFT][DRIVE_SPEED_FASTEST]   = duty_cycles_t(50,   100);

        _drive_to_duty_cycle[DRIVE_ARCTURN_WIDE_LEFT][DRIVE_SPEED_SLOW]     = duty_cycles_t(25,   50);
        _drive_to_duty_cycle[DRIVE_ARCTURN_WIDE_LEFT][DRIVE_SPEED_MEDIUM]   = duty_cycles_t(40,   50);
        _drive_to_duty_cycle[DRIVE_ARCTURN_WIDE_LEFT][DRIVE_SPEED_FAST]     = duty_cycles_t(60,   70);
        _drive_to_duty_cycle[DRIVE_ARCTURN_WIDE_LEFT][DRIVE_SPEED_FASTEST]  = duty_cycles_t(85,   100);

        _motor_driver.init();
    }

    void driver::stop()
    {
        _motor_driver.motor_stop_safely();
    }

    void driver::always_stop(bool always_stop)
    {
        _always_stop = always_stop;
    }

    void driver::set(drive_t drive, bool reverse, drive_speed_t drive_speed)
    { 
        if(_always_stop) { stop(); return;  }
        
        int8_t left = _drive_to_duty_cycle[drive - (drive % 2)][drive_speed].left;
        int8_t right = _drive_to_duty_cycle[drive - (drive % 2)][drive_speed].right;
        negate(drive, reverse, &left, &right); 

        _motor_driver.motor_set_duty_cycle(motor_driver::MOTORS_LEFT, left);
        _motor_driver.motor_set_duty_cycle(motor_driver::MOTORS_RIGHT, right);
    }

    void driver::negate(drive_t drive, bool reverse, int8_t *left, int8_t *right)
    {
        switch (drive) {
        case DRIVE_REVERSE:
        case DRIVE_ROTATE_RIGHT:
            *left = -*left;
            *right = -*right;
            break;
        case DRIVE_ARCTURN_SHARP_RIGHT:
        case DRIVE_ARCTURN_MID_RIGHT:
        case DRIVE_ARCTURN_WIDE_RIGHT:
        {
            const int8_t left_tmp = *left;
            *left = *right;
            *right = left_tmp;
            break;
        }
        default:
            break;
        }
        if (reverse) {
            *left = -*left;
            *right = -*right;
        }
    }


   
   /* -------------------------------------------------------------------------- */
   /*                         USEFUL HIGH-LEVEL FUNCTIONS                        */
   /* -------------------------------------------------------------------------- */
    bool driver::wait(uint32_t ms)
    {
        uint32_t start = millis();
        while (millis() - start < ms) {
            delayMicroseconds(100);

            static uint32_t last = 0;
            if(millis() - last > 50) {
                last = millis();
                if(_robotState==nullptr)        continue;
                Serial.println(_robotState());
                if(!_robotState())              return false;
            }
        }
        return true;
    }

    void driver::drive(drive_t drive, bool reverse, drive_speed_t drive_speed)
    {
        set(drive, reverse, drive_speed);
    }
 
    void driver::drive(drive_t drive, bool reverse)
    {
        set(drive, reverse, DRIVE_SPEED_MEDIUM);
    }

    void driver::drive(drive_t drive)
    {
        set(drive, false, DRIVE_SPEED_MEDIUM);
    }

    void driver::drive(drive_t drive, drive_speed_t drive_speed)
    {
        set(drive, false, drive_speed);
    }

    void driver::drive(int8_t left_dutycycle, int8_t right_dutycycle) {
        if(_always_stop) { stop(); return;  }
        _motor_driver.motor_set_duty_cycle(motor_driver::MOTORS_LEFT, left_dutycycle);
        _motor_driver.motor_set_duty_cycle(motor_driver::MOTORS_RIGHT, right_dutycycle);
    }
 
    void driver::forward(drive_speed_t drive_speed)
    {
        set(DRIVE_FORWARD, false, drive_speed);
    }

    void driver::forwardForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_FORWARD, false, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::stopForMs(uint32_t ms)
    {
        _motor_driver.motor_stop_safely();
        if(!wait(ms)) return;
    }

    void driver::reverse(drive_speed_t drive_speed)
    {
        set(DRIVE_REVERSE, false, drive_speed);
    } 

    void driver::reverseForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_REVERSE, false, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::rotateLeft(drive_speed_t drive_speed)
    {
        set(DRIVE_ROTATE_LEFT, false, drive_speed);
    }

    void driver::rotateLeftForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ROTATE_LEFT, false, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::rotateRight(drive_speed_t drive_speed)
    {
        set(DRIVE_ROTATE_RIGHT, false, drive_speed);
    }

    void driver::rotateRightForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ROTATE_RIGHT, false, drive_speed);
        if(!wait(ms)) return;
        stop();
    } 

    void driver::arcTurnSharpLeft(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_SHARP_LEFT, false, drive_speed);
    }

    void driver::arcTurnSharpLeftForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_SHARP_LEFT, false, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::arcTurnSharpRight(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_SHARP_RIGHT, false, drive_speed);
    }

    void driver::arcTurnSharpRightForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_SHARP_RIGHT, false, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::arcTurnMidLeft(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_MID_LEFT, false, drive_speed);
    }

    void driver::arcTurnMidLeftForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_MID_LEFT, false, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::arcTurnMidRight(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_MID_RIGHT, false, drive_speed);
    }

    void driver::arcTurnMidRightForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_MID_RIGHT, false, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::arcTurnWideLeft(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_WIDE_LEFT, false, drive_speed);
    }

    void driver::arcTurnWideLeftForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_WIDE_LEFT, false, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::arcTurnWideRight(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_WIDE_RIGHT, false, drive_speed);
    }

    void driver::arcTurnWideRightForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_WIDE_RIGHT, false, drive_speed);
        if(!wait(ms)) return;
        stop();
    }




    void driver::ReverseArcTurnSharpLeft(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_SHARP_LEFT, true, drive_speed);
    }

    void driver::ReverseArcTurnSharpLeftForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_SHARP_LEFT, true, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::ReverseArcTurnSharpRight(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_SHARP_RIGHT, true, drive_speed);
    }

    void driver::ReverseArcTurnSharpRightForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_SHARP_RIGHT, true, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::ReverseArcTurnMidLeft(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_MID_LEFT, true, drive_speed);
    }

    void driver::ReverseArcTurnMidLeftForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_MID_LEFT, true, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::ReverseArcTurnMidRight(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_MID_RIGHT, true, drive_speed);
    }

    void driver::ReverseArcTurnMidRightForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_MID_RIGHT, true, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::ReverseArcTurnWideLeft(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_WIDE_LEFT, true, drive_speed);
    }

    void driver::ReverseArcTurnWideLeftForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_WIDE_LEFT, true, drive_speed);
        if(!wait(ms)) return;
        stop();
    }

    void driver::ReverseArcTurnWideRight(drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_WIDE_RIGHT, true, drive_speed);
    }

    void driver::ReverseArcTurnWideRightForMs(uint32_t ms, drive_speed_t drive_speed)
    {
        set(DRIVE_ARCTURN_WIDE_RIGHT, true, drive_speed);
        if(!wait(ms)) return;
        stop();
    } 

    

}