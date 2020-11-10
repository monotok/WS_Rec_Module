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
#define TRANSIT_LED_PIN A1
#define ERR_LED_PIN A2

// Radio
#define RFM69_INT     3
#define RFM69_CS      4
#define RFM69_RST     2
#define RF69_FREQ 868.0

Transit rf(TRANSIT_LED_PIN, ERR_LED_PIN, RFM69_CS, RFM69_INT, RFM69_RST, RF69_FREQ);

short i = 0;

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
    rf.initialiseTransit();

    Wire.begin(MASTER_ADDRESS);
    Wire.onRequest(i2cSendData);
    Wire.onReceive(prepareNextSensorSendI2c);
}

void loop()
{
    rf.ReceiveSensor(sensors);
    for (auto &reading : sensors.receivedSensors)
    {
        if (reading.sensorId[0] != 0) {
            Serial.print("Sensor ID " + String(reading.sensorId) + " Reading ");
            Serial.print(reading.reading);
            Serial.print(" Array Pos ");
            Serial.print(i);
            Serial.print('\n');
        }
        i++;
    }
    i = 0;
    Serial.print('\n');
    delay(1000);
}