//
// Created by hammer on 12/11/2020.
//

#include "LocalSensor.hpp"

LocalSensor::LocalSensor(uint8_t cs_pin, uint8_t ledErrPin): bme(cs_pin), ledErrPin(ledErrPin)
{
    pinMode(ledErrPin, OUTPUT);
}

void LocalSensor::flashErrLed()
{
    for (int i = 0; i<10; i++) {
        digitalWrite(ledErrPin, HIGH);
        delay(100);
        digitalWrite(ledErrPin, LOW);
        delay(100);
    }
}

void LocalSensor::initialise()
{
    if (!bme.begin()) {
        flashErrLed();
        errInitialising = ERR_FOUND;
    }
}

void LocalSensor::processTemperature(Sensor& sensor)
{
    Sensor::SensorData* tmp = sensor.getTempSensorData();
    strcpy(tmp->sensorId, "1.0");
    if (errInitialising == ERR_NOT_FOUND) {
        tmp->reading = bme.readTemperature();
    } else {
        tmp->reading = 0.0;
    }
    sensor.addReceivedSensor();
    sensor.reinitialiseTempSensor();
}

void LocalSensor::processHumidity(Sensor &sensor)
{
    Sensor::SensorData* tmp = sensor.getTempSensorData();
    strcpy(tmp->sensorId, "1.1");
    if (errInitialising == ERR_NOT_FOUND) {
        tmp->reading = bme.readHumidity();
    } else {
        tmp->reading = 0.0;
    }
    sensor.addReceivedSensor();
    sensor.reinitialiseTempSensor();
}

void LocalSensor::processPressure(Sensor &sensor)
{
    Sensor::SensorData* tmp = sensor.getTempSensorData();
    strcpy(tmp->sensorId, "1.2");
    if (errInitialising == ERR_NOT_FOUND) {
        tmp->reading = bme.readPressure() / 100.0F;
    } else {
        tmp->reading = 0.0;
    }
    sensor.addReceivedSensor();
    sensor.reinitialiseTempSensor();
}

