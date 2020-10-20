//
// Created by hammer on 02/06/2020.
//

#ifndef WS_REC_MODULE_ABC_SENSOR_HPP
#define WS_REC_MODULE_ABC_SENSOR_HPP

#include <stdint-gcc.h>
#include "string.h"
#include <Arduino.h>


class Sensor
{

public:
    struct SensorData {
        char sensorId[4] = {};
        char sensorType[4] = {};
        float reading = {};
        char unit[4] = {};
    };

    void reinitialiseTempSensor();
    SensorData* getTempSensorData();

    void addReceivedSensor();
    void prepareSensorsForI2cTransit();
    int getSizeOfSensorArray();
    void nextPacket();
    void resetPacketCount();

//private:
    SensorData temp = {};
    SensorData receivedSensors[20] = {{}};
    char packet[sizeof(receivedSensors[0])];

    short packetCount = 0;


};


#endif //WS_REC_MODULE_ABC_SENSOR_HPP
