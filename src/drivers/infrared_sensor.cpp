#include "infrared_sensor.h"


namespace mdm_infrared_sensor {

infrared_sensor::infrared_sensor(/* args */)
{
  _maxValue = 1023; //Analog Sensor;
}

infrared_sensor::~infrared_sensor()
{
}


void infrared_sensor::init()
{  
  pinMode(GPIO_LINE_DETECT_IR, OUTPUT);
  digitalWrite(GPIO_LINE_DETECT_IR, LOW);
}


void infrared_sensor::emiter_on()
{
  digitalWrite(GPIO_LINE_DETECT_IR, HIGH);
  delayMicroseconds(300);
}

void infrared_sensor::emiter_off()
{
  digitalWrite(GPIO_LINE_DETECT_IR, LOW);
  delayMicroseconds(300);
}


void infrared_sensor::update(ir_voltages_t voltages)
{
  ir_voltages_t voltages_off, voltages_on;


  if(GPIO_LINE_DETECT_IR == -1) {
    voltages_on[INFRARED_SENSOR_FRONT_LEFT] = _maxValue - analogRead(GPIO_LINE_DETECT_FRONT_LEFT);
    voltages_on[INFRARED_SENSOR_FRONT_RIGHT] = _maxValue - analogRead(GPIO_LINE_DETECT_FRONT_RIGHT); 
    voltages[INFRARED_SENSOR_FRONT_LEFT] = voltages_on[INFRARED_SENSOR_FRONT_LEFT];
    voltages[INFRARED_SENSOR_FRONT_RIGHT] = voltages_on[INFRARED_SENSOR_FRONT_RIGHT];
  }else{
    emiter_on();
    voltages_on[INFRARED_SENSOR_FRONT_LEFT] = _maxValue - analogRead(GPIO_LINE_DETECT_FRONT_LEFT);
    voltages_on[INFRARED_SENSOR_FRONT_RIGHT] = _maxValue - analogRead(GPIO_LINE_DETECT_FRONT_RIGHT);
    emiter_off(); 
    voltages_off[INFRARED_SENSOR_FRONT_LEFT] = _maxValue - analogRead(GPIO_LINE_DETECT_FRONT_LEFT);
    voltages_off[INFRARED_SENSOR_FRONT_RIGHT] = _maxValue - analogRead(GPIO_LINE_DETECT_FRONT_RIGHT);

    voltages[INFRARED_SENSOR_FRONT_LEFT] = voltages_on[INFRARED_SENSOR_FRONT_LEFT] - voltages_off[INFRARED_SENSOR_FRONT_LEFT];
    voltages[INFRARED_SENSOR_FRONT_RIGHT] = voltages_on[INFRARED_SENSOR_FRONT_RIGHT] - voltages_off[INFRARED_SENSOR_FRONT_RIGHT];

  }


  voltages[INFRARED_SENSOR_FRONT_LEFT] = voltages[INFRARED_SENSOR_FRONT_LEFT] < 0 ? 0 : voltages[INFRARED_SENSOR_FRONT_LEFT];
  voltages[INFRARED_SENSOR_FRONT_RIGHT] = voltages[INFRARED_SENSOR_FRONT_RIGHT] < 0 ? 0 : voltages[INFRARED_SENSOR_FRONT_RIGHT];
  
  memcpy(_voltages, voltages, INFRARED_SENSOR_COUNT*sizeof(_voltages[0])); 
}

void infrared_sensor::get(ir_voltages_t voltages)
{
  memcpy(voltages, _voltages, INFRARED_SENSOR_COUNT*sizeof(_voltages[0]));
}

}; //NAMESPACE mdm_infrared_sensor