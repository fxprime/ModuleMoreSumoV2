
#include <Arduino.h>
#include "enemy_detector.h"

namespace mdmbot
{
    enemy_detector::enemy_detector(sensor_type_t type)
    {
        switch (type)
        {
        case SENSOR_TYPE_VL530X:
            _distance_sensor = new distance_sensor_vl530x();
            break;
        case SENSOR_TYPE_2Y0A21:
            _distance_sensor = new distance_sensor_2Y0A21();
            break;
        default:
            _distance_sensor = new distance_sensor_vl530x();
            break;
        }
    }

    enemy_detector::~enemy_detector()
    {
        delete _distance_sensor;
    }

    const char *enemy_detector::pos_str()
    {
        static const char *pos_str_map[] = {
            [ENEMY_POS_NONE] = "NONE",
            [ENEMY_POS_FRONT_LEFT] = "FRONT_LEFT",
            [ENEMY_POS_FRONT] = "FRONT",
            [ENEMY_POS_FRONT_RIGHT] = "FRONT_RIGHT",
            [ENEMY_POS_LEFT] = "LEFT",
            [ENEMY_POS_RIGHT] = "RIGHT",
            [ENEMY_POS_FRONT_AND_FRONT_LEFT] = "FRONT_AND_FRONT_LEFT",
            [ENEMY_POS_FRONT_AND_FRONT_RIGHT] = "FRONT_AND_FRONT_RIGHT",
            [ENEMY_POS_FRONT_ALL] = "FRONT_ALL",
            [ENEMY_POS_IMPOSSIBLE] = "IMPOSSIBLE",
        };
        return pos_str_map[_detection.position];
    }

    const char *enemy_detector::range_str()
    {
        static const char *range_str_map[] = {
            [ENEMY_RANGE_NONE] = "NONE",
            [ENEMY_RANGE_CLOSE] = "CLOSE",
            [ENEMY_RANGE_MID] = "MID",
            [ENEMY_RANGE_FAR] = "FAR",
        };
        return range_str_map[_detection.range];
    }


 





    void enemy_detector::update()
    {

        dist_ranges ranges;
        _distance_sensor->update(ranges);

        // const uint16_t range_left = ranges[IDX_LEFT];
        const uint16_t range_front_left = ranges[distance_sensor::IDX_FRONT_LEFT];
        const uint16_t range_front = ranges[distance_sensor::IDX_FRONT];
        const uint16_t range_front_right = ranges[distance_sensor::IDX_FRONT_RIGHT];
        // const uint16_t range_right = ranges[IDX_RIGHT];

        // const bool left = range_left < _DETECTED_THRESHOLD;
        const bool front_left = range_front_left < _DETECTED_THRESHOLD;
        const bool front = range_front < _DETECTED_THRESHOLD;
        const bool front_right = range_front_right < _DETECTED_THRESHOLD;
        // const bool right = range_right < _DETECTED_THRESHOLD;

        uint16_t range = _INVALID_RANGE;
        _detection.position = ENEMY_POS_IMPOSSIBLE;
        /*
            if (left) {
                if (front_right || right) {
                    // Impossible
                } else {
                    // TODO: Return something else if also front_left or front
                    _detection.position = ENEMY_POS_LEFT;
                    range = range_left;
                }
            } else if (right) {
                if (front_left || left) {
                    // Impossible
                } else {
                    // TODO: Return something else if also front_left or front
                    _detection.position = ENEMY_POS_RIGHT;
                    range = range_right;
                }
            } else if (front_left && front && front_right) {
        */
        if (front_left && front && front_right)
        {
            _detection.position = ENEMY_POS_FRONT_ALL;
            // Average
            range = ((((range_front_left + range_front) / 2) + range_front_right) / 2);
        }
        else if (front_left && front_right)
        {
            // Impossible
        }
        else if (front_left)
        {
            if (front)
            {
                _detection.position = ENEMY_POS_FRONT_AND_FRONT_LEFT;
                // Average
                range = (range_front_left + range_front) / 2;
            }
            else
            {
                _detection.position = ENEMY_POS_FRONT_LEFT;
                range = range_front_left;
            }
        }
        else if (front_right)
        {
            if (front)
            {
                _detection.position = ENEMY_POS_FRONT_AND_FRONT_RIGHT;
                // Average
                range = (range_front_right + range_front) / 2;
            }
            else
            {
                _detection.position = ENEMY_POS_FRONT_RIGHT;
                range = range_front_right;
            }
        }
        else if (front)
        {
            _detection.position = ENEMY_POS_FRONT;
            range = range_front;
        }
        else
        {
            _detection.position = ENEMY_POS_NONE;
        }

        // Convert range value to enum
        if (range != _INVALID_RANGE)
        {
            if (range < _RANGE_CLOSE)
            {
                _detection.range = ENEMY_RANGE_CLOSE;
            }
            else if (range < _RANGE_MID)
            {
                _detection.range = ENEMY_RANGE_MID;
            }
            else
            {
                _detection.range = ENEMY_RANGE_FAR;
            }
        }
    }


