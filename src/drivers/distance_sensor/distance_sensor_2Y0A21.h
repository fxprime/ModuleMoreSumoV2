#ifndef DISTANCE_SENSOR_2Y0A21
#define DISTANCE_SENSOR_2Y0A21

#include <Arduino.h> 
#include <Wire.h>


#include "distance_sensor.h" 
#include "../pinout.h"

namespace mdm_dist
{

    #define MINIMUM_DELAY_2Y0A21 10
    #define MAXIMUM_RANGE 1000


    class distance_sensor_2Y0A21 : public distance_sensor
    {

    public:

        struct dist_info_t
        { 
            gpio_t input;

            dist_info_t() {};
            dist_info_t(gpio_t a) : input(a) {};
        } ;

        distance_sensor_2Y0A21(/* args */);
        ~distance_sensor_2Y0A21();
 
        void init();
        void update(dist_ranges_t ranges);
        void get_range(dist_ranges_t ranges);
        void setFiltered(bool filtered);


    private: 
        inline bool readSingleSensor(dist_idx_t id)  __attribute__((always_inline));
            
        dist_info_t infos[IDX_COUNT];
        uint16_t _sensor[IDX_COUNT]; 
        dist_ranges_t _dist_mm; 
        unsigned long _last_update = 0;
        bool _filtered = false;
    };

}



#endif //DISTANCE_SENSOR_2Y0A21