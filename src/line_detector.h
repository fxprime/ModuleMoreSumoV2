#ifndef LINE_DETECTOR_H
#define LINE_DETECTOR_H

#include <Arduino.h>

#include "drivers/infrared_sensor.h"

using namespace mdm_infrared_sensor;

namespace mdmbot { 
 
class line_detector
{

public:

    typedef enum detection
    {
        LINE_DETECTION_NONE,
        LINE_DETECTION_FRONT, 
        LINE_DETECTION_FRONT_LEFT, 
        LINE_DETECTION_FRONT_RIGHT, 
    } detection_t;
    
private:
    infrared_sensor _infrared_sensor;
    detection_t _line_detection;


    int _LINE_SENSOR_VOLTAGE_THRESHOLD = 300;
    
public:
    line_detector(/* args */);
    ~line_detector();
    
    void init();
    void update();
    const char *str();  
    void setThreshold(int threshold) { _LINE_SENSOR_VOLTAGE_THRESHOLD = threshold; };
    void get_detection(detection_t& line) { line = _line_detection; };
    detection_t get_detection() { return _line_detection; };
    const int16_t getRawData(infrared_idx idx) const;
    bool isLineDetected() { return _line_detection != LINE_DETECTION_NONE; };
    bool isLineDetectedFront() { return _line_detection == LINE_DETECTION_FRONT; };
    bool isLineDetectedFrontLeft() { return _line_detection == LINE_DETECTION_FRONT_LEFT; };
    bool isLineDetectedFrontRight() { return _line_detection == LINE_DETECTION_FRONT_RIGHT; };


}; 
 typedef line_detector::detection_t line_detection;

} // namespace mdmbot


#endif //LINE_DETECTOR_H