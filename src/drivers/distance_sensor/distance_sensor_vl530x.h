#ifndef DISTANCE_SENSOR_VL530X_H
#define DISTANCE_SENSOR_VL530X_H

#include <Arduino.h>

#include <Wire.h>
#include "distance_sensor.h"
#include "../../externals/VL53L0X/VL53L0X.h"
#include "../pinout.h"

namespace mdm_dist
{

    #define MINIMUM_DELAY_VL53L0X 22
    #define MAXIMUM_RANGE 1000


    class distance_sensor_vl530x : public distance_sensor
    {

    public:

        struct dist_info_t
        {
            uint8_t addr;
            gpio_t xshut_gpio;

            dist_info_t() {};
            dist_info_t(uint8_t a, gpio_t b) :
            addr(a), xshut_gpio(b) {};
        } ;

        distance_sensor_vl530x(/* args */);
        ~distance_sensor_vl530x();
 
        void init();
        void update(dist_ranges_t ranges);
        void get_range(dist_ranges_t ranges);
        void setFiltered(bool filtered);


    private:
        void forceStandby(dist_info_t info);
        void initAddress(dist_idx_t id, dist_info_t info);
        inline bool readSingleSensor(dist_idx_t id)  __attribute__((always_inline));;
            
        VL53L0X _sensor[IDX_COUNT]; 
        dist_ranges_t _dist_mm; 
        float _dist_mm_filt[IDX_COUNT];
        unsigned long _last_update = 0;
        bool _filtered = false;
    };

}



#endif //DISTANCE_SENSOR_VL530X_H