/**
 * @file distance_sensor_vl530x.cpp
 * @author Thanabadee Bulunseechart (modulemore@gmail.com)
 * @brief Class of the multiple distance sensors VL530X handler 
 * @version 1.0
 * @date 2023-04-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "distance_sensor_vl530x.h"

namespace mdm_dist {

    distance_sensor_vl530x::distance_sensor_vl530x(/* args */)
    {

    }

    distance_sensor_vl530x::~distance_sensor_vl530x()
    {

    }


    void distance_sensor_vl530x::forceStandby(dist_info_t info) { 
        pinMode(info.xshut_gpio, OUTPUT);
        digitalWrite(info.xshut_gpio, LOW);
    }

    void distance_sensor_vl530x::initAddress(dist_idx_t id, dist_info_t info) {

        digitalWrite(info.xshut_gpio, HIGH); 
        _sensor[id].init(true); 
        _sensor[id].setAddress((uint8_t)info.addr);
        _sensor[id].setMeasurementTimingBudget(20000); 
        
        Serial.print("sensor ");
        Serial.print(sensor_str(id));
        Serial.println(" addresses set"); 
    }

    void distance_sensor_vl530x::init() { 

        static dist_info_t infos[IDX_COUNT];
        infos[IDX_FRONT] = dist_info_t(0x01, GPIO_XSHUT_FRONT); 
        infos[IDX_FRONT_RIGHT] = dist_info_t(0x02, GPIO_XSHUT_FRONT_RIGHT); 
        infos[IDX_FRONT_LEFT] = dist_info_t(0x03, GPIO_XSHUT_FRONT_LEFT); 
         
        for(int i=0;i<IDX_COUNT;i++) 
            forceStandby(infos[i]);
         
        delay(100); 
        Wire.begin();
        delay(10); 
        
        for(int i=0;i<IDX_COUNT;i++) 
            initAddress((dist_idx_t)i, infos[i]); 
        
        for(int i=0;i<IDX_COUNT;i++) 
            _sensor[i].startContinuous(); 
        
    }

    void distance_sensor_vl530x::setFiltered(bool filtered) {
        _filtered = filtered;
    }
 
    inline bool distance_sensor_vl530x::readSingleSensor(dist_idx_t id) {
        uint16_t range = _sensor[id].readRangeContinuousMillimeters(); //65535 is timeout
        if(range == 65535) return false; 
        if(range > MAXIMUM_RANGE) 
        range = MAXIMUM_RANGE;

        _dist_mm[id] = range; 
        return true;
    }

    

    void distance_sensor_vl530x::update(dist_ranges_t ranges ) {  
        if(millis() - _last_update > MINIMUM_DELAY_VL53L0X ) {
            _last_update = millis();
        
            // auto t_last = micros();
            bool success = true;
            for(int i=0;i<IDX_COUNT;i++)  
                success &= readSingleSensor((dist_idx_t)i);

            // Serial.println(micros() - t_last);

            if(success) { 
                if(_filtered) {
                    for(int i=0;i<IDX_COUNT;i++) 
                        _dist_mm_filt[i] = 0.8*_dist_mm_filt[i] + 0.2*_dist_mm[i]; 
                    
                    for(int i=0;i<IDX_COUNT;i++)
                        _dist_mm[i] = (uint16_t)_dist_mm_filt[i]; 
                }

                memcpy(ranges, _dist_mm, IDX_COUNT*sizeof(_dist_mm[0])); 
            }else{ 
                memset(ranges, MAXIMUM_RANGE, IDX_COUNT*sizeof(ranges[0]));  
            } 
            
        } else{
            memcpy(ranges, _dist_mm, IDX_COUNT*sizeof(_dist_mm[0])); 
        }
    }

    void distance_sensor_vl530x::get_range(dist_ranges_t ranges) { 
        memcpy(ranges, _dist_mm, IDX_COUNT*sizeof(_dist_mm[0])); 
    }

} // namespace mdm_dist
