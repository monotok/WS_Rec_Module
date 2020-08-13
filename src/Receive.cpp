//
// Created by hammer on 01/07/2020.
//

#include "../include/Receive.hpp"

void Receive::ReceiveSensor(Sensor &sensors)
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

void Receive::initialise()
{
    Radio.init();
}

