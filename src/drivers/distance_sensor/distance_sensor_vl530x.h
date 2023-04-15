#ifndef DISTANCE_SENSOR_VL530X_H
#define DISTANCE_SENSOR_VL530X_H

#include <Arduino.h>

#include <Wire.h>
#include "distance_sensor.h"
#include <VL53L0X.h>
#include "../pinout.h"

namespace mdm_dist
{

    #define MINIMUM_DELAY_VL53L0X 22
    #define MAXIMUM_RANGE 1000
    #define FILTSAMPLES 3



    class MedianFilter {
    private:
        int _numSamples;
        uint16_t *_samples;
        int _index;

    public:
        MedianFilter(int numSamples) {
        _numSamples = numSamples;
        _samples = new uint16_t[_numSamples];
        _index = 0;

        for (int i = 0; i < _numSamples; i++) {
            _samples[i] = 0;
        }
        }

        ~MedianFilter() {
        delete[] _samples;
        }

        uint16_t getFilteredValue(uint16_t inputValue) {
        // Add the inputValue to the samples array.
        _samples[_index] = inputValue;
        _index = (_index + 1) % _numSamples;

        // Create a copy of the samples array for sorting.
        uint16_t sortedSamples[_numSamples];
        for (int i = 0; i < _numSamples; i++) {
            sortedSamples[i] = _samples[i];
        }

        // Sort the sortedSamples array.
        for (int i = 0; i < _numSamples - 1; i++) {
            for (int j = 0; j < _numSamples - i - 1; j++) {
            if (sortedSamples[j] > sortedSamples[j + 1]) {
                uint16_t temp = sortedSamples[j];
                sortedSamples[j] = sortedSamples[j + 1];
                sortedSamples[j + 1] = temp;
            }
            }
        }

        // Return the median value.
        if (_numSamples % 2 == 0) {
            return (sortedSamples[_numSamples / 2] + sortedSamples[(_numSamples / 2) - 1]) / 2;
        } else {
            return sortedSamples[_numSamples / 2];
        }
        }
    };



    class distance_sensor_vl530x : public distance_sensor
    {

    public:

        struct dist_info_t
        {
            uint8_t addr;
            gpio_t xshut_gpio;

            dist_info_t() {};
            dist_info_t(uint8_t a, gpio_t b) :
            addr(a), xshut_gpio(b) {};
        } ;

        distance_sensor_vl530x(/* args */);
        ~distance_sensor_vl530x();
 
        void init();
        void update(dist_ranges_t ranges);
        void get_range(dist_ranges_t ranges);
        void setFiltered(bool filtered);


    private:
        void forceStandby(dist_info_t info);
        void initAddress(dist_idx_t id, dist_info_t info);
        inline bool readSingleSensor(dist_idx_t id)  __attribute__((always_inline));;
            
        VL53L0X _sensor[IDX_COUNT]; 
        dist_ranges_t _dist_mm; 
        float _dist_mm_filt[IDX_COUNT];
        unsigned long _last_update = 0;
        bool _filtered = false;

        MedianFilter *_medianFilter[IDX_COUNT]; 


    };

}



#endif //DISTANCE_SENSOR_VL530X_H