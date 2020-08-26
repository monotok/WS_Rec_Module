//TODO: Radio Rec
//TODO: DHT temperature module or support for another one with added functionality
//TODO: I2C Module to communicate with the Raspberry pi
//TODO: Threading

#include <Arduino.h>
#include <Abc_Sensor.hpp>
#include <Transit.hpp>
#include "Wire.h"

#define MASTER_ADDRESS 0x04

Sensor sensors;
Transit rec(3, 8);

void i2cSendData()
{
    Wire.write(sensors.packet, sensors.getSizeOfSensorArray());
}

void prepareNextSensorSendI2c(int numBytes)
{
    int chosenFunc = 0;
    while(Wire.available())
    {
        chosenFunc = Wire.read();
        if (chosenFunc == 0) {
            sensors.resetPacketCount();
        } else if (chosenFunc == 1) {
            sensors.nextPacket();
        }
        sensors.prepareSensorsForI2cTransit();
    }
}

void setup()
{
    Serial.begin(9600);
    rec.initialise();

    Wire.begin(MASTER_ADDRESS);
    Wire.onRequest(i2cSendData);
    Wire.onReceive(prepareNextSensorSendI2c);
}

void loop()
{
    rec.ReceiveSensor(sensors);
//    for (auto &reading : sensors.receivedSensors)
//    {
//        if (reading.sensorId != 0) {
//            Serial.print("Sensor ID " + String(reading.sensorId) + " Reading ");
//            Serial.print(reading.reading);
//            Serial.print('\n');
//        }
//    }
//    delay(2000);
}