#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H


#include <Arduino.h>
#include "pinout.h" 


 
namespace mdm_infrared_sensor {
    class infrared_sensor
    {

    public:

      typedef enum {
          INFRARED_SENSOR_FRONT_LEFT,
          INFRARED_SENSOR_FRONT_RIGHT,
          INFRARED_SENSOR_COUNT
      } infrared_idx_t;

      typedef int16_t ir_voltages_t[INFRARED_SENSOR_COUNT];




    public: 

      infrared_sensor(/* args */);
      ~infrared_sensor();

      void init();
      void update(ir_voltages_t voltages) __attribute__((always_inline));;
      void get(ir_voltages_t voltages) __attribute__((always_inline));;

    private:
             
      inline void emiter_on() __attribute__((always_inline));;
      inline void emiter_off() __attribute__((always_inline));;
      
      int16_t _maxValue;
      ir_voltages_t _voltages;
    };
    typedef infrared_sensor::ir_voltages_t ir_voltages;
    typedef infrared_sensor::infrared_idx_t infrared_idx;
}


#endif //INFRARED_SENSOR_H