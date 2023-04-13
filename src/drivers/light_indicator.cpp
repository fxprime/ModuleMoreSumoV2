#include "light_indicator.h"

namespace mdm_light_indicator
{

    light_indicator::light_indicator()
    {
        _indicator_type = INDICATOR_OFF;
    }

    light_indicator::~light_indicator()
    {
    }

    void light_indicator::init(int8_t pin)
    {
        _pin = pin;
        if(_pin == -1) return;
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, LOW);
        Serial.println("Light indicator initialized");
    }

    void light_indicator::set_indicator(indicator_type_t type)
    {
        if(_pin == -1) return;
        if(type == INDICATOR_COUNTDOWN && _indicator_type != INDICATOR_COUNTDOWN) {
            _countdown_start_time = millis();
        }
        _indicator_type = type;
    }

    void light_indicator::update()
    {
        if(_pin == -1) return;
        switch(_indicator_type)
        {
            case INDICATOR_OFF:
                digitalWrite(_pin, LOW);
                break;
            case INDICATOR_COUNTDOWN:{ 
                int period = 1000;
                if(millis() - _countdown_start_time < _countdowntime/4) {
                    period = 1000;
                }else if(millis() - _countdown_start_time < _countdowntime/2) {
                    period = 500;
                }else if(millis() - _countdown_start_time < _countdowntime*3/4) {
                    period = 250;
                }else {
                    period = 100;
                } 
                bool led = millis()%period < period/2;
                digitalWrite(_pin, led); 
                break;
            }
            case INDICATOR_READY: {
                //Boing plane blink pattern
                uint32_t period = 2000;
                bool led = millis()%period < 50 || (millis()%period > 100 && millis()%period < 150); 
                digitalWrite(_pin, led); 
                break;
            }
        }
    }

}