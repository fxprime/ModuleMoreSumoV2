#ifndef HELPER_DEF_H
#define HELPER_DEF_H
 
#include "driver.h"
#include "drivers/distance_sensor/distance_sensor.h"
#include "drivers/infrared_sensor.h"
#include "enemy_detector.h"
#include "line_detector.h"

using namespace mdm_dist;
using namespace mdm_infrared_sensor;

#define DIST_LEFT                       distance_sensor::IDX_FRONT_LEFT
#define DIST_FRONT                      distance_sensor::IDX_FRONT
#define DIST_RIGHT                      distance_sensor::IDX_FRONT_RIGHT

#define IR_LEFT                         infrared_sensor::INFRARED_SENSOR_FRONT_LEFT
#define IR_RIGHT                        infrared_sensor::INFRARED_SENSOR_FRONT_RIGHT

#define LINE_NOTFOUND                   line_detector::LINE_DETECTION_NONE
#define LINE_FRONT                      line_detector::LINE_DETECTION_FRONT 
#define LINE_FRONT_LEFT                 line_detector::LINE_DETECTION_FRONT_LEFT 
#define LINE_FRONT_RIGHT                line_detector::LINE_DETECTION_FRONT_RIGHT

#define ENEMY_NOTFOUND                  enemy_detector::ENEMY_POS_NONE
#define ENEMY_FRONT_LEFT                enemy_detector::ENEMY_POS_FRONT_LEFT
#define ENEMY_POS_FRONT_AND_FRONT_LEFT  enemy_detector::ENEMY_POS_FRONT_AND_FRONT_LEFT
#define ENEMY_FRONT                     enemy_detector::ENEMY_POS_FRONT
#define ENEMY_FRONT_RIGHT               enemy_detector::ENEMY_POS_FRONT_RIGHT
#define ENEMY_POS_FRONT_AND_FRONT_RIGHT enemy_detector::ENEMY_POS_FRONT_AND_FRONT_RIGHT

#define ENEMY_RANGE_NONE                enemy_detector::ENEMY_RANGE_NONE
#define ENEMY_RANGE_CLOSE               enemy_detector::ENEMY_RANGE_CLOSE
#define ENEMY_RANGE_MID                 enemy_detector::ENEMY_RANGE_MID
#define ENEMY_RANGE_FAR                 enemy_detector::ENEMY_RANGE_FAR

#define SPEED_SLOW                      driver::DRIVE_SPEED_SLOW
#define SPEED_MEDIUM                    driver::DRIVE_SPEED_MEDIUM
#define SPEED_FAST                      driver::DRIVE_SPEED_FAST
#define SPEED_FASTEST                   driver::DRIVE_SPEED_FASTEST

#define DRIVE_FORWARD                   driver::DRIVE_FORWARD
#define DRIVE_REVERSE                   driver::DRIVE_REVERSE
#define DRIVE_ROTATE_LEFT               driver::DRIVE_ROTATE_LEFT
#define DRIVE_ROTATE_RIGHT              driver::DRIVE_ROTATE_RIGHT
#define DRIVE_ARCTURN_SHARP_LEFT        driver::DRIVE_ARCTURN_SHARP_LEFT
#define DRIVE_ARCTURN_SHARP_RIGHT       driver::DRIVE_ARCTURN_SHARP_RIGHT
#define DRIVE_ARCTURN_MID_LEFT          driver::DRIVE_ARCTURN_MID_LEFT
#define DRIVE_ARCTURN_MID_RIGHT         driver::DRIVE_ARCTURN_MID_RIGHT
#define DRIVE_ARCTURN_WIDE_LEFT         driver::DRIVE_ARCTURN_WIDE_LEFT
#define DRIVE_ARCTURN_WIDE_RIGHT        driver::DRIVE_ARCTURN_WIDE_RIGHT

#define SENSOR_VL530X                   enemy_detector::SENSOR_TYPE_VL530X
#define SENSOR_2Y0A21                   enemy_detector::SENSOR_TYPE_2Y0A21

#define MODE_0                          robot_ui::mode_0
#define MODE_1                          robot_ui::mode_1
#define MODE_2                          robot_ui::mode_2
#define MODE_3                          robot_ui::mode_3
#define MODE_4                          robot_ui::mode_4
#define MODE_5                          robot_ui::mode_5
#define MODE_6                          robot_ui::mode_6
#define MODE_7                          robot_ui::mode_7  

// typedef distance_sensor::dist_idx_t DIDX;

#endif