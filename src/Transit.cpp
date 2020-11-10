//
// Created by hammer on 01/07/2020.
//

#include "../include/Transit.hpp"

Transit::Transit(int ledPin, short ledErrPin, short csPin, short intPin, short rstPin, float frequency): ledPin(ledPin),
                                                                                                         ledErrPin(ledErrPin), rstPin(rstPin), frequency(frequency), Radio(csPin, intPin)
{
    pinMode(ledPin, OUTPUT);
    pinMode(ledErrPin, OUTPUT);
    pinMode(rstPin, OUTPUT);
}

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

void Transit::initialiseTransit()
{
    if (!Radio.init()) {
        flashErrLed();
    }
    setRadioFrequency();
    setRadioPower();
}

void Transit::setRadioFrequency()
{
    if (!Radio.setFrequency(frequency)) {
        flashErrLed();
    }
}

[[noreturn]] void Transit::flashErrLed()
{
    while (true) {
        digitalWrite(ledErrPin, HIGH);
        delay(50);
        digitalWrite(ledErrPin, LOW);
        delay(50);
    }
}

void Transit::setRadioPower()
{
    Radio.setTxPower(20, HIGH);
}