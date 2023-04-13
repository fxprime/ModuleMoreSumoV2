#include "robot_ui.h"

namespace mdmbot
{

    robot_ui::robot_ui()
    {
        _state = ROBOT_STOP;
        _last_state = ROBOT_STOP;
        _target_state = ROBOT_STOP;
    }

    robot_ui::~robot_ui()
    {
        delete _button;
        delete _indicator;
    }

    const char *robot_ui::str()
    {
        static const char *state_str_map[] = {
            [ROBOT_STOP] = "STOP",
            [ROBOT_COUNTDOWN] = "COUNTDOWN",
            [ROBOT_STARTAUTO] = "STARTAUTO",
            [ROBOT_STARTMANUAL] = "STARTMANUAL",
        };
        return state_str_map[_state];
    }

    const char *robot_ui::mode_str(ui_mode_t &mode)
    {
        static const char *mode_str_map[] = {
            [MODE_0] = "MODE_0",
            [MODE_1] = "MODE_1",
            [MODE_2] = "MODE_2",
            [MODE_3] = "MODE_3",
            [MODE_4] = "MODE_4",
            [MODE_5] = "MODE_5",
            [MODE_6] = "MODE_6",
            [MODE_7] = "MODE_7"
        };
        return mode_str_map[mode];
    }

    void robot_ui::init(uint16_t countdown)
    {
        _button = new mdm_pushbutton::ezButton();
        if(GPIO_LIGHT_INDICATOR != -1) _indicator = new mdm_light_indicator::light_indicator();
        _COUNTDOWNTIME = countdown;
        if(_indicator != nullptr) {
            _indicator->init();
            _indicator->set_countdown_time(countdown);
            _indicator->set_indicator(light_indicator::INDICATOR_READY);
        }
        _mode = getMode();
        _last_mode = _mode;

        pinMode(13, OUTPUT);

        Serial.println("Robot UI initialized");
    }

    uint8_t robot_ui::getMode()
    {

        uint16_t val = analogRead(GPIO_SW_MODE);
        if (val < 200)
            return MODE_0;
        else if (val < 300)
            return MODE_1;
        else if (val < 400)
            return MODE_2;
        else if (val < 500)
            return MODE_3;
        else if (val < 550)
            return MODE_4;
        else if (val < 600)
            return MODE_5;
        else if (val < 625)
            return MODE_6;
        else
            return MODE_7;
    }
    
    void robot_ui::update()
    {
        updateButton();
        updateState();
        updateMode(); 
        if(_indicator != nullptr) _indicator->update(); 
    }

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



    void robot_ui::countingDown()
    {
        if (_last_state == ROBOT_STOP)
        {
            _countdown_start_time = millis();
            Serial.println("Start Robot UI countdown");
            if(_indicator != nullptr) _indicator->set_indicator(light_indicator::INDICATOR_COUNTDOWN);
        }

        unsigned long current_time = millis();
        if (current_time - _countdown_start_time > _COUNTDOWNTIME)
        {
            _last_state = _state;
            _state = _target_state; 
            Serial.println(" Robot UI countdown finished");
            if(_indicator != nullptr) _indicator->set_indicator(light_indicator::INDICATOR_READY);
        }
    }

    void robot_ui::setCountdown(uint16_t countdown)
    {
        _COUNTDOWNTIME = countdown;
        if(_indicator != nullptr) _indicator->set_countdown_time(countdown);
    }


    uint8_t robot_ui::getRawButton() {
        if(_button->isPressed()) return (uint8_t)BUTTON_PRESSED;
        else if(_button->isReleased())  return (uint8_t)BUTTON_RELEASED;
        else return (uint8_t)BUTTON_NONE;
    }

    uint16_t robot_ui::getRawMode() {
        return analogRead(GPIO_SW_MODE);
    }

    const char* robot_ui::getModeStr()
    {
        return mode_str(_mode);
    }
}
