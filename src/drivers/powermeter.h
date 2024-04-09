
#ifndef POWERMETER
#define POWERMETER

#include <Arduino.h>
#include <INA219_WE.h>
#include "pinout.h"
 
class PowerMeter
{

public: 

    typedef struct {
        float m_current;
        float m_voltage;
        float m_power;
        bool is_overflow;

        inline bool is_valid() {
            return !is_overflow;
        }

        inline void print() {
            Serial.print("Current: "); Serial.print(m_current); Serial.print(" mA\t");
            Serial.print("Voltage: "); Serial.print(m_voltage); Serial.print(" V\t");
            Serial.print("Power: "); Serial.print(m_power); Serial.print(" mW\t");
            Serial.print("Overflow: "); Serial.println(is_overflow);
        }

        inline void update(INA219_WE &meter) {
            m_current = m_current*0.99 + 0.01*meter.getCurrent_mA();
            float loadV = meter.getBusVoltage_V() + (meter.getShuntVoltage_mV() *0.001);
            m_voltage = m_voltage*0.99 + 0.01*loadV;
            m_power = m_power*0.99 + 0.01*meter.getBusPower();
            is_overflow = meter.getOverflow();
        }

        inline bool is_critical_low_voltage() {
            if(!is_valid()) return false;
            if(m_current > 500) return m_voltage < 7.0;
            return (m_voltage < 7.2);
        }
 
    }meter_t;


public:
    PowerMeter(/* args */) {};
    ~PowerMeter() {};

    void init() {
        if(!m_ina219.init()) {
            Serial.println("INA219 chip not found, ignored.");
            return;
        }
        m_inited = true;
        m_meter.m_voltage = 7.8;
        m_meter.m_current = 0;
        m_meter.m_power = 0;
        m_meter.is_overflow = false; 
        Serial.println("INA219 chip found.");
    }
    inline void update() {
        if(!m_inited) return;
        if(!m_ina219.getConversionReady()) return;
        m_meter.update(m_ina219);
        // m_meter.print(); 
    }
    inline bool valid() {
        bool valid = m_meter.is_valid() || m_inited;
        return valid;
    }
    inline void print() { m_meter.print(); }
    inline bool is_critical_low_voltage() { return m_meter.is_critical_low_voltage(); }
    inline uint8_t getBatteryPercentage() { return (uint8_t)( 100*(m_meter.m_voltage - 7.0)/(8.4-7.0) ); }
    inline float getBatteryVoltage() { return m_meter.m_voltage; }
    inline int16_t getBatteryCurrent() { return (int16_t)m_meter.m_current; }


private: 
    const uint8_t INA219_ADDRESS = 0x40;
    INA219_WE       m_ina219 = INA219_WE(INA219_ADDRESS );
    meter_t         m_meter;
    bool m_inited = false;

}; 

#endif //POWERMETER