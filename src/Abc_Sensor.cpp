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

void Sensor::prepareSensorsForI2cTransit()
{
    memcpy(packet, &receivedSensors[packetCount], sizeof(receivedSensors[0]));
}

int Sensor::getSizeOfSensorArray()
{
    return sizeof(receivedSensors[0]);
}

void Sensor::nextPacket()
{
    if(packetCount < (sizeof(receivedSensors)/sizeof(receivedSensors[0])))
    {
        if(packetCount == sizeof(receivedSensors[0])-1) {
            packetCount = 0;
        } else {
            packetCount += 1;
        }
    }
}

void Sensor::resetPacketCount()
{
    packetCount = 0;
}

