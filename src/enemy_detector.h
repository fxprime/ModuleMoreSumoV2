#ifndef ENEMY_DETECTOR_H
#define ENEMY_DETECTOR_H

#include <Arduino.h> 
#include "drivers/distance_sensor/distance_sensor_vl530x.h"
#include "drivers/distance_sensor/distance_sensor_2Y0A21.h"


using namespace mdm_dist;

namespace mdmbot {
 
    // #define DETECT_THRESHOLD (600) // mm
    // #define INVALID_RANGE (1000)
    // #define RANGE_CLOSE (100) // mm
    // #define RANGE_MID (200) // mm
    // #define RANGE_FAR (300) // mm 


    
    class enemy_detector
    {
    public: 

        typedef enum sensor_type{
            SENSOR_TYPE_VL530X,
            SENSOR_TYPE_2Y0A21
        } sensor_type_t;

        typedef enum enemy_pos
        {
            ENEMY_POS_NONE,
            ENEMY_POS_FRONT_LEFT,
            ENEMY_POS_FRONT,
            ENEMY_POS_FRONT_RIGHT,
            ENEMY_POS_LEFT,
            ENEMY_POS_RIGHT,
            ENEMY_POS_FRONT_AND_FRONT_LEFT,
            ENEMY_POS_FRONT_AND_FRONT_RIGHT,
            ENEMY_POS_FRONT_ALL,
            ENEMY_POS_IMPOSSIBLE // Keep this for debugging
        } pos_t;

        typedef enum range
        {
            ENEMY_RANGE_NONE,
            ENEMY_RANGE_CLOSE,
            ENEMY_RANGE_MID,
            ENEMY_RANGE_FAR,
        } range_t;

        struct detection_t
        {
            pos_t position;
            range_t range;
            detection_t() {};
        } ;






    public:
        enemy_detector(sensor_type_t type);
        ~enemy_detector();

        void init(void);
        void update();
        const char *pos_str();
        const char *range_str();

        void setDetectThreshold(int16_t threshold) { _DETECTED_THRESHOLD = threshold; }
        void setInvalidRange(int16_t invalidRange) { _INVALID_RANGE = invalidRange; }
        void setRangeClose(int16_t rangeClose) { _RANGE_CLOSE = rangeClose; }
        void setRangeMid(int16_t rangeMid)  { _RANGE_MID = rangeMid; }
        void setRangeFar(int16_t rangeFar) { _RANGE_FAR = rangeFar; }
        void setDistanceSensorFiltered(bool filtered) { _distance_sensor->setFiltered(filtered); }
 
        void get_detection(detection_t& out);
        detection_t* get_detection() { return &_detection; };


        bool detected();
        bool at_left();
        bool at_right();
        bool at_front();
        bool at_front_left();
        bool at_front_right();

        bool enemy_close();
        bool enemy_mid();
        bool enemy_far();

        bool is_at_left(detection_t* detection);
        bool is_at_right(detection_t* detection);
        bool is_at_front(detection_t* detection);

        const uint16_t getRawData(dist_idx index) const ;
 

    private:


 

        distance_sensor* _distance_sensor;

        detection_t _detection; 

        int16_t _DETECTED_THRESHOLD = 600;
        int16_t _INVALID_RANGE = 1000;
        int16_t _RANGE_CLOSE = 100;
        int16_t _RANGE_MID = 200;
        int16_t _RANGE_FAR = 300;
 

    };
    

    typedef enemy_detector::detection_t enemy_detection;
    typedef distance_sensor::dist_ranges_t dist_ranges;



};




#endif