#ifndef ROBOT_UI_H
#define ROBOT_UI_H

#include <Arduino.h>
#include <INA219_WE.h>
#include "drivers/push_button.h"
#include "drivers/light_indicator.h"
#include "drivers/rcinput.h"
#include "drivers/powermeter.h"
 
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
            mode_0,
            mode_1,
            mode_2,
            mode_3,
            mode_4,
            mode_5,
            mode_6,
            mode_7,
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
        inline void update()__attribute__((always_inline));

        
        inline void updateState() __attribute__((always_inline));
        inline void updateMode()__attribute__((always_inline));
        inline void updateButton()__attribute__((always_inline));
        inline void updatePower()__attribute__((always_inline));
        inline void updateRCInput()__attribute__((always_inline));
        void setCountdown(uint16_t countdown);
        ui_mode_t getMode();
        const char* getModeStr();
        
        bool isRobotStartAuto()   { update(); return _state == ROBOT_STARTAUTO;   };
        bool isRobotStartManual() { update(); return _state == ROBOT_STARTMANUAL; };
        bool isRobotStop()        { update(); return _state == ROBOT_STOP;        };
        void countingDown();

        uint8_t getRawButton();
        uint16_t getRawMode();


        /* -------------------------------------------------------------------------- */
        /*                                   RCInput                                  */
        /* -------------------------------------------------------------------------- */
        inline short getRCThrottlePCT() __attribute__((always_inline)){ return _rcinput->channel(RCInput::channel_en::THROTTLE)->deadband(10)->map(-100, 100)->get(); };
        inline short getRCRollPCT() __attribute__((always_inline))    { return _rcinput->channel(RCInput::channel_en::ROLL)->deadband(10)->map(-100, 100)->get(); };
        inline short getRCPitchPCT() __attribute__((always_inline))   { return _rcinput->channel(RCInput::channel_en::PITCH)->deadband(10)->map(-100, 100)->get(); };
        inline short getRCYawPCT() __attribute__((always_inline))     { return _rcinput->channel(RCInput::channel_en::YAW)->deadband(10)->map(-100, 100)->get(); };
        inline short getRCRaw(int channel) __attribute__((always_inline)) { return _rcinput->channel((RCInput::channel_en)channel)->get(); };

        /* -------------------------------------------------------------------------- */
        /*                                 PowerMeter                                 */
        /* -------------------------------------------------------------------------- */
        inline uint8_t getBatteryPCT() { return _meter->getBatteryPercentage(); };
        inline float getBatteryVoltage() { return _meter->getBatteryVoltage(); };
        inline int16_t getBatteryCurrent() { return _meter->getBatteryCurrent(); };
        inline bool isBatteryLow() { return _meter->is_critical_low_voltage(); };
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

        RCInput *_rcinput;

        PowerMeter *_meter;

    };

    void robot_ui::update()
    {
        updateButton();
        updateRCInput();
        updateState();
        updateMode(); 
        updatePower();
        if(_indicator != nullptr) _indicator->update(); 
    };


    void robot_ui::updateButton()
    {
        _button->loop();
        //TODO : Add more complex button pattern if needed here.
    }

    void robot_ui::updateState()
    { 
        switch (_state)
        {
        case ROBOT_STOP:
            if (_button->isPressed())
            {
                _target_state = ROBOT_STARTAUTO;
                _state = ROBOT_COUNTDOWN;
            }
            break;
        case ROBOT_COUNTDOWN:
            if (_button->isPressed())
            {
                _target_state = ROBOT_STOP;
                _state = ROBOT_STOP;
            }
            break;
        case ROBOT_STARTAUTO:
            if (_button->isPressed())
            {
                _target_state = ROBOT_STOP;
                _state = ROBOT_STOP;
            }
            break;
        case ROBOT_STARTMANUAL:
            if (_button->isPressed())
            {
                _target_state = ROBOT_STOP;
                _state = ROBOT_STOP;
            }
            break;
        default:
            break;
        }

        if (_state == ROBOT_COUNTDOWN)
            countingDown();

        if (_last_state != _state)
        {
            Serial.print("Robot UI state changed from ");
            Serial.print(_last_state);
            Serial.print(" to ");
            Serial.println(_state);
            _last_state = _state;
        }
    }

    void robot_ui::updateMode()
    {

        static uint32_t lastCheck = 0;
        if (millis() - lastCheck < 300)
            return;
        lastCheck = millis();
        _mode = (ui_mode_t)getMode();
        if (_mode != _last_mode)
        {
            _last_mode = _mode;
            Serial.print("Mode changed to: ");
            Serial.println(mode_str(_mode));
        }
    }

    void robot_ui::updatePower() 
    {
        _meter->update();
    }

    void robot_ui::updateRCInput()
    {
        _rcinput->update();
    }


}


#endif