    void enemy_detector::init()
    {
        _distance_sensor->init();
    }


    const uint16_t enemy_detector::getRawData(dist_idx index) const
    {
        dist_ranges ranges;
        _distance_sensor->update(ranges);
        return ranges[index];
    }
     
    bool enemy_detector::detected()
    {
        return _detection.position != ENEMY_POS_NONE && _detection.position != ENEMY_POS_IMPOSSIBLE;
    }

    bool enemy_detector::at_left()
    {
        return _detection.position == ENEMY_POS_LEFT || _detection.position == ENEMY_POS_FRONT_LEFT || _detection.position == ENEMY_POS_FRONT_AND_FRONT_LEFT;
    }

    bool enemy_detector::at_right()
    {
        return _detection.position == ENEMY_POS_RIGHT || _detection.position == ENEMY_POS_FRONT_RIGHT || _detection.position == ENEMY_POS_FRONT_AND_FRONT_RIGHT;
    }

    bool enemy_detector::at_front()
    {
        return _detection.position == ENEMY_POS_FRONT || _detection.position == ENEMY_POS_FRONT_ALL;
    }

    bool enemy_detector::at_front_left()
    {
        return _detection.position == ENEMY_POS_FRONT_AND_FRONT_LEFT;
    }

    bool enemy_detector::at_front_right()
    {
        return _detection.position == ENEMY_POS_FRONT_AND_FRONT_RIGHT;
    }

    bool enemy_detector::enemy_close()
    {
        return _detection.range == ENEMY_RANGE_CLOSE && detected();
    }

    bool enemy_detector::enemy_mid()
    {
        return _detection.range == ENEMY_RANGE_MID && detected();
    }

    bool enemy_detector::enemy_far()
    {
        return _detection.range == ENEMY_RANGE_FAR && detected();
    }





    bool enemy_detector::is_at_left(detection_t* detection) {
        return detection->position == ENEMY_POS_LEFT || detection->position == ENEMY_POS_FRONT_LEFT || detection->position == ENEMY_POS_FRONT_AND_FRONT_LEFT;
    }

    bool enemy_detector::is_at_right(detection_t* detection) {
        return detection->position == ENEMY_POS_RIGHT || detection->position == ENEMY_POS_FRONT_RIGHT || detection->position == ENEMY_POS_FRONT_AND_FRONT_RIGHT;
    }

    bool enemy_detector::is_at_front(detection_t* detection) {
        return detection->position == ENEMY_POS_FRONT || detection->position == ENEMY_POS_FRONT_ALL;
    }

    void enemy_detector::get_detection(detection_t& out) { 
        memcpy(&out, &_detection, sizeof(detection_t));
    }



};