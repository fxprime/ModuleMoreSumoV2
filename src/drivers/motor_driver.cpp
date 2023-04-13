

#include "motor_driver.h"


namespace motor_driver_ns {

    motor_driver::motor_driver(/* args */)
    {
        _motor_controls[MOTORS_LEFT] = motor_control_t(GPIO_MOTORS_LEFT_CC_1, GPIO_MOTORS_LEFT_CC_2, GPIO_MOTORS_LEFT_PWM);
        _motor_controls[MOTORS_RIGHT] = motor_control_t(GPIO_MOTORS_RIGHT_CC_1, GPIO_MOTORS_RIGHT_CC_2, GPIO_MOTORS_RIGHT_PWM);
    }

    motor_driver::~motor_driver()
    {
    }

    void motor_driver::init()
    {  
        for (int i = 0; i < MOTORS_COUNT; i++)
        {
            pinMode(_motor_controls[i].cc_1, OUTPUT);
            pinMode(_motor_controls[i].cc_2, OUTPUT);
            pinMode(_motor_controls[i].pwm_out, OUTPUT);
        }
        motor_stop_safely();
    }

    void motor_driver::motor_set_duty_cycle(motors_t motors, int16_t duty_cycle)
    {
        if (duty_cycle > 0)
        {
            motor_set_mode(motors, MOTOR_MODE_FORWARD);
        }
        else if (duty_cycle < 0)
        {
            motor_set_mode(motors, MOTOR_MODE_REVERSE);
        }
        else
        {
            motor_set_mode(motors, MOTOR_MODE_STOP);
        }
        analogWrite(_motor_controls[motors].pwm_out, (_motor_maxSpeed*abs(duty_cycle))/100);
    }

    void motor_driver::motor_stop_safely(void)
    {
        for (int i = 0; i < MOTORS_COUNT; i++)
        {
            digitalWrite(_motor_controls[i].cc_1, LOW);
            digitalWrite(_motor_controls[i].cc_2, LOW);
            analogWrite(_motor_controls[i].pwm_out, 0);
        }
    }

    void motor_driver::motor_set_mode(motors_t motors, motor_mode_t mode)
    {
        switch (mode)
        {
        case MOTOR_MODE_STOP:
            digitalWrite(_motor_controls[motors].cc_1, LOW);
            digitalWrite(_motor_controls[motors].cc_2, LOW);
            break;
        case MOTOR_MODE_FORWARD:
            digitalWrite(_motor_controls[motors].cc_1, HIGH);
            digitalWrite(_motor_controls[motors].cc_2, LOW);
            break;
        case MOTOR_MODE_REVERSE:
            digitalWrite(_motor_controls[motors].cc_1, LOW);
            digitalWrite(_motor_controls[motors].cc_2, HIGH);
            break;
        default:
            break;
        }
    }
 

}