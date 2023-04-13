#include "distance_sensor.h"
 
namespace mdm_dist
{
    distance_sensor::distance_sensor(/* args */)
    {
    }
    
    distance_sensor::~distance_sensor()
    {
    }
        
    const char* distance_sensor::sensor_str(dist_idx_t id)
    {
        static const char *sensor_str_map[] = {
            [IDX_FRONT_RIGHT] = "FRONT_RIGHT",
            [IDX_FRONT] = "FRONT",
            [IDX_FRONT_LEFT] = "LEFT",
            [IDX_COUNT] = "COUNT", 
        };
        return sensor_str_map[id];
    }

} // namespace mdm_dist
