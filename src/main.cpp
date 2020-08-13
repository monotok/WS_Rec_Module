//TODO: Radio Rec
//TODO: DHT temperature module or support for another one with added functionality
//TODO: I2C Module to communicate with the Raspberry pi
//TODO: Threading

#include <Arduino.h>
#include <Abc_Sensor.hpp>
#include <Receive.hpp>

Sensor sensors;
Receive rec(3, 8);

void setup()
{
    Serial.begin(9600);
    rec.initialise();
}

void loop()
{
    rec.ReceiveSensor(sensors);
    for (auto &reading : sensors.receivedSensors)
    {
        if (reading.sensorId != 0) {
            Serial.print("Sensor ID " + String(reading.sensorId) + " Reading ");
            Serial.print(reading.reading);
            Serial.print('\n');
        }
    }
    Serial.print('\n');
    delay(2000);
}