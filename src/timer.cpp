#include "timer.h" 

void timer_start(timer_t *timer) { *timer = millis(); }

uint32_t timer_ms_elapsed(const timer_t *timer)
{
    if (*timer) {
        return millis() - *timer;
    } else {
        return 0;
    }
}