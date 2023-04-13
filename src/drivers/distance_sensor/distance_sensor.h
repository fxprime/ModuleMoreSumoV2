#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include <Arduino.h>


namespace mdm_dist
{
    class distance_sensor
    {
    public:


        typedef enum
        {
            IDX_FRONT_RIGHT,
            IDX_FRONT, 
            IDX_FRONT_LEFT,
            IDX_COUNT
        } dist_idx_t;
            
        typedef uint16_t dist_ranges_t[IDX_COUNT];


        distance_sensor(/* args */);
        ~distance_sensor();

        const char *sensor_str(dist_idx_t id);
        virtual void init() = 0;
        virtual void update(dist_ranges_t ranges) = 0;
        virtual void get_range(dist_ranges_t ranges) = 0; 
        virtual void setFiltered(bool filtered) = 0;


    private:
        // dist_ranges_t _dist_mm; 
    };


    typedef distance_sensor::dist_ranges_t dist_ranges;
    typedef distance_sensor::dist_idx_t dist_idx; 
} // namespace mdm_dist
 

#endif 