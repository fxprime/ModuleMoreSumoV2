
#include "line_detector.h"

namespace mdmbot {

line_detector::line_detector(/* args */)
{
}

line_detector::~line_detector()
{
}
 

void line_detector::init()
{ 
    _infrared_sensor.init();
    Serial.println("line_detector init");
}

const char *line_detector::str()
{
    static const char *line_detection_str_map[] = { [LINE_DETECTION_NONE] = "NONE",
                                                    [LINE_DETECTION_FRONT] = "FRONT",
                                                    [LINE_DETECTION_FRONT_LEFT] = "FRONT_LEFT",
                                                    [LINE_DETECTION_FRONT_RIGHT] = "FRONT_RIGHT",
 };
    return line_detection_str_map[_line_detection];
}

void line_detector::update()
{
    
    ir_voltages voltages; 
    _infrared_sensor.update(voltages); 

    const bool frontLeft = voltages[infrared_sensor::INFRARED_SENSOR_FRONT_LEFT] > _LINE_SENSOR_VOLTAGE_THRESHOLD;
    const bool frontRight = voltages[infrared_sensor::INFRARED_SENSOR_FRONT_RIGHT] > _LINE_SENSOR_VOLTAGE_THRESHOLD;
 
    if(frontLeft && frontRight)
        _line_detection = LINE_DETECTION_FRONT;
    else if(frontLeft)
        _line_detection = LINE_DETECTION_FRONT_LEFT;
    else if(frontRight)
        _line_detection = LINE_DETECTION_FRONT_RIGHT;
    else
        _line_detection = LINE_DETECTION_NONE;
 
}

const int16_t line_detector::getRawData(infrared_idx idx) const
{
    ir_voltages voltages;
    // _infrared_sensor.update(voltages);
    _infrared_sensor.get(voltages); 
    return voltages[idx];
}
 



} // namespace mdmbot