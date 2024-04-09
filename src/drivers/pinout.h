#ifndef PINOUT
#define PINOUT

#include <Arduino.h>

/**
 * @brief ONLY FIRST VERSION UNDEFINED THIS MACRO 
 */
// #define OLD_PINOUT 

#ifdef OLD_PINOUT

    typedef enum
    { 

        GPIO_MOTORS_LEFT_CC_1        = 16,
        GPIO_MOTORS_LEFT_CC_2        = 10,
        GPIO_MOTORS_LEFT_PWM         = 6,

        GPIO_RC_PPM                  = 4,

        GPIO_MOTORS_RIGHT_PWM        = 5,
        GPIO_MOTORS_RIGHT_CC_1       = 15,
        GPIO_MOTORS_RIGHT_CC_2       = 14,

        GPIO_2Y0A21_FRONT_LEFT       = A2,
        GPIO_2Y0A21_FRONT            = A0,
        GPIO_2Y0A21_FRONT_RIGHT      = A1, 


        GPIO_LINE_DETECT_IR          = -1,

        GPIO_SW_ALL                  = 7,

        GPIO_SW_MODE                 = -1,

        GPIO_LIGHT_INDICATOR         = -1,
        
        GPIO_LINE_DETECT_FRONT_LEFT  = A3,
        GPIO_LINE_DETECT_FRONT_RIGHT = A6, 



        //Unused
        GPIO_XSHUT_FRONT_RIGHT       = -1,
        GPIO_XSHUT_FRONT             = -1,
        GPIO_XSHUT_FRONT_LEFT        = -1, 
    } gpio_t;
#else

    typedef enum
    { 

        GPIO_MOTORS_LEFT_CC_1        = 3,
        GPIO_MOTORS_LEFT_CC_2        = 2,
        GPIO_MOTORS_LEFT_PWM         = 5,

        GPIO_RC_PPM                  = 4,

        GPIO_MOTORS_RIGHT_PWM        = 6,
        GPIO_MOTORS_RIGHT_CC_1       = 7,
        GPIO_MOTORS_RIGHT_CC_2       = 8,

        GPIO_XSHUT_FRONT_RIGHT       = 9,
        GPIO_XSHUT_FRONT             = 10,
        GPIO_XSHUT_FRONT_LEFT        = 11, 

        GPIO_SW_ALL                  = A0,
        
        GPIO_SW_MODE                 = A3,

        GPIO_LINE_DETECT_FRONT_LEFT  = A1,
        GPIO_LINE_DETECT_FRONT_RIGHT = A2, 
        GPIO_LINE_DETECT_IR          = 12,

        GPIO_LIGHT_INDICATOR         = 13,

        //Unused
        GPIO_2Y0A21_FRONT_LEFT       = -1,
        GPIO_2Y0A21_FRONT            = -1,
        GPIO_2Y0A21_FRONT_RIGHT      = -1, 
    } gpio_t;

#endif




#endif //PINOUT