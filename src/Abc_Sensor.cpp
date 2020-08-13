//
// Created by hammer on 30/07/2020.
//

#include "Abc_Sensor.hpp"

void Sensor::reinitialiseTempSensor()
{
    temp = {};
}

Sensor::SensorData* Sensor::getTempSensorData()
{
    return &temp;
}

void Sensor::addReceivedSensor()
{
    for (auto &s : receivedSensors)
    {
        if(s.sensorId == temp.sensorId || s.sensorId == 0)
        {
            s = temp;
            break;
        }
    }
}

Sensor::SensorData* Sensor::getReceivedSensors()
{
    return receivedSensors;
}

