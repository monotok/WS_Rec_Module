//
// Created by hammer on 12/11/2020.
//

#include "LocalSensor.hpp"

LocalSensor::LocalSensor(uint8_t cs_pin, uint8_t ledErrPin): bme(cs_pin), ledErrPin(ledErrPin)
{
    pinMode(ledErrPin, OUTPUT);
}

[[noreturn]] void LocalSensor::flashErrLed()
{
    while (true) {
        digitalWrite(ledErrPin, HIGH);
        delay(50);
        digitalWrite(ledErrPin, LOW);
        delay(50);
    }
}

void LocalSensor::initialise()
{
    if (!bme.begin()) {
        flashErrLed();
    }
}

void LocalSensor::processTemperature(Sensor& sensor)
{
    Sensor::SensorData* tmp = sensor.getTempSensorData();
    strcpy(tmp->sensorId, "1.0");
    strcpy(tmp->sensorType, "tmp");
    strcpy(tmp->unit, "c");
    tmp->reading = bme.readTemperature();
    sensor.addReceivedSensor();
    sensor.reinitialiseTempSensor();
}

void LocalSensor::processHumidity(Sensor &sensor)
{
    Sensor::SensorData* tmp = sensor.getTempSensorData();
    strcpy(tmp->sensorId, "1.1");
    strcpy(tmp->sensorType, "hum");
    strcpy(tmp->unit, "%");
    tmp->reading = bme.readHumidity();
    sensor.addReceivedSensor();
    sensor.reinitialiseTempSensor();
}

void LocalSensor::processPressure(Sensor &sensor)
{
    Sensor::SensorData* tmp = sensor.getTempSensorData();
    strcpy(tmp->sensorId, "1.2");
    strcpy(tmp->sensorType, "pre");
    strcpy(tmp->unit, "hPa");
    tmp->reading = bme.readPressure() / 100.0F;
    sensor.addReceivedSensor();
    sensor.reinitialiseTempSensor();
}

