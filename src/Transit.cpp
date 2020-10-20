//
// Created by hammer on 01/07/2020.
//

#include "../include/Transit.hpp"

void Transit::ReceiveSensor(Sensor &sensors)
{
    if (Radio.recv(sensorBuffer, &sensorBufferLength))
    {
        digitalWrite(ledPin, HIGH);
        delay(100); //so the led is visible
        memcpy(sensors.getTempSensorData(), sensorBuffer, sensorBufferLength);
        digitalWrite(ledPin, LOW);
        sensors.addReceivedSensor();
        sensors.reinitialiseTempSensor();
    }
}

void Transit::initialise()
{
    Radio.init();
}

