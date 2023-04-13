#ifndef LIGHT_INDICATOR_H
#define LIGHT_INDICATOR_H

#include <Arduino.h>
#include "pinout.h"

namespace mdm_light_indicator {

class light_indicator
{
public:

    typedef enum {
        INDICATOR_OFF,
        INDICATOR_COUNTDOWN,
        INDICATOR_READY,
    }indicator_type_t;

    light_indicator();
    ~light_indicator();

    void init(int8_t pin = GPIO_LIGHT_INDICATOR);
    void set_indicator(indicator_type_t type);
    void set_countdown_time(uint32_t time) { _countdowntime = time; };
    void update();

private:    
    indicator_type_t _indicator_type;
    int8_t _pin = -1;
    uint32_t _countdowntime = 5000;
    uint32_t _countdown_start_time = 0;
};
}
#endif