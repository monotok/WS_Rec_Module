//
// Created by hammer on 02/06/2020.
//

#ifndef WS_REC_MODULE_ABC_SENSOR_HPP
#define WS_REC_MODULE_ABC_SENSOR_HPP

#include <stdint-gcc.h>

class Sensor
{

public:
    struct SensorData {
        uint8_t sensorId;
        char sensorType;
        float reading;
        char readingType;
        char unit;
        uint8_t precision;
        uint8_t length;
    } null = {0};

    void reinitialiseTempSensor();
    SensorData* getTempSensorData();

    void addReceivedSensor();
    SensorData* getReceivedSensors();
//    void deleteReceivedSensors();

//private:
    SensorData receivedSensors[20] = {{null}};
    SensorData temp = {};


};


#endif //WS_REC_MODULE_ABC_SENSOR_HPP
