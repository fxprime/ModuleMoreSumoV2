
#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>
#include "pinout.h"

namespace motor_driver_ns {
    
    class motor_driver
    {

    public:

        typedef enum
        {
            MOTORS_LEFT =0,
            MOTORS_RIGHT,
            MOTORS_COUNT
        } motors_t;

        struct motor_control_t
        {
            gpio_t cc_1;
            gpio_t cc_2;
            gpio_t pwm_out;
            motor_control_t() {};
            motor_control_t(gpio_t cc_1, gpio_t cc_2, gpio_t pwm_out) : cc_1(cc_1), cc_2(cc_2), pwm_out(pwm_out) {};
        } ;

        typedef enum
        {
            MOTOR_MODE_STOP,
            MOTOR_MODE_FORWARD,
            MOTOR_MODE_REVERSE
        } motor_mode_t;


    public:
        motor_driver(/* args */);
        ~motor_driver();

        void init(); 
        void set_max_speed(uint8_t maxSpeed) { _motor_maxSpeed = constrain(maxSpeed,0,255); };
        void motor_set_duty_cycle(motors_t motors, int16_t duty_cycle);
        void motor_stop_safely(void);

    private: 

        void motor_set_mode(motors_t motors, motor_mode_t mode);


        motor_control_t _motor_controls[MOTORS_COUNT];
        uint8_t _motor_maxSpeed = 100;
    
    };

        

};


#endif //MOTOR_DRIVER_H