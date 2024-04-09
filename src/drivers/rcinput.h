
#ifndef RC_INPUT
#define RC_INPUT

#include <Arduino.h>
#include "helper_def.h"
#include "pinout.h"
#include "ppm.h"
 
  
namespace mdmbot
{

#define RC_MIN_VALUE 950
#define RC_MAX_VALUE 2050
#define RC_MIDDLE_VALUE (RC_MIN_VALUE + RC_MAX_VALUE)/2

class RCInput
{

public:  
    typedef enum  {
        INVALID= 0,
        ROLL,
        PITCH,
        THROTTLE,
        YAW,
        CHANNEL_5,
        CHANNEL_6,
        CHANNEL_7,
        CHANNEL_8,
        CHANNEL_COUNT
    }channel_en;
public:
    RCInput(/* args */) {}
    ~RCInput() {}

    void init(){ 
        ppm.begin(4, false); 
    }
    inline void update() {
        m_rc[0] = 0;
        m_rc[1] = ppm.read_channel(1);
        m_rc[2] = ppm.read_channel(2);
        m_rc[3] = ppm.read_channel(3);
        m_rc[4] = ppm.read_channel(4);
        m_rc[5] = ppm.read_channel(5);
        m_rc[6] = ppm.read_channel(6);
        m_rc[7] = ppm.read_channel(7); 
        m_rc[8] = ppm.read_channel(8); 

        // Serial.print("RC: ");
        // for(int i=1; i<CHANNEL_COUNT; i++) {
        //     Serial.print(m_rc[i]); Serial.print(" ");
        // }
        // Serial.println();
    }
    inline bool valid() {
        return true;
    }
    inline void print() { }


    inline short applyDeadband(short v, short bandwidth) 
    {
        return (v > RC_MIDDLE_VALUE + bandwidth || v < RC_MIDDLE_VALUE - bandwidth) ? v : RC_MIDDLE_VALUE;
    }
 
    inline short applyMap(short x, short in_min, short in_max, short out_min, short out_max) {
        return (x - in_min) * (float)(out_max - out_min) / (in_max - in_min) + out_min;
    } 

    inline short clamp(short x, short min, short max) {
        return x < min ? min : (x > max ? max : x);
    }
    

    
    inline short get_value(channel_en channel) { return m_rc[channel]; }
    inline bool get_value_as_bool(channel_en channel, short cutoff = RC_MIDDLE_VALUE) { return m_rc[channel] > cutoff;};
    inline short get_value_as_percentage(channel_en channel, short min = RC_MIN_VALUE, short max=RC_MAX_VALUE, short deadband = 50) { 
        short value = m_rc[channel];
        value = applyDeadband(value, deadband);
        return applyMap(value, min, max, -100, 100); 
    } 




    inline RCInput* channel(channel_en channel) { 
        m_currentChannel = channel; 
        m_currentValue = m_rc[m_currentChannel];
        m_currentMin = RC_MIN_VALUE;
        m_currentMax = RC_MAX_VALUE;
        return this; 
    }
    inline RCInput* deadband(short bandwidth) { 
        m_currentValue = applyDeadband(m_currentValue, bandwidth); 
        return this; 
    }
    inline RCInput* map(short out_min, short out_max) { 
        m_currentValue = applyMap(m_currentValue, m_currentMin, m_currentMax, out_min, out_max); 
        m_currentMin = out_min;
        m_currentMax = out_max;
        return this; 
    }
    inline RCInput* clamp(short min, short max) { 
        m_currentValue = clamp(m_currentValue, min, max);
        m_currentMin=min; 
        m_currentMax=max; 
        return this; 
    }
    inline RCInput* twoSidePercentage() { 
        m_currentValue = applyMap(m_currentValue, m_currentMin, m_currentMax, -100, 100);  
        m_currentMin = -100;
        m_currentMax = 100;
        return this; 
    }
    inline RCInput* percentage() { 
        m_currentValue = applyMap(m_currentValue, m_currentMin, m_currentMax, 0, 100); 
        m_currentMin = 0;
        m_currentMax = 100;
        return this; 
    }
    inline RCInput* onoff() { 
        m_currentValue = m_currentValue > (m_currentMax - m_currentMin)*0.5; 
        return this; 
    }
    inline short  get() { 
        return m_currentValue; 
    }

private:  
    short m_rc[CHANNEL_COUNT];
    short m_currentValue;
    short m_currentChannel;
    short m_currentMin = RC_MIN_VALUE;
    short m_currentMax = RC_MAX_VALUE;
}; 

};

#endif //RC_INPUT