
#include "distance_sensor_2Y0A21.h"

namespace mdm_dist {

    distance_sensor_2Y0A21::distance_sensor_2Y0A21(/* args */)
    {
        infos[IDX_FRONT].input = GPIO_2Y0A21_FRONT;
        infos[IDX_FRONT_RIGHT].input = GPIO_2Y0A21_FRONT_RIGHT;
        infos[IDX_FRONT_LEFT].input = GPIO_2Y0A21_FRONT_LEFT;

    }

    distance_sensor_2Y0A21::~distance_sensor_2Y0A21()
    {

    }
 
    void distance_sensor_2Y0A21::init() {  
    }

    void distance_sensor_2Y0A21::setFiltered(bool filtered) {
        _filtered = filtered;
    }



    inline bool distance_sensor_2Y0A21::readSingleSensor(dist_idx_t id) {
        
        // uint16_t range = 1023 - analogRead(infos[id].input);
        uint16_t range = 136000 / (analogRead(infos[id].input) - 20);
   
        if(range > MAXIMUM_RANGE) 
        range = MAXIMUM_RANGE;

        _dist_mm[id] = range; 
        return true;
    }

    

    void distance_sensor_2Y0A21::update(dist_ranges_t ranges ) {   
    
        // auto t_last = micros();
        bool success = true;
        success &= readSingleSensor(IDX_FRONT);
        success &= readSingleSensor(IDX_FRONT_RIGHT);
        success &= readSingleSensor(IDX_FRONT_LEFT);



        if(success) {
            for (int i = 0; i < IDX_COUNT; i++)
            {
            ranges[i] = _dist_mm[i];
            }
        }else{ 
            for (int i = 0; i < IDX_COUNT; i++)
            {
            ranges[i] = MAXIMUM_RANGE;
            }
        } 
 
    }

    void distance_sensor_2Y0A21::get_range(dist_ranges_t ranges) { 
        for (int i = 0; i < IDX_COUNT; i++)
        {
            ranges[i] = _dist_mm[i];
        }
    }

} // namespace mdm_dist
