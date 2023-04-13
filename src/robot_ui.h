#ifndef ROBOT_UI_H
#define ROBOT_UI_H

#include <Arduino.h>
#include "drivers/push_button.h"
#include "drivers/light_indicator.h"
 
using namespace mdm_light_indicator;

namespace mdmbot {
    class robot_ui
    {
    public:
        typedef enum {
            ROBOT_STOP,
            ROBOT_COUNTDOWN,
            ROBOT_STARTAUTO,
            ROBOT_STARTMANUAL,
        }ui_state_t;

        typedef enum {
            MODE_0,
            MODE_1,
            MODE_2,
            MODE_3,
            MODE_4,
            MODE_5,
            MODE_6,
            MODE_7,
            MODE_COUNT
        }ui_mode_t;

        typedef enum {
            BUTTON_NONE,
            BUTTON_PRESSED,
            BUTTON_RELEASED,
            // BUTTON_LONGPRESSED
        }ui_raw_button_t;

        robot_ui();
        ~robot_ui();
        const char* str();
        const char* mode_str(ui_mode_t& mode);
        void init(uint16_t countdown=5000);
        void update();
        void updateState();
        void updateMode();
        void updateButton();
        void setCountdown(uint16_t countdown);
        uint8_t getMode();
        const char* getModeStr();
        
        bool isRobotStartAuto()   { update(); return _state == ROBOT_STARTAUTO;   };
        bool isRobotStartManual() { update(); return _state == ROBOT_STARTMANUAL; };
        bool isRobotStop()        { update(); return _state == ROBOT_STOP;        };
        void countingDown();

        uint8_t getRawButton();
        uint16_t getRawMode();


    private:

        mdm_pushbutton::ezButton *_button;
        mdm_light_indicator::light_indicator *_indicator;
        ui_state_t _state;
        ui_state_t _last_state;
        ui_state_t _target_state;
        ui_mode_t _mode;
        ui_mode_t _last_mode;

        unsigned long _COUNTDOWNTIME = 5000;
        unsigned long _countdown_start_time = 0;


    };
}


#endif